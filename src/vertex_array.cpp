#include "only_compile_used_libs.h"
#include "instances.hpp"
#include "vertex_array.h"

void sgl::vertex_array_i::initialize()
{
    glGenVertexArrays(1, &_handle);
}

void sgl::vertex_array_i::destroy()
{
    glDeleteVertexArrays(1, &_handle);
    _handle = 0;
}

void sgl::vertex_array_i::bind(bool is_using) const
{
    glBindVertexArray(is_using ? _handle : 0);
}

void sgl::vertex_array_i::bind_buffer(sgl::buffer &buff, size32_t index, size32_t attribut_size)
{
    bind();
    buff->bind();

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, attribut_size / sizeof(float), GL_FLOAT, 0, 0, 0);

    buff->bind(0);
    bind(0);

    _binded_buffers.insert({index, buff});
}

void sgl::vertex_array_i::unbind_buffer(size32_t index)
{
    bind();
    buffer(index)->bind();

    glDisableVertexAttribArray(index);

    buffer(index)->bind(0);
    bind(0);

    _binded_buffers.erase(index);
}

sgl::buffer &sgl::vertex_array_i::buffer(size32_t index)
{
    return _binded_buffers[index];
}

sgl::detail::instance_ref<sgl::vertex_array_i> sgl::vertex_array_i::ref()
{
    return detail::instance_ref<vertex_array_i>(*this);
}
