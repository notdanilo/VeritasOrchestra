#pragma once

#include <Veritas/Orchestra/Computing/ParallelManager.h>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class DedicatedManager : public ParallelManager {
                public:
                    Routing::MessageQueue& getMessageQueue();
                private:
                    Routing::MessageQueue messageQueue;
            };
        }
    }
}
