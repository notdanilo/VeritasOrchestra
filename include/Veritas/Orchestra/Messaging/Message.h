#pragma once

#include <Veritas/Data/String.h>
#include "Content.h"
#include "Address.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            using Data::String;
            class Message {
                public:
                    Message();
                    Message(const Message& message);
                    Message(Message&& message);
                    ~Message();

                    Message& operator=(const Message& message);
                    Message& operator=(Message&& message);

                    // temporary
                    Message& setInterface(const Data::String& interface);
                    const Data::String& getInterface() const;

                    Message& setOrigin(const Address& address);
                    Message& setDestiny(const Address& address);

                    const Address& getOrigin() const;
                    const Address& getDestiny() const;

                    Message& set(const Content& content);
                    Message& set(Content&& content);
                    const Content& getContent() const;
                    Content& getContent();
                private:
                    Address origin, destiny;
                    Content content;

                    Data::String interface;
            };
        }
    }
}
