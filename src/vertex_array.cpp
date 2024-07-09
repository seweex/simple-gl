#include "only_compile_used_libs.h"
#include "instances.hpp"
#include "vertex_array.h"

using namespace sgl;

void vertex_array_i::initialize() _SGL_NOTHROW
{
    glGenVertexArrays(1, &_handle);
}

void vertex_array_i::destroy() _SGL_NOTHROW
{
    glDeleteVertexArrays(1, &_handle);
    _handle = 0;
}

void vertex_array_i::bind(bool is_using) _SGL_SAFE
{
    glBindVertexArray(is_using ? _handle : 0);
}

void vertex_array_i::bind_buffer(sgl::buffer &buff, size32_t index, size32_t attribut_size) _SGL_NOTHROW
{
    bind();
    buff->bind();

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, attribut_size / sizeof(float), GL_FLOAT, 0, 0, 0);

    buff->bind(0);
    bind(0);

    _binded_buffers.insert({index, buff});
}

void vertex_array_i::unbind_buffer(size32_t index) _SGL_NOTHROW
{
    bind();
    buffer(index)->bind();

    glDisableVertexAttribArray(index);

    buffer(index)->bind(0);
    bind(0);

    _binded_buffers.erase(index);
}

buffer &vertex_array_i::buffer(size32_t index)
{
    if (_binded_buffers.find(index) == _binded_buffers.end())
        throw std::out_of_range("buffer on 'index' doesn't exist");

    return _binded_buffers.at(index);
}

cref<sgl::buffer> vertex_array_i::buffer(size32_t index) const
{
    if (_binded_buffers.find(index) == _binded_buffers.end())
        throw std::out_of_range("buffer on 'index' doesn't exist");

    return _binded_buffers.at(index);
}

vertex_array vertex_array_i::ref() _SGL_NOTHROW
{
    return vertex_array(*this);
}
