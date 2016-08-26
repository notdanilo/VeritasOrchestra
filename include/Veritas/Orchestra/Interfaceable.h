#pragma once

#include "Message.h"

#define OutputInterface(NAME, ...) \
    template <class ...Args> \
    void NAME (Args... args) { publish(#NAME, args...); } \
    const bool NAME ## _INTERFACED = true

#define InputInterface(NAME, ...) \
    void NAME (__VA_ARGS__); \
    const bool NAME ## _INTERFACED = Interfaceable::add(#NAME, &std::remove_pointer<decltype(this)>::type::NAME)

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

                Interfaceable() {
                    on("", [=](const Message& m) { // Move it to Interfaceable constructor
                        any_method *am = methodMap[m.getName()];
                        if (am) {
                            const Message::SetOrder& order = m.getSetOrder();
                            any_args args;
                            for (auto i : order) args.push_back(m.get(i));
                            try { (*am)(args); } catch (...) { /* Wrong number of arguments */ }
                        }
                    });
                }

                ~Interfaceable() { for (auto i : methodMap) delete i.second; }
            protected:
            private:
        };
    }
}
