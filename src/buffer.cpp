#include "only_compile_used_libs.h"
#include "buffer.h"

using namespace sgl;
using sgl::buffer_i;
using sgl::buffer;

/* Static fields */

buffer_i::binding_target buffer_i::current_binding_target{ array_buffer };

/* Funcs */

void buffer_i::initialize() _SGL_NOTHROW
{
    glCreateBuffers(1, &_handle);
    bind();
    glBufferData(current_binding_target, DEFAULT_BUFFER_SIZE, 0, usage_hint::static_draw);
    bind(0);
}

void buffer_i::destroy() _SGL_NOTHROW
{
    glDeleteBuffers(1, &_handle);
    _handle = 0;
}

void buffer_i::bind(bool is_using) _SGL_SAFE
{
    glBindBuffer(current_binding_target, is_using ? _handle : 0);
}

void buffer_i::data(size32_t size, lpc data, usage_hint usage) _SGL_NOTHROW
{
    bind();
    glBufferData(current_binding_target, size, data, usage);
    bind(0);
}

void buffer_i::data(size32_t size, lpc data, size32_t offset) _SGL_NOTHROW
{
    bind();
    glBufferSubData(current_binding_target, offset, size, data);
    bind(0);
}

void buffer_i::copy(buffer &to) _SGL_NOTHROW
{
    glBindBuffer(GL_COPY_READ_BUFFER, this->_handle);
    glBindBuffer(GL_COPY_WRITE_BUFFER, to->_handle);

    size32_t size = this->size();
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

size32_t buffer_i::size() _SGL_SAFE
{
    int size = 0;

    bind();
    glGetBufferParameteriv(current_binding_target, GL_BUFFER_SIZE, &size);
    bind(0);

    return static_cast<size32_t>(size);
}

buffer buffer_i::ref() _SGL_NOTHROW
{
    return buffer(*this);
}

void buffer_i::set_binding_target(binding_target target) _SGL_NOTHROW
{
    current_binding_target = target;
}
