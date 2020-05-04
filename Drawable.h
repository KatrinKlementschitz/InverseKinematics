#pragma once
#include <glad/glad.h>
#include "Buffers.h"
#include <vector>

class Engine;

class Drawable
{
protected:
	Buffers buffers;
	Engine* engine_;
	int indices_size_, vertices_size_;
	std::vector<unsigned int> indices = std::vector<unsigned int>();
	std::vector<float> vertices = std::vector<float>();

public:
	bool canDraw = false;

	Drawable(Engine* engine);

protected:
	~Drawable();

public:
	virtual void OnDestruct();

	void Init();

	virtual void SetData() = 0;

	virtual void Draw() = 0;
};