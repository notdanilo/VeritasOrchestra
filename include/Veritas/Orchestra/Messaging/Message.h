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

                    Message& setName(const String& name);
                    String getName() const;

                    Message& set(const String& field, const Content& content);
                    Message& set(const String& field, const String& content);
                    const Content& get(const String& field) const;

                    Buffer serialize() const;
                private:
                    Content name;
                    typedef std::map<String, Content> ContentMap;
                    ContentMap contents;
            };
        }
    }
}
