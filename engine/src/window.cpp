#include "window.hpp"

namespace StructuraEngine {
    void StructuraWindow::SetSize(int w, int h)
    {
        width = w >= MIN_WIN_WIDTH ? w : MIN_WIN_HEIGHT;
        height = h >= MIN_WIN_HEIGHT ? h : MIN_WIN_HEIGHT;
    }

    void StructuraWindow::SetType(WindowType value) {
        type = value;
        UpdateTitle();
    }

    void StructuraWindow::SetResizable(bool value)
    {
        if (!allowResizable && value)
        {
            return;
        }
        SDL_SetWindowResizable(window, value);
    }

    void StructuraWindow::Init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr
                << "SDL init failed: "
                << SDL_GetError()
                << "\n";
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        Uint32 flags = SDL_WINDOW_OPENGL;
        if (allowResizable)  flags |= SDL_WINDOW_RESIZABLE;
        if (allowFullscreen) flags |= SDL_WINDOW_FULLSCREEN;
        if (allowBorderless) flags |= SDL_WINDOW_BORDERLESS;

        UpdateTitle();
        window = SDL_CreateWindow(title.c_str(), width, height, flags);
        if (!window) {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
            return;
        }

        gl_context = SDL_GL_CreateContext(window);
        if (!gl_context) {
            std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
            return;
        }

        SDL_GL_MakeCurrent(window, gl_context);

        if (allowVsync) {
            SDL_GL_SetSwapInterval(1);
        }
        else {
            SDL_GL_SetSwapInterval(0);
        }
    }

    void StructuraWindow::UpdateTitle() {
        const std::string suffix = "    —   Editor";

        if (type == WindowType::EDITOR) {
            if (title.find(suffix) == std::string::npos) {
                title += suffix;
                if (window) SDL_SetWindowTitle(window, title.c_str());
            }
        }
        else {
            size_t pos = title.find(suffix);
            if (pos != std::string::npos) {
                title.erase(pos, suffix.length());
                if (window) SDL_SetWindowTitle(window, title.c_str());
            }
        }
    }
}
