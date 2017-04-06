#pragma once

#include <Veritas/Orchestra/Messaging/Message.h>
#include "Sender.h"

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Replier {
                public:
                    Replier(const Messaging::Message& message);
                    void reply(const Messaging::Message& message = Messaging::Message()) const;
                private:
                    Sender sender;
                    uint32 requestID;
                    Messaging::Address origin;
                    Data::String interface;
            };
        }
    }
}
