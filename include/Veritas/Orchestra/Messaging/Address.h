#pragma once

#include <Veritas/Data/String.h>
#include "List.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Address {
                public:
                    Address();
                    Address(const Data::String& address);
                    Address(const void* address);
                    Address(const Address& address);
                    Address(Address&& address);
                    ~Address();

                    Address& operator=(const Address& address);
                    Address& operator=(Address&& address);

                    Address& setString(const Data::String& string);
                    const Data::String& getString() const;

                    bool operator==(const Address& address) const;

                    void* getLocalAddress() const;
                private:
                    Data::String string;
            };
        }
    }
}
