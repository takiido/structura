#include <SDL3/SDL.h>
#include <iostream>

namespace StructuraEngine {
  const int MIN_WIN_WIDTH = 640;
  const int MIN_WIN_HEIGHT = 480;

  enum WindowType {
    EDITOR,
    GAME,
  };

  struct WindowConfig {
    int width = 640;
    int height = 480;
    std::string title = "Structura Engine Window";
    WindowType type = GAME;
    bool resizable = true;
    bool fullscreen = false;
    bool borderless = false;
    bool vsync = false;
  };

  class StructuraWindow {
  public:
    StructuraWindow(const WindowConfig& cfg)
      : width(cfg.width),
      height(cfg.height),
      title(cfg.title),
      type(cfg.type),
      allowResizable(cfg.resizable),
      allowFullscreen(cfg.fullscreen),
      allowBorderless(cfg.borderless),
      allowVsync(cfg.vsync) {
    }

    void SetSize(int w, int h);
    void SetType(WindowType value);
    void SetResizable(bool value);
    std::string GetTitle() { return title; };
    void Init();

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return gl_context; }

  private:
    // Window props
    int width;
    int height;
    std::string title;
    WindowType type;

    // Window flags
    bool allowResizable;
    bool allowFullscreen;
    bool allowBorderless;

    // GL props
    bool allowVsync;

    SDL_Window* window = nullptr;
    SDL_GLContext gl_context = nullptr;

    void UpdateTitle();
  };
}
