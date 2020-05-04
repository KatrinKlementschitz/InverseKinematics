#pragma once
#include "DrawCollection.h"
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Shader;
class Engine;

class RectDrawer : public DrawCollection
{
	Engine* engine_;
	Shader* shader;
	unsigned int VAO;

public:
	struct Rect
	{
		glm::vec4 color = glm::vec4(1);
		glm::vec2 pos = glm::vec2(0);
		float width = 100;
		float height = 100;
		float rot = 0;
	};

private:
	std::vector<Rect*> rects;

public:
	RectDrawer(Engine* engine);

	void Draw() override;

	void UpdateWindowSize();

	void Add(Rect* r);

	void Remove(Rect* r);
};

