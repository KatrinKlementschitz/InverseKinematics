#include "Engine.h"
#include "KeyBoard.h"
#include <GLFW/glfw3.h>
#include "Window.h"

void KeyBoard::KeyEvent(int key, int action)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(engine_->window_->GetWindow(), true);
	}
}
