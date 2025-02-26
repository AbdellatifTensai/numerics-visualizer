#include <stdio.h>
#include <SDL.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "implot.h"

int main(){
        
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
                return -1;

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        if (!window)
                return -1;

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if(!renderer)
                return -1;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer2_Init(renderer);

        ImPlot::CreateContext();

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        float xs[10];
        for(int x=0; x<10; x++) xs[x] = (float)x;

        float ys[10];
        for(int x=0; x<10; x++) ys[x] = (float)x;

        bool done = false;
        while (!done){
                SDL_Event event;
                while (SDL_PollEvent(&event)){
                        ImGui_ImplSDL2_ProcessEvent(&event);
                        if (event.type == SDL_QUIT)
                                done = true;
                        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                                done = true;
                }
                if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED){
                        SDL_Delay(10);
                        continue;
                }

                ImGui_ImplSDLRenderer2_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();

                {
                        static float f = 0.0f;
                        static int counter = 0;

                        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                        ImGui::Checkbox("Another Window", &show_another_window);

                        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                                counter++;
                        ImGui::SameLine();
                        ImGui::Text("counter = %d", counter);

                        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

                        if (ImPlot::BeginPlot("My Plot")) {
                                ImPlot::PlotLine("My Line Plot", xs, ys, 10);
                                ImPlot::EndPlot();
                        }

                         ImGui::End();

                }

                if (show_another_window){
                        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                        ImGui::Text("Hello from another window!");
                        if (ImGui::Button("Close Me"))
                                show_another_window = false;
                        ImGui::End();
                }

                ImGui::Render();
                SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
                SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
                SDL_RenderClear(renderer);
                ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
                SDL_RenderPresent(renderer);
        }

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
