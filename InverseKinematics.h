#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "RectDrawer.h"

class Engine;

class Segment
{
	glm::vec2 m = glm::vec2(0);
	const float deg2rad = 0.01745329251;

public:
	glm::vec2 a = glm::vec2(0);
	glm::vec2 b = glm::vec2(0);
	float length;
	float angle;

	RectDrawer::Rect rect_;

	void Calculate();

	Segment(float x, float y, float angle_, float length_);

	void Follow(glm::vec2 target);
};

class InverseKinematics
{
	std::vector<Segment*> segments_;

public:
	InverseKinematics(Engine* engine, int count, float length, float width, glm::vec4 color);

	void Update(glm::vec2 target);
};