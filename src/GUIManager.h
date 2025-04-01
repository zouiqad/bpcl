#pragma once

#include <vector>
#include <string>
#include <imgui.h>

#include "WindowManager.h"
#include "core/Event.h"

struct ImGuiIO;

class GUIManager {
public:
    void Init(GLFWwindow* window);

    void Update();

    void Shutdown();

    void NewFrame();

    void Log(const std::string& msg, const LogMessageType& type = LogMessageType::Text);

private:
    ImGuiIO *io = nullptr;

    std::vector<LogMessage> mLogMessages;

    void DrawParams();
    void DrawLog();

    // Listeners
    void LogListener(Event &event);
};
