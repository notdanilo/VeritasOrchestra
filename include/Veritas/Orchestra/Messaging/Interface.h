#pragma once
#include <functional>
#include "Message.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Interface {
                public:
                    Interface(const String& name);
                    Interface(const Interface& copy);
                    Interface(Interface&& move);
                    ~Interface();

                    Interface& operator=(const Interface& copy);
                    Interface& operator=(Interface&& move);

                    const String& getName() const;

                    Interface& require(const String& field);
                private:
                    String name;
            };
        }
    }
}
