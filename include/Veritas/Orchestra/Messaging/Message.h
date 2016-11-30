#pragma once

#include <Veritas/Data/String.h>
#include <map>

#include "Content.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            using Veritas::Data::String;
            using Veritas::Data::Buffer;
            class Message {
                public:
                    Message(const Buffer& serializedMessage);
                    Message(const String& name);
                    ~Message();

                    // make it "const String&" will depend on changing "Content name"
                    String getName() const;

                    Message& setOrigin(const String& origin);
                    const String& getOrigin() const; // implement serialization/deserealization

                    Message& set(const String& field, const Content& content);
                    Message& set(const String& field, const String& content);
                    const Content& get(const String& field) const;

                    Buffer serialize() const;
                private:
                    Content name;
                    String origin;
                    typedef std::map<String, Content> ContentMap;
                    ContentMap contents;
            };
        }
    }
}
