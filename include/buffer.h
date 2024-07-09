#ifndef __buffer_h__
#define __buffer_h__

#include "instances.hpp"
#include "config.h"

namespace sgl
{
    class buffer_i : public detail::i_instance
    {
        buffer_i() _SGL_NOTHROW = default;

    public:

        friend context;

        enum usage_hint : u32
        {
            static_draw = 0x88E4,
            dynamic_draw = 0x88E8,
            stream_draw = 0x88E0,

            static_copy = 0x88E6,
            dynamic_copy = 0x88EA,
            stream_copy = 0x88E2,

            static_read = 0x88E5,
            dynamic_read = 0x88E9,
            stream_read = 0x88E1
        };

        enum binding_target : u32
        {
            array_buffer = 0x8892,
            element_array_buffer = 0x8893,
            shader_storage_buffer = 0x90D2,
            uniform_buffer = 0x8A11,
            texture_buffer = 0x8C2A,
            transform_feedback_buffer = 0x8C8E
        };

        void initialize() _SGL_NOTHROW override;
        void destroy() _SGL_NOTHROW override;
        void bind(bool is_using = true) _SGL_SAFE override;

        void data(size32_t size, lpc data, usage_hint usage = stream_draw) _SGL_NOTHROW;
        void data(size32_t size, lpc data, size32_t offset) _SGL_NOTHROW;
        void copy(detail::instance_ref<buffer_i>& to) _SGL_NOTHROW;

        size32_t size() _SGL_SAFE;
        detail::instance_ref<buffer_i> ref() _SGL_NOTHROW;

        static void set_binding_target(binding_target target) _SGL_NOTHROW;

    private:

        static binding_target current_binding_target; 
    };

    typedef detail::instance_ref<buffer_i> buffer;
}

#endif