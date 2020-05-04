#include "Window.h"
#include <cstdlib>
#include <iostream>

Window::Window(int Width, int Height, const char* Title)
{
	width = Width;
	height = Height;
	title = Title;
	Create();
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

void Window::Create()
{
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	if(width <= 0||height<=0)
	{
		width = mode->width;
		height = mode->height;

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwSetWindowMonitor(window, monitor, 50, 50, width, height, 60);
	}
	else
	{
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwSetWindowMonitor(window, nullptr, 50, 50, width, height, 60);
	}
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	SetGlfwCallBacks();


	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	OnAfterCreated();
}

void Window::UpdateDimensions()
{

}

void Window::MaximizeWindow()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(window, monitor, 50, 50, mode->width, mode->height, 60);
	isMax = true;
}

void Window::RestoreWindow()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(window, nullptr, 50, 50, 800, 800, 60);
	isMax = false;
}

void Window::ToggleFullscreen()
{
	if (isMax)
		RestoreWindow();
	else
		MaximizeWindow();
}

void Window::OnAfterCreated()
{
}

void Window::SetGlfwCallBacks()
{
}
