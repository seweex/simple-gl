#include "only_compile_used_libs.h"
#include "program.h"

using namespace sgl;

/*
    !Uniforms
    Valid types:

    int,
    int[],

    float,
    float[],

    glm::vec2,
    glm::vec3,
    glm::vec4,

    glm::mat2,
    glm::mat3,
    glm::mat4,

    glm::vec2[],
    glm::vec3[],
    glm::vec4[],

    glm::mat2[],
    glm::mat3[],
    glm::mat4[],
*/

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<int> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform1i(pos, data);

    bind(0);
    return true;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<float> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform1f(pos, data);

    bind(0);
    return true;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<vec2> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform2f(pos, UNWRAP_VEC2(data));

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<vec3> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform3f(pos, UNWRAP_VEC3(data));

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<vec4> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform4f(pos, UNWRAP_VEC4(data));

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<glm::mat2> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniformMatrix2fv(pos, 1, 0, &data[0][0]);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<glm::mat3> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniformMatrix3fv(pos, 1, 0, &data[0][0]);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, cref<glm::mat4> data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniformMatrix4fv(pos, 1, 0, &data[0][0]);

    bind(0);
    return false;
}

/* Arrays */

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const int* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform1iv(pos, size, data);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const float* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform1fv(pos, size, data);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const vec2* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform2fv(pos, size, &data[0][0]);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const vec3* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform3fv(pos, size, &data[0][0]);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const vec4* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniform4fv(pos, size, &data[0][0]);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const glm::mat3* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniformMatrix2fv(pos, size, 0, (float*)&data);

    bind(0);
    return false;
}

_SGL_TEMPLATE bool program_i::uniform(lpcstr name, size32_t size, const glm::mat4* data) _SGL_NOTHROW
{
    bind();

    u32 pos = glGetUniformLocation(_handle, name);
    if (pos == 0) return false;
    else
    glUniformMatrix3fv(pos, size, 0, (float*)&data);

    bind(0);
    return false;
}

//_SGL_TEMPLATE void program_i::uniform(lpcstr name, size32_t size, const glm::mat4* data) _SGL_NOTHROW
//{
//    bind();
//
//    u32 pos = glGetUniformLocation(_handle, name);
//    glUniformMatrix4fv(pos, size, 0, (float*)&data);
//
//    bind(0);
//}