#include "GUIManager.h"

#include <iostream>
#include <ostream>

#include "core/Mediator.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "game/Config.h"


extern Mediator gMediator;

void GUIManager::Init(GLFWwindow* window) {
    // Create ImGui context and set style.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize Platform/Renderer backends.
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    gMediator.AddEventListener(METHOD_LISTENER(Events::Log::NEW_MESSAGE, GUIManager::LogListener));
}

void GUIManager::NewFrame() {
    // Start a new ImGui frame.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DrawParams();
    DrawLog();
}

void GUIManager::DrawParams() {
    if(ImGui::Begin("Simulation Controls"))
    {
        // Autoplay toggle.
        ImGui::Checkbox("Autoplay", &Config::GetInstance().autoplay);

        if (ImGui::CollapsingHeader("Initialization Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SeparatorText("Zombie params");
            ImGui::SliderInt("Zombie Base Count", &Config::GetInstance().baseZombieCount, 0, 10);
            ImGui::SliderInt("Zombie Explosive Count", &Config::GetInstance().explosiveZombieCount, 0, 10);
            ImGui::SliderInt("Zombie Runner Count", &Config::GetInstance().runnerZombieCount, 0, 10);

            ImGui::SeparatorText("Survivor params");
            ImGui::SliderInt("Survivor Base Count", &Config::GetInstance().baseSurvivorCount, 0, 10);
            ImGui::SliderInt("Survivor Doctor Count", &Config::GetInstance().doctorSurvivorCount, 0, 10);
            ImGui::SliderInt("Survivor Military Count", &Config::GetInstance().militarySurvivorCount, 0, 10);
        }

        if (ImGui::CollapsingHeader("Runtime Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SeparatorText("Zombie params");
            ImGui::SliderInt("Explosive Zombie - Explosion Radius", &Config::GetInstance().explosiveZombieRange, 0.0f, 10.0f);
            ImGui::SliderInt("Runner Steps", &Config::GetInstance().runnerZombieSteps, 0, 10);

            ImGui::SeparatorText("Survivor params");
            ImGui::SliderInt("Military Survivor Range", &Config::GetInstance().militarySurvivorRange, 0.0f, 10.0f);
            ImGui::SliderInt("Survivor infection speed (Number of turns)", &Config::GetInstance().infectionSpeed, 1, 10);

            ImGui::SeparatorText("Misc params");
            ImGui::SliderFloat("Turn Speed (seconds)", &Config::GetInstance().turnDuration, 0.1f, 10.0f);
        }



        if(Config::GetInstance().autoplay || !Config::GetInstance().simulationStarted || Config::GetInstance().simulationFinished) {
            ImGui::BeginDisabled();
        }

        if(ImGui::Button("Next Turn")) {
            Event event(Events::GUI::NEXT_TURN_CLICKED);
            gMediator.SendEvent(event);
        }

        if(Config::GetInstance().autoplay || !Config::GetInstance().simulationStarted || Config::GetInstance().simulationFinished) {
            ImGui::EndDisabled();
        }

        if(ImGui::Button("Start Simulation")) {
            Event event(Events::GUI::START_GAME_CLICKED);
            gMediator.SendEvent(event);
        }

        if(ImGui::Button("Reset Simulation")) {
            mLogMessages.clear();

            Event event(Events::GUI::RESET_GAME_CLICKED);
            gMediator.SendEvent(event);
        }

    }

    ImGui::SeparatorText("Basic Controls");
    ImGui::Text("Press F to enable flycam / cursor.");
    ImGui::Text("Use WASD to move when in flycam mode.");
    ImGui::Text("Use the tweak settings above to adjust simulation parameters.");
    ImGui::Text("Press ESC to quit the application.");

    ImGui::End();
}

void GUIManager::DrawLog() {
    ImGui::Begin("Simulation Logs");
    for (const auto &entry : mLogMessages) {
        switch (entry.type) {
            case LogMessageType::Separator:
                ImGui::SeparatorText(entry.text.c_str());
            break;
            case LogMessageType::Text:
                ImGui::TextUnformatted(entry.text.c_str());
            break;
        }
    }
    ImGui::End();
}


void GUIManager::Update()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::Log(const std::string& msg, const LogMessageType& type) {
    mLogMessages.push_back(LogMessage{type, msg});

    if (mLogMessages.size() > 1000)
        mLogMessages.erase(mLogMessages.begin());
}

void GUIManager::LogListener(Event &event) {
    auto msg = event.GetParam<std::string>(Events::Log::MESSAGE);
    Log(msg);
}

