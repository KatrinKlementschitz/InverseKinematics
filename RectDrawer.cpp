#include "RectDrawer.h"
#include "Engine.h"
#include "Window.h"

RectDrawer::RectDrawer(Engine* engine)
{
	engine_ = engine;
	shader = new Shader("resources\\shader\\v.glsl", "resources\\shader\\f.glsl");

	UpdateWindowSize();

	unsigned int VBO, EBO;
	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left 
	};

	unsigned int indices[] = {
		// note that we start from 0!
		0, 1, 3, // first Triangle
		1, 2, 3 // second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RectDrawer::Draw()
{
	shader->use();

	for (int i = rects.size()-1; i >= 0; i--)
	{
		Rect* r = rects[i];
		glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(r->pos, 0));
		model = rotate(model, glm::radians(r->rot), glm::vec3(0.0f, 0.0f, 1.0f));
		model = scale(model, glm::vec3(r->width, r->height, 1));

		shader->setMat4("model", model);
		shader->setVec4("color", r->color);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void RectDrawer::UpdateWindowSize()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(engine_->window_->width), 0.0f,
	                                  static_cast<GLfloat>(engine_->window_->height));

	shader->use();
	shader->setMat4("projection", /*glm::mat4(1.0f));*/projection);
}

void RectDrawer::Add(Rect* r)
{
	rects.push_back(r);
}

void RectDrawer::Remove(Rect* r)
{
	rects.erase(std::remove(rects.begin(), rects.end(), r));
}
