#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bitset>
#include <string>


class WindowManager
{
public:
	bool Init(
		std::string const& windowTitle, unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPositionX, unsigned int windowPositionY);

	void Update();

	void ProcessEvents();

	void Shutdown();

	GLFWwindow* getWindow() const { return mWindow; }

	bool isCursorEnabled = false;
	bool mFirstMouse;
	double mLastMouseX, mLastMouseY = 0;
private:
	GLFWwindow* mWindow;

	std::bitset<8> mButtons;

	void toggleCursorMode();
};
