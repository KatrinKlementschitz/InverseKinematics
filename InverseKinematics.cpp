#include "InverseKinematics.h"
#include "Engine.h"
#include "HSV.h"

void Segment::Calculate()
{
	float val = length / 2.0f;
	float rad = glm::radians(angle);
	float xi = cos(rad);
	float yi = sin(rad);

	m = glm::vec2(a.x + xi * val, a.y + yi * val);

	b = glm::vec2(m.x + xi * val, m.y + yi * val);

	rect_.pos = m;
	rect_.rot = angle;
	rect_.width = length;
}

Segment::Segment(float x, float y, float angle_, float length_)
{
	angle = angle_;
	length = length_;

	a.x = x;
	a.y = y;

	Calculate();
}

void Segment::Follow(glm::vec2 target)
{
	glm::vec2 dir = target - a;
	angle = atan2(dir.y, dir.x) / deg2rad;
	dir = glm::normalize(dir);
	dir *= length;
	a = target - dir;
	Calculate();
}

InverseKinematics::InverseKinematics(Engine* engine, int count, float length, float width, glm::vec4 color)
{
	segments_ = std::vector<Segment*>();

	for (int i = 0; i < count; i++)
	{
		Segment* s = new Segment(400, 400, 0, length);
		s->rect_.height = width;
		hsv HSV;
		HSV.s = 1;
		HSV.v = 1;
		double w = (double)(i % 200) / 200.0;
		HSV.h = w * 360.0;
		rgb RGB = hsv2rgb(HSV);
		color.r = RGB.r;
		color.g = RGB.g;
		color.b = RGB.b;
		s->rect_.color = color;
		segments_.push_back(s);
		engine->rect_drawer->Add(&s->rect_);
	}
}

void InverseKinematics::Update(glm::vec2 target)
{
	Segment* seg = nullptr;
	for (auto& segment : segments_)
	{
		if (seg != nullptr)
			segment->Follow(seg->a);
		else
			segment->Follow(target);
		seg = segment;
	}
}
