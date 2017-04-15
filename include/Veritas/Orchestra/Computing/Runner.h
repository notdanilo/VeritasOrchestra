#pragma once

#include <Veritas/Orchestra/Computing/LocalModule.h>
#include <Veritas/Orchestra/Interfacing/Publisher.h>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class Runner : public LocalModule {
                public:
                    Runner();

                    void run();
                private:
                    static const Interfacing::Interfacer& getInterfacer();
                    Interfacing::Publisher publisher;
            };
        }
    }
}
