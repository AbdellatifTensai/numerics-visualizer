#include <stdio.h>
#include <SDL.h>
#include <limits.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "implot.h"

int main(){
        
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
                return -1;

        SDL_Window* Window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        if (!Window)
                return -1;

        SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if(!Renderer)
                return -1;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(Window, Renderer);
        ImGui_ImplSDLRenderer2_Init(Renderer);
        
        //ImFont *font = io.Fonts->AddFontFromFileTTF("~/.fonts/JetBrainsMonoNerdFont-Medium.ttf", 15.0f);

        ImPlot::CreateContext();

        // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        float xs[100];
        float ys[100];
        for(int x=0; x<100; x++){
                xs[x] = (float)(x * .1f);
                ys[x] = 1 * cos(xs[x]);
        }

        char Buff_a[64];
        char Buff_b[64];
        char Buff_c[64];
        char Buff_f[64];
        char Buff_y[64];
        int BuffSize = 64;
        int N = 64;
        float T0 = 0;
        float Tf = 1;
        float h = (Tf - T0) / N;

        bool IsQuit = false;
        while (!IsQuit){

                SDL_Event event;
                while (SDL_PollEvent(&event)){
                        ImGui_ImplSDL2_ProcessEvent(&event);
                        if (event.type == SDL_QUIT)
                                IsQuit = true;
                        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Window))
                                IsQuit = true;
                }

                if (SDL_GetWindowFlags(Window) & SDL_WINDOW_MINIMIZED){
                        SDL_Delay(10);
                        continue;
                }

                ImGui_ImplSDLRenderer2_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();

                ImGui::SetNextWindowSize(io.DisplaySize);
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::Begin("Numerics", nullptr, ImGuiWindowFlags_NoDecoration);
                 ImGui::ShowDemoWindow();

                ImVec2 WindowDim = ImGui::GetContentRegionAvail();
                float PanelWidth = WindowDim.x * .3;

                ImGui::BeginChild("Methodes", ImVec2(PanelWidth, WindowDim.y), true);

                if (ImGui::CollapsingHeader("Equation Differentielle Ordinaire")){
                        ImGui::DragFloat("t0", &T0, 0.05f, 0.0f, Tf, "%.3f", ImGuiSliderFlags_None);
                        ImGui::DragFloat("tf", &Tf, 0.05f, T0, FLT_MAX, "%.3f", ImGuiSliderFlags_None);
                        if(ImGui::DragInt("N", &N, 1, 1, INT_MAX, "%d", ImGuiSliderFlags_None))
                                h = (Tf - T0) / N;
                        if(ImGui::DragFloat("h", &h, 0.0001f, 0, 1, "%f", ImGuiSliderFlags_None))
                                N = (int)((Tf - T0) / h);

                        ImGui::InputText("y(t)", Buff_y, BuffSize);
                //         bool Update = false;
                //         ImGui::Text("a(x)y''(x) + b(x)y'(x) + c(x)y(x) = f(x)");
                //         Update |= ImGui::InputText("a(x)", Buff_a, BuffSize);
                //         Update |= ImGui::InputText("b(x)", Buff_b, BuffSize);
                //         Update |= ImGui::InputText("c(x)", Buff_c, BuffSize);
                //         Update |= ImGui::InputText("f(x)", Buff_f, BuffSize);
                //         if(Update){

                //         }
                }

                if (ImGui::CollapsingHeader("Equation Differentielle Partielle")){}
                if (ImGui::CollapsingHeader("Gradient Descent")){}
                
                ImGui::EndChild();

                ImGui::SameLine();

                float GraphWidth = WindowDim.x - PanelWidth;
                ImGui::BeginChild("Graph", ImVec2(GraphWidth, WindowDim.y), true);

                if (ImPlot::BeginPlot("Solution", ImGui::GetContentRegionAvail())) {
                        ImPlot::PlotLine("y(x)", xs, ys, 100);
                        ImPlot::EndPlot();
                }

                ImGui::EndChild();
                ImGui::End();

                ImGui::Render();
                SDL_RenderSetScale(Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
                SDL_RenderClear(Renderer);
                ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), Renderer);
                SDL_RenderPresent(Renderer);
        }

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
        SDL_Quit();

        return 0;
}
