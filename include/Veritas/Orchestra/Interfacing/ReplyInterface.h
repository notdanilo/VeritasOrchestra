#pragma once

#include <Veritas/Orchestra/Interfacing/Interfacing.h>
#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/Interfacing/Context.h>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class ReplyInterface : public Interface {
                public:
                    typedef std::function<void(const Messaging::Message& message, const Context& context)> Callback;
                    ReplyInterface(const Data::String& name, LocalModule* module, Callback callback = 0);
                    template <class C> ReplyInterface(const Data::String& name, C* module, void (C::*callback)(const Messaging::Message& message, const Context& context) = 0) : ReplyInterface(name, module, callback? [module, callback](const Messaging::Message& message, const Context& context) { (module->*callback)(message, context); } : Callback()) {}
                    ReplyInterface(const ReplyInterface& copy) = delete;
                    ReplyInterface(ReplyInterface&& move);
                    ~ReplyInterface();

                    ReplyInterface& operator=(const ReplyInterface& copy) = delete;
                    ReplyInterface& operator=(ReplyInterface&& move);

                    void reply(uint32 requestID, const Messaging::Message& message = Messaging::Message());
                private:
                    Callback callback;
                    InputInterface inputInterface;
                    OutputInterface outputInterface;

                    void Request(const Messaging::Message& message);

                    typedef std::map<uint32, Messaging::Address> AddressMap;
                    AddressMap addresses;
            };
        }
    }
}
