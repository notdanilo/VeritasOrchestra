#pragma once

#include "Sender.h"
#include "RequestInterface.h"
#include <Veritas/Orchestra/Computing/LocalModule.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Requester {
                public:
                    Requester(Computing::LocalModule& module);
                    Requester(Computing::LocalModule* module);
                    void request(const Data::String& interface, const Computing::Module* module, const Messaging::Content& content = Messaging::Content(), const any& context = any());
                    void request(const Data::String& interface, const Computing::Module& module, const Messaging::Content& content = Messaging::Content(), const any& context = any());

                    const Computing::LocalModule& getModule() const;
                private:
                    Sender sender;
            };
        }
    }
}
