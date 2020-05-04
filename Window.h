#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Window
{
protected:
	GLFWwindow* window = nullptr;
	bool isMax = false;

public:
	int width, height;
	float aspectRatio;
	const char* title;
	glm::vec2 cursor = glm::vec2(0);

	Window(int Width, int Height, const char* Title);

	GLFWwindow* GetWindow();

	void Create();

	void UpdateDimensions();

	void MaximizeWindow();

	void RestoreWindow();

	void ToggleFullscreen();

	virtual void OnAfterCreated();

	virtual void SetGlfwCallBacks();
};

