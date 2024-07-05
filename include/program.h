#ifndef __program_h__
#define __program_h__

#include "config.h"
#include "shader.h"

namespace sgl
{
    class program_i : public detail::i_instance
    {
        program_i() = default;

    public:

        friend context;

        void initialize() override;
        void destroy() override;
        void bind(bool is_using = true) const override;

        void attach(shader& sh);
        void detach(shader& sh);

        int link() const;
        std::string log() const;

        template<typename T>
        void uniform(lpcstr name, T data);

        template<typename T>
        void uniform(lpcstr name, size32_t size, const T* data);

        void compute(glm::i32vec3 groups, bool barrier);

        detail::instance_ref<program_i> ref();
    };

    typedef detail::instance_ref<program_i> program;
}

#endif 