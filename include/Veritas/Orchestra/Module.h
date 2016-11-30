#pragma once

#include <Veritas/Data/String.h>
#include <list>

namespace Veritas {
    namespace Orchestra {
        class Module {
            public:
                Module(void* address);
                Module(const Data::String& address);
                virtual ~Module();

                const Data::String& getAddress() const;
            private:
                Data::String address;
        };
    }
}
