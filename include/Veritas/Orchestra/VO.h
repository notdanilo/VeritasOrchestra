#pragma once

#include <Veritas/Orchestra/Computing/Computing.h>

namespace Veritas {
    namespace Orchestra {
        class VO {
            public:
                static VO& getInstance();

                void run();

                Routing::MessageQueue& getMessageQueue();
                Computing::Runner& getRunner();

                void finalize();
                bool isRunning() const;
            private:
                VO();
                ~VO();

                Computing::Runner runner;

                Computing::Manager mainManager;

                typedef std::list<Computing::ParallelManager*> ParallelManagers;
                ParallelManagers parallelManagers;

                Routing::MessageQueue messageQueue;

                void setThreadNumbers(uint32 size);
                uint32 getThreadNumbers() const;
        };
    }
}
