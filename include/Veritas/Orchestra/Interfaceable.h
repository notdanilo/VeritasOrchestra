#pragma once

#include "Message.h"

#define OutputInterface(NAME, ...) \
    template <class ...Args> \
    void NAME (Args... args) { LocalModule::publish(#NAME, args...); } \
    const bool NAME ## _INTERFACED = true

#define InputInterface(NAME, ...) \
    void NAME (__VA_ARGS__); \
    const bool NAME ## _INTERFACED = ([=]() { return Interfaceable::add(#NAME, &std::remove_pointer<decltype(this)>::type::NAME); })()

namespace Veritas {
    namespace Orchestra {
        class Interfaceable : public Message::Listener {
            public:
                template <class R, class C, class ...Args>
                bool add(const Veritas::Data::String& name, R (C::*method)(Args...)) {
                    methodMap[name] = new any_method(method, (C*) this);
                    return true;
                }

                typedef std::map<Veritas::Data::String, Veritas::any_method*> MethodMap;
                MethodMap methodMap;

                Interfaceable();
                ~Interfaceable();
            protected:
            private:
        };
    }
}
