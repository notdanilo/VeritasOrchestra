#pragma once

#include <Veritas/Orchestra/Computing/LocalModule.h>
#include <Veritas/Orchestra/Routing/Routing.h>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>

namespace Veritas {
    namespace Orchestra {
        class VO;
        namespace Computing {
            class Manager {
                public:
                    Manager();
                    Manager(const Manager& copy) = delete;
                    Manager(Manager&& move);
                    virtual ~Manager();

                    void operator=(const Manager& copy) = delete;

                    bool isRunning() const;

                    virtual Routing::MessageQueue& getMessageQueue();
                    void finalize();
                    void run();
                private:
                    volatile std::atomic<bool> isrunning;
            };
        }
    }
}
