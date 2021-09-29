#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <memory>

namespace matteo {
  class Screen {
    public:
      const static int SCREEN_WIDTH = 2000;
      const static int SCREEN_HEIGHT = 2000;

    private:
      SDL_Window *m_window;
      SDL_Renderer *m_renderer;
      SDL_Texture *m_texture;
      Uint32* m_buffer1;
      Uint32* m_buffer2;
      Uint32 lastTime;

    private:
      void boxblurPixel(const int& x, const int& y);
      // inclusive start and exclusive end
      void boxblurRows(const int xStart, const int xEnd);

    public:
      Screen();
      bool init();
      bool processEvents();
      void update();
      void setPixel(Uint32 x, Uint32 y, Uint8 red, Uint8 green, Uint8 blue);
      void setScreen(Uint32** coordinates, Uint8** colors);
      bool close();
      void boxblur();
  };
}
#endif /* ifndef SCREEN.h */
