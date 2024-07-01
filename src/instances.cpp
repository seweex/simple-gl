#include "instances.hpp"

sgl::detail::i_instance::i_instance() : _handle(0) {}

unsigned sgl::detail::i_instance::handle() const noexcept
{
    return _handle;
}
