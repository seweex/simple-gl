#ifndef __vertex_array_h_
#define __vertex_array_h_

#include "config.h"
#include "buffer.h"

namespace sgl
{
    class vertex_array_i : public sgl::detail::i_instance
    {
        vertex_array_i() = default;

        std::map<size32_t, buffer> _binded_buffers; 

    public:

        void initialize() override;
        void destroy() override;
        void bind(bool is_using = true) const override;

        void bind_buffer(buffer& buff, size32_t index, size32_t vertex_size);
        void unbind_buffer(size32_t index);
        buffer& buffer(size32_t index);

        vertex_array ref();
    };
}

#endif