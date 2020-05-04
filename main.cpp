#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Engine.h"
#include "Window.h"
#include "Text.h"
#include <GL/gl.h>
#include "Drawable.h"
#include "RectDrawer.h"
#include "HSV.h"
#include "InverseKinematics.h"

class customWindow : public Window
{
public:
	customWindow(float width, float height, const char* title) : Window(width, height, title) { }

	void SetGlfwCallBacks() override;

	void OnAfterCreated() override;
};

customWindow custom_window(800, 800, "Inverse Kinematics!");
Text::TextStruct fps_monitor;

RectDrawer::Rect r;

class customEngine : public Engine
{
public:
	customEngine(customWindow* window) : Engine(window){}

	void OnBeforeDraw() override;

	void OnAfterDraw() override;
};

customEngine engine(&custom_window);

InverseKinematics snake = InverseKinematics(&engine, 1000, 2, 2, glm::vec4(1, 0, 0, 1));

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	engine.window_->cursor.x = xpos;
	engine.window_->cursor.y = custom_window.height - ypos;
	r.pos = engine.window_->cursor;
	snake.Update(engine.window_->cursor);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0)
		return;
	glViewport(0, 0, width, height);

	engine.window_->width = width;
	engine.window_->height = height;
	engine.window_->aspectRatio = static_cast<float>(engine.window_->width) / static_cast<float>(engine.window_->height);
	
	engine.text->UpdateWindowSize();
	engine.rect_drawer->UpdateWindowSize();
	fps_monitor.y = engine.window_->height - 40;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	engine.key_board.KeyEvent(key, action);
}

void customWindow::SetGlfwCallBacks()
{
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	glEnable(GL_FRAMEBUFFER_SRGB);
}

void customWindow::OnAfterCreated()
{
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void customEngine::OnBeforeDraw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

average aver(300);

void customEngine::OnAfterDraw()
{
	const double fps = aver.Get(timer.deltaTime);
	fps_monitor.text = std::to_string(static_cast<int>(1.0 / fps));

	Engine::OnAfterDraw();
}

void Stop()
{
	glfwSetWindowShouldClose(engine.window_->GetWindow(), true);
	glfwTerminate();
}

int main()
{
	fps_monitor.x = 10;
	fps_monitor.y = engine.window_->height-40;
	fps_monitor.color = glm::vec3(0.1,0.1,0.1);
	fps_monitor.scale = 0.75;
	fps_monitor.text = "";

	engine.text->DrawText(&fps_monitor);
	engine.DrawBuffer.push_back(engine.text);
	engine.DrawBuffer.push_back(engine.rect_drawer);

	engine.Start();

	Stop();
	return 0;
}