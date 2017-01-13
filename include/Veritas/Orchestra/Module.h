#pragma once

#include <Veritas/Data/String.h>
#include <list>
#include "Messaging/Address.h"

namespace Veritas {
    namespace Orchestra {
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
