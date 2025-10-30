#ifndef STRUCTURA_ENGINE_WINDOW_HPP
#define STRUCTURA_ENGINE_WINDOW_HPP

#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>

namespace StructuraEngine {
  constexpr int MIN_WIN_WIDTH = 640;
  constexpr int MIN_WIN_HEIGHT = 480;

  enum WindowType {
    EDITOR,
    GAME,
  };

  struct WindowResolution {
    int w;
    int h;
  };

  struct WindowConfig {
    WindowResolution resolution = {640, 480};
    std::string title = "Structura Engine Window";
    WindowType type = GAME;
    bool resizable = true;
    bool fullscreen = false;
    bool borderless = false;
    bool vsync = false;
  };

  class StructuraWindow {
  public:
    StructuraWindow(const WindowConfig& cfg);
    ~StructuraWindow();

    StructuraWindow(const StructuraWindow&) = delete;
    StructuraWindow& operator=(const StructuraWindow&) = delete;

    void setResolution(WindowResolution size);
    void setTitle(const std::string& value);
    void setType(WindowType value);
    void setVsync(bool value);

    WindowResolution getResolution() const { return m_resolution; }
    std::string getTitle() const { return m_title; };
    WindowType getType() const { return m_type; }
    bool getVsync() const { return m_enableVsync; }
    SDL_Window* getWindow() const { return m_window; }
    SDL_GLContext getGLContext() const { return m_glContext; }

  private:
    static int s_instanceCount;
    static constexpr std::string_view EDITOR_SUFFIX = "    —   Editor";

    // Window props
    WindowResolution m_resolution;
    std::string m_title;
    WindowType m_type;

    // Window flags
    bool m_allowResizable;
    bool m_allowFullscreen;
    bool m_allowBorderless;

    // GL props
    bool m_enableVsync;

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;

    void updateTitle();
  };
}

#endif // STRUCTURA_ENGINE_WINDOW_HPP