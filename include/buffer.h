#ifndef __buffer_h__
#define __buffer_h__

#include "instances.hpp"
#include "config.h"

namespace sgl
{
    class buffer_i : public detail::i_instance
    {
        buffer_i() = default;

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

        friend context;

        void initialize() override;
        void destroy() override;
        void bind(bool is_using = true) const override;

        void data(size32_t size, lpc data, usage_hint usage = stream_draw);
        void data(size32_t size, lpc data, size32_t offset);

        void copy(buffer_i& to);

        size32_t size() const;

        detail::instance_ref<buffer_i> ref();

        static void set_binding_target(binding_target target) noexcept;
    private:
        static binding_target current_binding_target; 
    };

    typedef detail::instance_ref<buffer_i> buffer;
}

#endif