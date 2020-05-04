#pragma once
#include <glad/glad.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Libraries/stb_image.h"
#include <vector>

static double modulo(double x, double N)
{
	return fmod((fmod(x, N) + N), N);
}

static float modulo(float x, float N)
{
	return fmodf((fmodf(x, N) + N), N);
}

static int modulo(int x, int N)
{
	return (x % N + N) % N;
}

static std::string FileToStr(const char* Path, const char* type = nullptr)
{
    std::string Code;
    std::ifstream File;
    File.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        File.open(Path);
        std::stringstream ShaderStream;
        ShaderStream << File.rdbuf();
        File.close();
        Code = ShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        if(type!=nullptr)
			std::cout << "ERROR::" << type << "::FILE_NOT_SUCCESFULLY_READ: " << Path << std::endl;
        else
            std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << Path << std::endl;
    }
    return Code;
}

static unsigned int create_array_texture(const char* path, int layers)
{
	unsigned int texture_atlas = 0;
    int w, h, c;
    unsigned char* data = stbi_load(path, &w, &h, &c, 3);

    glGenTextures(1, &texture_atlas);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture_atlas);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB8, 32, 32, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    delete data;
    return texture_atlas;
}

class average
{
private:
    std::vector<double>q = std::vector<double>();
    int length_;
    int pos = 0;
public:
    average(int length)
    {
        length_ = length;
        for (int i = 0; i < length; i++)
        {
            q.push_back(0);
        }
    }

    double Get(double x)
    {
        pos %= length_;
        q[pos] = x;
        pos++;

        double sum = 0;
        for (int i = 0; i < length_; i++)
        {
            sum += q[i];
        }

        return sum / length_;
    }
};