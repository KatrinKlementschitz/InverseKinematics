#pragma once
#include <glad/glad.h>

class Buffers
{
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void Clear();
};
