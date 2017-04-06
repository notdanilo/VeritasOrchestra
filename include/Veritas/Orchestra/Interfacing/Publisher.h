#pragma once
#include <Veritas/Orchestra/Interfacing/Sender.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Publisher : protected Sender {
                public:
                    Publisher(const LocalModule& module);
                    Publisher(const LocalModule* module);

                    void publish(const Data::String& interface, const Messaging::Message& message = Messaging::Message()) const;
            };
        }
    }
}
