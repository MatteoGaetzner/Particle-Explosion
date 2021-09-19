#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

int main()
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 800;

  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    std::cout << "SDL init failed" << std::endl;
    return 0;
  }

  SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    SDL_Quit();
    return 2;
  }

  // SDL_RENDERER_PRESENTVSYNC tells rendering to sync with display refresh rate (looks better)
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (renderer == NULL) {
    std::cout << "Could not create renderer." << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 3;
  }

  if (texture == NULL) {
    std::cout << "Could not create texture." << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 4;
  }

  /* Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; */
  std::unique_ptr<Uint32> buffer(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]);

  // make screen black
  memset(buffer.get(), 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));


  SDL_UpdateTexture(texture, NULL, buffer.get(), SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  bool quit = false;

  SDL_Event event;

  while(not quit) {
    // Update particles
    // Draw particles
    // Check for messages / events

    while (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
