#include "window.hpp"

namespace StructuraEngine {
    int StructuraWindow::s_instanceCount = 0;

    StructuraWindow::StructuraWindow(const WindowConfig& cfg)
        : m_resolution{
            std::max(cfg.resolution.w, MIN_WIN_WIDTH),
            std::max(cfg.resolution.h, MIN_WIN_HEIGHT)
        },
        m_title(cfg.title),
        m_type(cfg.type),
        m_allowResizable(cfg.resizable),
        m_allowFullscreen(cfg.fullscreen),
        m_allowBorderless(cfg.borderless),
        m_enableVsync(cfg.vsync)
    {
        if (s_instanceCount == 0) {
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                throw std::runtime_error(
                    std::string("SDL init failed: ") + SDL_GetError()
                );
            }
        }
        s_instanceCount++;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        Uint32 flags = SDL_WINDOW_OPENGL;
        if (m_allowResizable)  flags |= SDL_WINDOW_RESIZABLE;
        if (m_allowFullscreen) flags |= SDL_WINDOW_FULLSCREEN;
        if (m_allowBorderless) flags |= SDL_WINDOW_BORDERLESS;

        updateTitle();
        m_window = SDL_CreateWindow(m_title.c_str(), m_resolution.w, m_resolution.h, flags);
        if (!m_window) {
            throw std::runtime_error(
                std::string("Window creation failed: ") + SDL_GetError()
            );
        }

        m_glContext = SDL_GL_CreateContext(m_window);
        if (!m_glContext) {
            SDL_DestroyWindow(m_window);
            s_instanceCount--;
            if (s_instanceCount == 0) {
                SDL_Quit();
            }

            throw std::runtime_error(
                std::string("SDL_GL_CreateContext failed: ") + SDL_GetError()
            );
        }

        SDL_GL_MakeCurrent(m_window, m_glContext);

        SDL_GL_SetSwapInterval(m_enableVsync ? 1 : 0);
    }

    StructuraWindow::~StructuraWindow() {
        if (m_glContext) {
            SDL_GL_DestroyContext(m_glContext);
            m_glContext = nullptr;
        }
        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }

        s_instanceCount--;
        if (s_instanceCount == 0) {
            SDL_Quit();
        }
    }

    void StructuraWindow::setResolution(WindowResolution resolution)
    {
        if (!m_window) return;
        if (resolution.w < MIN_WIN_WIDTH || resolution.h < MIN_WIN_HEIGHT)
            return;
        m_resolution = resolution;

        SDL_SetWindowSize(m_window, m_resolution.w, m_resolution.h);
    }

    void StructuraWindow::setTitle(const std::string& value) {
        if (!m_window) return;
        m_title = value;
        updateTitle();
    }

    void StructuraWindow::setType(WindowType value) {
        if (!m_window) return;
        m_type = value;
        updateTitle();
    }

    void StructuraWindow::setVsync(bool value) {
        m_enableVsync = value;
        if (m_enableVsync) {
            SDL_GL_SetSwapInterval(1);
        }
        else {
            SDL_GL_SetSwapInterval(0);
        }
    }

    void StructuraWindow::updateTitle() {
        static bool isEditorTitle = false;
        if (m_type == WindowType::EDITOR && !isEditorTitle) {
            if (m_title.find(EDITOR_SUFFIX) == std::string::npos) {
                m_title += EDITOR_SUFFIX;
                if (m_window) SDL_SetWindowTitle(m_window, m_title.c_str());
            }
            isEditorTitle = true;
        }
        else if (m_type == WindowType::GAME && isEditorTitle) {
            size_t pos = m_title.find(EDITOR_SUFFIX);
            if (pos != std::string::npos) {
                m_title.erase(pos, EDITOR_SUFFIX.length());
                if (m_window) SDL_SetWindowTitle(m_window, m_title.c_str());
            }
            isEditorTitle = false;
        }
    }
}
