#pragma once
#include <queue>
#include "Buffers.h"
#include "Text.h"
#include "KeyBoard.h"
#include "Timer.h"
#include "RectDrawer.h"

class Buffers;
class Window;
class DrawCollection;
class Config;

class Engine
{
public:
	KeyBoard key_board = KeyBoard(this);
	Window* window_;
	RectDrawer* rect_drawer;
	Text* text;
	Timer timer;

	Engine(Window* window);

	void AddBufferToDelete(Buffers b);

private:
	std::queue<Buffers> DeleteBuffers = std::queue<Buffers>();

public:
	std::vector<DrawCollection*> DrawBuffer = std::vector<DrawCollection*>();
	void Start();

	void Update();

	void ClearBuffers();

	void Draw();

	virtual void OnBeforeDraw();

	virtual void OnAfterDraw();

	virtual void OnExit();
};

