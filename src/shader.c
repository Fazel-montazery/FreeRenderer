#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "utils.h"

State compile_shader(GLuint shader)
{
	glCompileShader(shader);
	int  success;
	char infoLog[DEBUG_LOG_BUFFER_SIZE];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, DEBUG_LOG_BUFFER_SIZE, NULL, infoLog);
		fprintf(stderr, "[ERROR::SHADER::COMPILATION_FAILED]\n%s\n", infoLog);
		return ERROR_SHADER_COMPILATION;
	}

	return SUCCESS;
}

State create_shader(const char* path, GLuint* shader_id, GLenum shader_type)
{
	const char* ShaderSrc = load_string_from_file(path);
	if (!ShaderSrc) {
		return ERROR_FILE_LOAD;
	}
	*shader_id = glCreateShader(shader_type);
	if (*shader_id == 0) {
		free((char*) ShaderSrc);
		return ERROR_SHADER_CREATION;
	}
	glShaderSource(*shader_id, 1, &ShaderSrc, NULL);
	free((char*) ShaderSrc);

	return compile_shader(*shader_id);
}

State create_program(GLuint vertexShader, GLuint fragmentShader, GLuint* program_id)
{
	GLuint id = glCreateProgram();
	if (id == 0) return ERROR_SHADER_PROGRAM_CREATION;
        
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	int success;
	char infoLog[DEBUG_LOG_BUFFER_SIZE];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(id, DEBUG_LOG_BUFFER_SIZE, NULL, infoLog);
		fprintf(stderr, "[ERROR::SHADER_PROGRAM::LINKING_FAILED]\n%s\n", infoLog);
		return ERROR_PROGRAM_LINKING;
	}
	*program_id = id;

	return SUCCESS;
}

State create_program_from_shaders(const char* vertShaderPath, const char* fragShaderPath, GLuint* programId)
{
        GLuint vertexShader;
        if (create_shader(vertShaderPath, &vertexShader, GL_VERTEX_SHADER) != SUCCESS) {
		fprintf(stderr, "Failed to Load and Compile Vertex Shader!\n");
                return ERROR_SHADER_COMPILATION;
        }

        GLuint fragmentShader;
        if (create_shader(fragShaderPath, &fragmentShader, GL_FRAGMENT_SHADER) != SUCCESS) {
		fprintf(stderr, "Failed to Load and Compile Fragment Shader!\n");
                glDeleteShader(vertexShader);
                return ERROR_SHADER_COMPILATION;
        }

        if (create_program(vertexShader, fragmentShader, programId) != SUCCESS) {
		fprintf(stderr, "Failed to Create Shader Program!\n");
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                return ERROR_PROGRAM_LINKING;
        }
        glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return SUCCESS;
}
