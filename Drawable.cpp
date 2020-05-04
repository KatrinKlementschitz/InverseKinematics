#include "Drawable.h"
#include "Engine.h"
#include "Buffers.h"

Drawable::Drawable(Engine* engine): buffers(), indices_size_(0), vertices_size_(0)
{
	engine_ = engine;
}

Drawable::~Drawable()
{
	OnDestruct();
	engine_->AddBufferToDelete(buffers);
}

void Drawable::OnDestruct()
{
}

void Drawable::Init()
{
	if (vertices_size_ == 0 || indices_size_ == 0)
		return;

	if (buffers.VAO == 0)
		glGenVertexArrays(1, &buffers.VAO);
	if (buffers.VBO == 0)
		glGenBuffers(1, &buffers.VBO);
	if (buffers.EBO == 0)
		glGenBuffers(1, &buffers.EBO);

	glBindVertexArray(buffers.VAO);

	SetData();

	canDraw = true;
	std::vector<float>().swap(vertices);
	std::vector<unsigned int>().swap(indices);
}