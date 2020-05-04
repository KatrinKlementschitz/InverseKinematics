#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <ft2build.h>
#include "shader_s.h"
#include "vector"
#include "DrawCollection.h"
#include FT_FREETYPE_H  

class Engine;

class Text : public DrawCollection
{
	Engine* engine_;
	Shader shader = Shader("resources\\shader\\text_v.glsl", "resources\\shader\\text_f.glsl");
	GLuint VAO, VBO;

	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

public:
	struct TextStruct
	{
		std::string text;
		GLfloat x;
		GLfloat y;
		GLfloat scale;
		glm::vec3 color;
	};

private:
	std::vector<TextStruct*> texts_;
	std::map<char, Character> Characters;

	void RenderText(TextStruct* text);

public:
	Text(Engine* engine);

	void DrawText(TextStruct* text);

	void Draw() override;

	void UpdateWindowSize();
};
