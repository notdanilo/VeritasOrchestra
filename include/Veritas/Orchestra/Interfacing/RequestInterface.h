#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class RequestInterface : public Interface {
                public:
                    typedef std::function<void(Messaging::Message& message, Messaging::Content& content)> RequestCallback;
                    typedef std::function<void(const Messaging::Message& message, const Messaging::Content& content)> ReplyCallback;
                    RequestInterface(const Data::String& name, LocalModule* module, ReplyCallback replyCallback, RequestCallback requestCallback = 0);
                    template <class C> RequestInterface(const Data::String& name, C* module, void (C::*replyCallback)(const Messaging::Message& message, const Messaging::Content& content), void (C::*requestCallback)(Messaging::Message& message, Messaging::Content& content) = 0) : RequestInterface(name, module, [module, replyCallback](const Messaging::Message& message, const Messaging::Content& content) { (module->*replyCallback)(message, content); }, [module, requestCallback](Messaging::Message& message, Messaging::Content& content) { (module->*requestCallback)(message, content); }) {}
                    RequestInterface(const RequestInterface& copy) = delete;
                    RequestInterface(RequestInterface&& move);
                    ~RequestInterface();

                    RequestInterface& operator=(const RequestInterface& copy) = delete;
                    RequestInterface& operator=(RequestInterface&& move);

                    void request(const Module& module, Messaging::Message& message) const;
                    void request(const Module& module, Messaging::Message&& message = Messaging::Message()) const;
                    void request(const Messaging::Address& address, Messaging::Message& message) const;
                    void request(const Messaging::Address& address, Messaging::Message&& message = Messaging::Message()) const;
                private:
                    RequestCallback requestCallback;
                    ReplyCallback replyCallback;
                    InputInterface inputInterface;
                    OutputInterface outputInterface;

                    void Request(Messaging::Message& message);
                    void Reply(const Messaging::Message& message);

                    uint32 requestID;
                    uint32 getRequestID();
                    typedef std::map<uint32, Messaging::Content> ContentMap;
                    ContentMap contextes;
            };
        }
    }
}
