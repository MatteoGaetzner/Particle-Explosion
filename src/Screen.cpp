#include <iostream>
#include <memory>
#include "Screen.h"

namespace matteo {
  Screen::Screen()
    :m_window(NULL), m_renderer(NULL),
    m_texture(NULL), m_buffer(NULL) {

    }


  bool Screen::init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
      std::cout << "SDL init failed" << std::endl;
      return false;
    }

    m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_window == NULL) {
      SDL_Quit();
      return false;
    }

    // SDL_RENDERER_PRESENTVSYNC tells rendering to sync with display refresh rate (looks better)
    SDL_Renderer* renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (renderer == NULL) {
      std::cout << "Could not create renderer." << std::endl;
      SDL_DestroyWindow(m_window);
      SDL_Quit();
      return false;
    }

    if (texture == NULL) {
      std::cout << "Could not create texture." << std::endl;
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(m_window);
      SDL_Quit();
      return false;
    }

    std::unique_ptr<Uint32> buffer(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]);

    memset(buffer.get(), 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; ++i) {
      buffer.get()[i] = 0xFFF00FFF;
    }

    SDL_UpdateTexture(texture, NULL, buffer.get(), SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

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

  bool Screen::close(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
  }
}
