#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/Interfacing/Context.h>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class RequestInterface : public Interface {
                public:
                    typedef std::function<void(const Messaging::Message& message, const Context& context)> Callback;
                    RequestInterface(const Data::String& name, LocalModule* module, Callback callback = 0);
                    template <class C> RequestInterface(const Data::String& name, C* module, void (C::*callback)(const Messaging::Message& message, const Context& context)) : RequestInterface(name, module, [module, callback](const Messaging::Message& message, const Context& context) { (module->*callback)(message, context); }) {}
                    RequestInterface(const RequestInterface& copy) = delete;
                    RequestInterface(RequestInterface&& move);
                    ~RequestInterface();

                    RequestInterface& operator=(const RequestInterface& copy) = delete;
                    RequestInterface& operator=(RequestInterface&& move);

                    void request(const Module& module, const Messaging::Message& message = Messaging::Message(), const Messaging::Content& content = Messaging::Content());
                    void request(const Module* module, const Messaging::Message& message = Messaging::Message(), const Messaging::Content& content = Messaging::Content());
                    void request(const Messaging::Address& address, const Messaging::Message& message = Messaging::Message(), const Messaging::Content& content = Messaging::Content());
                private:
                    Callback callback;
                    InputInterface inputInterface;
                    OutputInterface outputInterface;

                    void Request(Messaging::Message& message);
                    void Reply(const Messaging::Message& message);

                    uint32 requestID;
                    uint32 getRequestID();
                    typedef std::map<uint32, Context> ContextMap;
                    ContextMap contextes;
            };
        }
    }
}
