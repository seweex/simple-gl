#include "only_compile_used_libs.h"
#include "shader.h"

using namespace sgl;

shader_i::shader_i(type tp) _SGL_NOTHROW 
    : _type(tp) 
{}

void shader_i::bind(bool) _SGL_SAFE {}

void shader_i::initialize() _SGL_NOTHROW
{
    _handle = glCreateShader(_type);
}

void shader_i::destroy() _SGL_NOTHROW
{
    glDeleteShader(_handle);
}

int shader_i::compile(lpcstr source) _SGL_NOTHROW
{
    glShaderSource(_handle, 1, &source, nullptr);
    glCompileShader(_handle);

    int success = 0;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    return success;
}

std::string shader_i::log() _SGL_SAFE
{
    char log[DEFAULT_INFO_LOG_SIZE];
    glGetShaderInfoLog(_handle, DEFAULT_INFO_LOG_SIZE, 0, log);

    return std::string{log};
}

shader shader_i::ref() _SGL_NOTHROW
{
    return shader(*this);
}
