#pragma once

#include "Module.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        class LocalModule : public Module {
            public:
                LocalModule();
                ~LocalModule();

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                void virtual run();
            protected:
                void publish(const Message& message);

                template <class Arg0>
                Message& MessageArgs(Message& message, Arg0 arg0) {
                    return message.add(arg0);
                }

                template <class Arg0, class ...Args>
                Message& MessageArgs(Message& message, Arg0 arg0, Args... args) {
                    return MessageArgs(message.add(arg0), args...);
                }

                template <class ...Args>
                void publish(const Data::String& name, Args... args) {
                    Message m(name);
                    publish(MessageArgs(m, args...));
                }

                void publish(const Data::String& name) {
                    publish(Message(name));
                }

            private:
                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;
        };
    }
}
