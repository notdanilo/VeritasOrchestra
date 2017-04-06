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
                    typedef std::function<void(const Messaging::Message& message, const any& context)> Callback;
                    RequestInterface(const Data::String& name, Callback callback = 0);
                    RequestInterface(const RequestInterface& copy);
                    RequestInterface(RequestInterface&& move);
                    template <class C> RequestInterface(const Data::String& name, void (C::*callback)(const Messaging::Message& message, const any& context)) : RequestInterface(name, [callback](const Messaging::Message& message, const any& context) { (((C*) message.getDestiny().getLocalAddress())->*callback)(message, context); }) {}
                    ~RequestInterface();

                    RequestInterface& operator=(const RequestInterface& copy);
                    RequestInterface& operator=(RequestInterface&& move);
                private:
                    friend class Requester;
                    void request(const LocalModule& origin, const Module& destiny, const Messaging::Message& message, const any& context);
                    void request(const LocalModule& origin, const Module* destiny, const Messaging::Message& message, const any& context);
                    void request(const LocalModule* origin, const Module& destiny, const Messaging::Message& message, const any& context);
                    void request(const LocalModule* origin, const Module* destiny, const Messaging::Message& message, const any& context);

                    void onSet(Interfacer *interfacer);

                    Callback callback;
                    OutputInterface outputInterface;
                    InputInterface inputInterface;

                    uint32 getRequestID();
                    uint32 requestID;
                    typedef std::map<uint32, any> Contextes;
                    Contextes contextes;

                    void Reply(const Messaging::Message& message);
            };
        }
    }
}
