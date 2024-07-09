#include "only_compile_used_libs.h"
#include "program.h"

using namespace sgl;

void program_i::initialize() _SGL_NOTHROW
{
    _handle = glCreateProgram();
}

void program_i::destroy() _SGL_NOTHROW
{
    glDeleteProgram(_handle);
    _handle = 0;
}

void program_i::bind(bool is_using) _SGL_SAFE
{
    glUseProgram(is_using ? _handle : 0);
}

void program_i::attach(shader &sh) _SGL_NOTHROW
{
    glAttachShader(_handle, sh->handle());
}

void program_i::detach(shader &sh) _SGL_NOTHROW
{
    glDetachShader(_handle, sh->handle());
}

int program_i::link() _SGL_SAFE
{
    glLinkProgram(_handle);

    int success = 0;
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);

    return success;
}

std::string program_i::log() _SGL_SAFE
{
    char log[DEFAULT_INFO_LOG_SIZE];
    glGetProgramInfoLog(_handle, DEFAULT_INFO_LOG_SIZE, 0, log);

    return std::string{log};
}

void program_i::compute(glm::i32vec3 groups, bool barrier) _SGL_NOTHROW
{
    glDispatchCompute(UNWRAP_VEC3(groups));
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

program sgl::program_i::ref() _SGL_NOTHROW
{
    return program(*this);
}
