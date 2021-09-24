#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <memory>

namespace matteo {
  class Screen {
    public:
      const static int SCREEN_WIDTH = 1000;
      const static int SCREEN_HEIGHT = 1000;
    private:
      SDL_Window *m_window;
      SDL_Renderer *m_renderer;
      SDL_Texture *m_texture;
      Uint32* m_buffer;
      Uint32 lastTime;

    public:
      Screen();
      bool init();
      bool processEvents();
      void update();
      void setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue);
      bool close();
  };
}
#endif /* ifndef SCREEN.h */
