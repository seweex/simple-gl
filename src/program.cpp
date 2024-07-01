#include "only_compile_used_libs.h"
#include "program.h"

#define UniformMatFunc(sizeX, sizeY) glUniformMatrix sizeX x sizeY f

void sgl::program_i::initialize()
{
    _handle = glCreateProgram();
}

void sgl::program_i::destroy()
{
    glDeleteProgram(_handle);
    _handle = 0;
}

void sgl::program_i::bind(bool is_using) const
{
    glUseProgram(is_using ? _handle : 0);
}

void sgl::program_i::attach(shader &sh)
{
    glAttachShader(_handle, sh->handle());
}

void sgl::program_i::detach(shader &sh)
{
    glDetachShader(_handle, sh->handle());
}

int sgl::program_i::link() const
{
    glLinkProgram(_handle);

    int success = 0;
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);

    return success;
}

std::string sgl::program_i::log() const
{
    char log[DEFAULT_INFO_LOG_SIZE];
    glGetProgramInfoLog(_handle, DEFAULT_INFO_LOG_SIZE, 0, log);

    return std::string{log};
}

void sgl::program_i::compute(glm::i32vec3 groups, bool barrier)
{
    glDispatchCompute(UNWRAP_VEC3(groups));
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

sgl::detail::instance_ref<sgl::program_i> sgl::program_i::ref()
{
    return detail::instance_ref<program_i>(*this);
}


template<>
void sgl::program_i::uniform(lpcstr name, float data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniform1f(pos, data);

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, vec2 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniform2f(pos, UNWRAP_VEC2(data));

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, vec3 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniform3f(pos, UNWRAP_VEC3(data));

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, vec4 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniform4f(pos, UNWRAP_VEC4(data));

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, mat4 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniformMatrix4fv(pos, 1, 0, &data[0][0]);

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, glm::mat3 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniformMatrix3fv(pos, 1, 0, &data[0][0]);

    bind(0);
}

template<>
void sgl::program_i::uniform(lpcstr name, glm::mat2 data)
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    glUniformMatrix2fv(pos, 1, 0, &data[0][0]);

    bind(0);
}