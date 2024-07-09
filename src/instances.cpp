#include "config.h"

using sgl::u32;
using sgl::detail::i_instance;

i_instance::i_instance() _SGL_NOTHROW
    : _handle(0) 
{}

u32 i_instance::handle() _SGL_SAFE
{
    return _handle;
}