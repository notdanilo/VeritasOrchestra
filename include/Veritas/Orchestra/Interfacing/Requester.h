#pragma once

#include "Sender.h"
#include "RequestInterface.h"
#include <Veritas/Orchestra/Computing/LocalModule.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Requester {
                public:
                    Requester(LocalModule& module);
                    Requester(LocalModule* module);
                    void request(const Data::String& interface, const Module* module, const Messaging::Message& message = Messaging::Message(), const any& context = any());
                    void request(const Data::String& interface, const Module& module, const Messaging::Message& message = Messaging::Message(), const any& context = any());

                    const LocalModule& getModule() const;
                private:
                    Sender sender;
            };
        }
    }
}
