#pragma once

#include "Message.h"

namespace Veritas {
    namespace Orchestra {
        class Interfaceable : public Message::Listener {
            public:
                template <class R, class C, class ...Args>
                bool AddInterface(const Veritas::Data::String& name, R (C::*method)(Args...)) {
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
