#pragma once

#include <bitset>
#include <glm/glm.hpp>
#include <cstdint>


// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
    return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
{
    return fnv1a_32(s, count);
}


// ECS
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;


// Input
enum class InputButtons
{
    W,
    A,
    S,
    D,
    Q,
    E
};

// Logs
enum class LogMessageType {
    Text,
    Separator
};

struct LogMessage {
    LogMessageType type;
    std::string text;
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color = {1.0f, 1.0f, 1.0f};
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// TODO: Make these easier to define and use (macro?)
// TODO: Add some kind of enforcement/automation that a SetParam type and a GetParam type match

// Events
using EventId = std::uint32_t;
using ParamId = std::uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

// Events : Window
namespace Events::Window {
const EventId QUIT = "Events::Window::QUIT"_hash;
const EventId RESIZED = "Events::Window::RESIZED"_hash;
const EventId KEYDOWN = "Events::Window::KEYDOWN"_hash;
const EventId MOUSEMOVE = "Events::Window::MOUSEMOVE"_hash;
const EventId MOUSECLICK = "Events::Window::MOUSECLICK"_hash;
}

// Params
namespace Events::Window::Input {
const ParamId KEYS_DOWN = "Events::Window::Input::KEYS_DOWN"_hash;
const ParamId MOUSE_XOFFSET =  "Events::Window::Input::MOUSE_XOFFSET"_hash;
const ParamId MOUSE_YOFFSET =  "Events::Window::Input::MOUSE_YOFFSET"_hash;
const ParamId MOUSE_BUTTON = "Events::Window::Input::MOUSE_BUTTON"_hash;
}

namespace Events::Window::Resized {
const ParamId WIDTH = "Events::Window::Resized::WIDTH"_hash;
const ParamId HEIGHT = "Events::Window::Resized::HEIGHT"_hash;
}

// Events : Game
namespace Events::Game {
const EventId START =  "Events::Game::START"_hash;
const EventId NEW_TURN = "Events::Game::NEW_TURN"_hash;
}

// Params
namespace Events::Game {
const ParamId CURRENT_TURN = "Events::Game::CURRENT_TURN"_hash;
}


// Events : Log
namespace Events::Log {
const EventId NEW_MESSAGE = "Events::Log::NEW_MESSAGE"_hash;
const ParamId MESSAGE = "Events::Log::MESSAGE"_hash;
}

// Events GUI
namespace Events::GUI {
const EventId START_GAME_CLICKED = "Events::GUI::START_GAME_CLICKED"_hash;
const EventId RESET_GAME_CLICKED = "Events::GUI::RESET_GAME_CLICKED"_hash;
const EventId NEXT_TURN_CLICKED = "Events::GUI::NEXT_TURN_CLICKED"_hash;
}