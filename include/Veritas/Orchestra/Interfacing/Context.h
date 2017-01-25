#pragma once

#include "../Messaging/Content.h"

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Context { // Better identification. It serves only for ReqRep.
                public:
                    Context(uint32 requestID);
                    Context(const Context& copy);
                    Context(Context&& move);

                    Context& operator=(const Context& copy);
                    Context& operator=(Context&& move);

                    uint32 getRequestID() const;

                    void setContent(const Messaging::Content& content);
                    void setContent(Messaging::Content&& content);
                    const Messaging::Content& getContent() const;
                private:
                    uint32 requestID;
                    Messaging::Content content;
            };
        }
    }
}
