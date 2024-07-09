#ifndef __vertex_array_h_
#define __vertex_array_h_

#include "config.h"
#include "buffer.h"

namespace sgl
{
    class vertex_array_i : public sgl::detail::i_instance
    {
        vertex_array_i() _SGL_NOTHROW = default;

        std::map<size32_t, buffer> _binded_buffers; 

    public:

        friend context;

        void initialize() _SGL_NOTHROW override;
        void destroy() _SGL_NOTHROW override;
        void bind(bool is_using = true) _SGL_SAFE override;

        void bind_buffer(buffer& buff, size32_t index, size32_t attribut_size) _SGL_NOTHROW;
        void unbind_buffer(size32_t index) _SGL_NOTHROW;

        buffer& buffer(size32_t index);
        cref<sgl::buffer> buffer(size32_t index) const;

        detail::instance_ref<vertex_array_i> ref() _SGL_NOTHROW;
    };
    
    typedef detail::instance_ref<vertex_array_i> vertex_array;
}

#endif