#include "Engine.h"
#include "Window.h"
#include "DrawCollection.h"
#include <GLFW/glfw3.h>


Engine::Engine(Window* window)
{
	window_ = window;
	window->SetGlfwCallBacks();
	rect_drawer = new RectDrawer(this);
	text = new Text(this);
}

void Engine::AddBufferToDelete(Buffers b)
{
	DeleteBuffers.push(b);
}

void Engine::Start()
{
	GLFWwindow* window = window_->GetWindow();
	//Timer per;


	while (!glfwWindowShouldClose(window))
	{
		timer.Update();
		ClearBuffers();
		OnBeforeDraw();
		Draw();
		OnAfterDraw();
	}

	OnExit();
}

void Engine::Update()
{
}

void Engine::ClearBuffers()
{
	while (true)
	{
		if (DeleteBuffers.empty() || DeleteBuffers.front().VAO == NULL)
			return;
		DeleteBuffers.front().Clear();
		DeleteBuffers.pop();
	}
}

void Engine::Draw()
{
	for (auto& i : DrawBuffer){
		i->Draw();
	}
}

void Engine::OnBeforeDraw()
{
}

void Engine::OnAfterDraw()
{
	glfwSwapBuffers(window_->GetWindow());
	glfwPollEvents();
}

void Engine::OnExit()
{
	glfwTerminate();
}
