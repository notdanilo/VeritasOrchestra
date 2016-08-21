#pragma once

#include <Veritas/Orchestra/Module.h>

namespace Veritas {
    namespace Orchestra {
        class RemoteModule : public Module {
            public:
                RemoteModule(const Data::String& address);
                ~RemoteModule();

                Data::String getAddress() const;
            private:
                Data::String address;
        };
    }
}
