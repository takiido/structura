#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#include "window.hpp"

int main(int, char**)
{
    StructuraEngine::WindowConfig config;
    config.title = "Test window";
    config.type = StructuraEngine::EDITOR;

    StructuraEngine::StructuraWindow SWin = StructuraEngine::StructuraWindow(config);
    SWin.Init();

    SDL_Window* window = SWin.GetWindow();
    SDL_GLContext gl_context = SWin.GetGLContext();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup backends
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool show_window = true;
    bool running = true;

    // Main loop
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Create a simple window
        ImGui::Begin("Hello, world!", &show_window);
        ImGui::Text(config.type == StructuraEngine::EDITOR
            ? "This is Structura Engine Editor window"
            : "This is Structura Engine Editor window");
        if (ImGui::Button("Close"))
            running = false;
        ImGui::End();

        // Render
        ImGui::Render();
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
