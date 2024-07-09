#ifndef __program_h__
#define __program_h__

#include "config.h"
#include "shader.h"

namespace sgl
{
    class program_i : public detail::i_instance
    {
        program_i() _SGL_NOTHROW = default;

    public:

        friend context;

        void initialize() _SGL_NOTHROW override;
        void destroy() _SGL_NOTHROW override;
        void bind(bool is_using = true) _SGL_SAFE override;

        void attach(shader& sh) _SGL_NOTHROW;
        void detach(shader& sh) _SGL_NOTHROW;

        int link() _SGL_SAFE;
        std::string log() _SGL_SAFE;

        template<typename T>
        bool uniform(lpcstr name, cref<T> data) _SGL_NOTHROW;
        template<typename T>
        bool uniform(lpcstr name, size32_t size, const T* data) _SGL_NOTHROW;

        void compute(glm::i32vec3 groups, bool barrier) _SGL_NOTHROW;

        detail::instance_ref<program_i> ref() _SGL_NOTHROW;
    };

    typedef detail::instance_ref<program_i> program;
}

#endif 