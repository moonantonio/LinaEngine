/*
Author: Inan Evin
www.inanevin.com

MIT License

Lina Engine, Copyright (c) 2018 Inan Evin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

4.0.30319.42000
10/15/2018 7:20:01 PM

*/

#include "pch.h"
#include "Rendering/Lina_Shader.h"  


void Lina_Shader::AddVertexShader(const char* text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void Lina_Shader::AddGeometryShader(const char* text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void Lina_Shader::AddFragmentShader(const char* text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void Lina_Shader::AddProgram(const char* text, int type)
{
	unsigned int shader = glCreateShader(type);

	if (shader == 0)
	{
		Lina_Console cons;
		cons.AddConsoleMsg("Shader Program Insert Failed!", Lina_Console::MsgType::Error, "Shader");
		return;
	}

	// Init shader source & compile the text.
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	CheckError(shader, GL_COMPILE_STATUS);

	// Attach said shader to the program.
	glAttachShader(shader, program);

}


void Lina_Shader::CompileShader()
{
	// Link the program.
	glLinkProgram(program);

	// Check for errors.
	CheckError(program, GL_LINK_STATUS);

	// Validate program.
	glValidateProgram(program);
}

void Lina_Shader::CheckError(unsigned int ID, int type)
{
	int success;
	char infoLog[1024];

	glGetShaderiv(ID, type, &success);

	if (!success)
	{
		glGetShaderInfoLog(ID, 1024, NULL, infoLog);
		std::cout << "Shader ERR:" << type << " Shader\n" << infoLog << "--------\n" << std::endl;
	}
}
