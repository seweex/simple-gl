#include "only_compile_used_libs.h"
#include "buffer.h"

sgl::buffer_i::binding_target sgl::buffer_i::current_binding_target{sgl::buffer_i::binding_target::array_buffer};

void sgl::buffer_i::initialize()
{
    glCreateBuffers(1, &_handle);
    bind();
    glBufferData(current_binding_target, sgl::DEFAULT_BUFFER_SIZE, 0, usage_hint::static_draw);
    bind(0);
}

void sgl::buffer_i::destroy()
{
    glDeleteBuffers(1, &_handle);
    _handle = 0;
}

void sgl::buffer_i::bind(bool is_using) const
{
    glBindBuffer(current_binding_target, is_using ? _handle : 0);
}

void sgl::buffer_i::data(size32_t size, lpc data, usage_hint usage)
{
    bind();
    glBufferData(current_binding_target, size, data, usage);
    bind(0);
}

void sgl::buffer_i::data(size32_t size, lpc data, size32_t offset)
{
    bind();
    glBufferSubData(current_binding_target, offset, size, data);
    bind(0);
}

void sgl::buffer_i::copy(buffer_i &to)
{
    glBindBuffer(GL_COPY_READ_BUFFER, this->_handle);
    glBindBuffer(GL_COPY_WRITE_BUFFER, to._handle);

    size32_t size = this->size();
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

sgl::size32_t sgl::buffer_i::size() const
{
    int size = 0;

    bind();
    glGetBufferParameteriv(current_binding_target, GL_BUFFER_SIZE, &size);
    bind(0);

    return static_cast<size32_t>(size);
}

sgl::detail::instance_ref<sgl::buffer_i> sgl::buffer_i::ref()
{
    return sgl::detail::instance_ref<buffer_i>(*this);
}

void sgl::buffer_i::set_binding_target(binding_target target) noexcept
{
    current_binding_target = target;
}
