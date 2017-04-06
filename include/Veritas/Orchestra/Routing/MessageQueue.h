#pragma once

#include "../Messaging/Message.h"

#include <mutex>
#include <queue>
#include <quadmath.h>

#warning What if a message event generates more than one message and then it bloats the MQ?

namespace Veritas {
    namespace Orchestra {
        namespace Routing {
            class MessageQueue {
                public:
                    uint32 getAmmount() const;

                    void receive(const Messaging::Message& message);
                    void receive(Messaging::Message&& message);
                    Messaging::Message consume();
                private:
                    typedef std::queue<Messaging::Message> Queue;
                    std::mutex mutex;
                    Queue queue;
            };
        }
    }
}
