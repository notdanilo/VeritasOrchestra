#pragma once

#include <Veritas/Data/String.h>
#include <Veritas/Orchestra/Messaging/Address.h>
#include <list>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class Module {
                public:
                    Module(const Messaging::Address& address);
                    Module(Messaging::Address&& address);
                    virtual ~Module();

                    const Messaging::Address& getAddress() const;

                    bool operator==(const Module& module);
                private:
                    Messaging::Address address;
            };
        }
    }
}
