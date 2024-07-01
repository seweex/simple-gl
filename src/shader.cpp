#include "only_compile_used_libs.h"
#include "shader.h"

sgl::shader_i::shader_i(type tp) : _type(tp) {}

void sgl::shader_i::bind(bool) const {}

void sgl::shader_i::initialize()
{
    _handle = glCreateShader(_type);
}

void sgl::shader_i::destroy()
{
    glDeleteShader(_handle);
}

int sgl::shader_i::compile(lpcstr source) const
{
    glShaderSource(_handle, 1, &source, nullptr);
    glCompileShader(_handle);

    int success = 0;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    return success;
}

std::string sgl::shader_i::log() const
{
    char log[DEFAULT_INFO_LOG_SIZE];
    glGetShaderInfoLog(_handle, DEFAULT_INFO_LOG_SIZE, 0, log);

    return std::string{log};
}

sgl::detail::instance_ref<sgl::shader_i> sgl::shader_i::ref()
{
    return detail::instance_ref<shader_i>(*this);
}
