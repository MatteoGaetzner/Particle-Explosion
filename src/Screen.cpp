#include <iostream>
#include <stdlib.h>
#include <thread>
#include "../inc/Screen.h"

#define SCREEN_MODE SDL_WINDOW_ALLOW_HIGHDPI
/* #define SCREEN_MODE SDL_FULLSCREEN */

const unsigned int PROCESSOR_COUNT = std::thread::hardware_concurrency();
std::mutex mtx;

namespace matteo {
  Screen::Screen()
    :m_window(NULL), m_renderer(NULL),
    m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {}


  bool Screen::init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
      std::cout << "SDL init failed" << std::endl;
      return false;
    }

    m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MODE);

    if (m_window == NULL) {
      SDL_Quit();
      return false;
    }

    // SDL_RENDERER_PRESENTVSYNC tells rendering to sync with display refresh rate (looks better)
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (m_renderer == NULL) {
      std::cout << "Could not create renderer." << std::endl;
      SDL_DestroyWindow(m_window);
      SDL_Quit();
      return false;
    }

    if (m_texture == NULL) {
      std::cout << "Could not create texture." << std::endl;
      SDL_DestroyRenderer(m_renderer);
      SDL_DestroyWindow(m_window);
      SDL_Quit();
      return false;
    }

    m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    memset(m_buffer1, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;
  }

  bool Screen::processEvents(){
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return false;
      }
    }

    return true;
  }

  void Screen::setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue) {

    if (x >= Screen::SCREEN_WIDTH || y >= Screen::SCREEN_HEIGHT) {
      return;
    }

    unsigned int color = 0;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer1[x + SCREEN_WIDTH * y] = color;
  }

  void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    // looks funny if next line gets uncommented
    /* memset(m_buffer1, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); */
  }

  bool Screen::close() {
    delete [] m_buffer1;
    delete [] m_buffer2;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
  }

  void Screen::boxblurRows(const int xStart, const int xEnd) {
    for (int x = xStart; x < xEnd; ++x) {
      for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        boxblurPixel(x, y);
      }
    }
  }

  void Screen::boxblurPixel(const int& x, const int& y) {
    Uint16 totalRed = 0;
    Uint16 totalGreen = 0;
    Uint16 totalBlue = 0;

    /* Use the box blur kernel
     *
     *    0 0 0
     *    0 1 0
     *    0 0 0
     *
     * to update the pixel */

    int currentX;
    int currentY;

    for (int row = -1; row <= 1; row++) {
      for (int col = -1; col <= 1; col++) {

        currentX = x + col;
        currentY = y + row;

        // If the current pixel is actually within the screen..
        if (currentX >= 0 && currentY >= 0 && currentX < SCREEN_WIDTH && currentY < SCREEN_HEIGHT) {

          Uint32 currentColor = m_buffer2[currentY * SCREEN_WIDTH + currentX];

          /* totalRed += currentColor >> 24; */
          /* totalGreen += currentColor >> 16; */
          /* totalBlue = currentColor >> 8; */
          Uint8 red = currentColor >> 24;
          Uint8 green = currentColor >> 16;
          Uint8 blue = currentColor >> 8;

          totalRed += red;
          totalGreen += green;
          totalBlue += blue;
        }
      }
    }

    // Set the pixel
    /* std::cout << totalRed / 9 << " " <<  totalGreen / 9 << " "  << totalBlue / 9 << std::endl; */

    Uint8 red = totalRed / 9;
    Uint8 green = totalGreen / 9;
    Uint8 blue = totalBlue / 9;

    setPixel(x, y, red, green, blue);
  }

  void Screen::boxblur() {
    // Swap buffers
    Uint32 *tmpBuffer = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = tmpBuffer;

    // Create threads array
    std::thread workers[PROCESSOR_COUNT+1];
    int batchsize = SCREEN_WIDTH / PROCESSOR_COUNT;
    int workerIdx = 0;

    // Iterate over all pixels
    for (int x = 0; x < SCREEN_WIDTH; x += batchsize) {
      int xMax = SCREEN_WIDTH <= x + batchsize ? SCREEN_WIDTH : x + batchsize;
      workers[workerIdx++] = std::thread(&Screen::boxblurRows, this, x, xMax);
    }

    for (std::thread &worker : workers) {
      if (worker.joinable())
        worker.join();
    }
  }
}
