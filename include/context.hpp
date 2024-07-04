#ifndef __context_h__
#define __context_h__

#include "config.h"
#include "shader.h"
#include "window.h"

namespace sgl
{
    class context
    {
        std::set<detail::i_instance*> _instances;
        
    public:

        context(u32 mj, u32 mn, bool compat);
        ~context();

        template <typename T> detail::instance_ref<typename T::type> make()
        {
            static_assert(std::is_base_of<detail::i_instance, typename T::type>::value, "invalid T type");

            typename T::type * obj = new typename T::type{};
            obj->initialize();
            _instances.insert(obj);

            return obj->ref();
        }
        window make(size32_t width, size32_t height, lpcstr title, bool resizeable);
        shader make(shader_i::type type);

        template <typename T> inline void destroy(T& obj)
        {
            static_assert(std::is_base_of<detail::i_instance, typename T::type>::value, "invalid T type");

            obj->destroy();
            _instances.erase(&obj.get());
            delete &obj.get();
        }
    };
}

#endif