#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>

#include <Veritas/Data/Array.h>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class RequestInterface : public Interface {
                public:
                    RequestInterface(const Data::String& name, LocalModule* module);
                    RequestInterface(const RequestInterface& copy);
                    RequestInterface(RequestInterface&& move);
                    ~RequestInterface();

                    RequestInterface& operator=(const RequestInterface& copy);
                    RequestInterface& operator=(RequestInterface&& move);

                    RequestInterface& setRequestCallback(std::function<void(Messaging::Message& message)> callback);
                    RequestInterface& setReplyCallback(std::function<void(const Messaging::Message& message)> callback);
                    template <class C> RequestInterface& setRequestCallback(void (C::*callback)(Messaging::Message& message), C *object) { return setRequestCallback([object, callback](Messaging::Message& message) { (object->*callback)(message); }); }
                    template <class C> RequestInterface& setReplyCallback(void (C::*callback)(const Messaging::Message& message), C *object) { return setReplyCallback([object, callback](const Messaging::Message& message) { (object->*callback)(message); }); }

                    void request(const Module& module, Messaging::Message& message) const;
                    void request(const Module& module, Messaging::Message&& message = Messaging::Message()) const;
                    void request(const Messaging::Address& address, Messaging::Message& message) const;
                    void request(const Messaging::Address& address, Messaging::Message&& message = Messaging::Message()) const;
                private:
                    InputInterface inputInterface;
                    OutputInterface outputInterface;
            };
        }
    }
}
