#ifndef SHADER_H
#define SHADER_H

#include "../include/glad/glad.h"
#include "states.h"

State compile_shader(GLuint shader);
State create_shader(const char* path, GLuint* shader_id, GLenum shader_type);
State create_program_from_shaders(const char* vertShaderPath, const char* fragShaderPath, GLuint* programId);

#endif // SHADER_H
