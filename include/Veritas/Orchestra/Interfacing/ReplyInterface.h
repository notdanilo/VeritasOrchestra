#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class ReplyInterface : public Interface {
                public:
                    typedef std::function<void(const Messaging::Message& message, Messaging::Content& context)> RequestCallback;
                    typedef std::function<void(Messaging::Message& message, const Messaging::Content& context)> ReplyCallback;
                    ReplyInterface(const Data::String& name, LocalModule* module, RequestCallback requestCallback, ReplyCallback replyCallback = 0);
                    template <class C> ReplyInterface(const Data::String& name, C* module, void (C::*requestCallback)(const Messaging::Message& message, Messaging::Content& content), void (C::*replyCallback)(Messaging::Message& message, const Messaging::Content& context) = 0) : ReplyInterface(name, module, [module, requestCallback](const Messaging::Message& message, Messaging::Content& context) { (module->*requestCallback)(message, context); }, [module, replyCallback](Messaging::Message& message, const Messaging::Content& context) { (module->*replyCallback)(message, context); }) {}
                    ReplyInterface(const ReplyInterface& copy) = delete;
                    ReplyInterface(ReplyInterface&& move);
                    ~ReplyInterface();

                    ReplyInterface& operator=(const ReplyInterface& copy) = delete;
                    ReplyInterface& operator=(ReplyInterface&& move);

                    void reply(const Messaging::Message& incoming, Messaging::Message& message) const;
                    void reply(const Messaging::Message& incoming, Messaging::Message&& message = Messaging::Message()) const;
                private:
                    RequestCallback requestCallback;
                    ReplyCallback replyCallback;
                    InputInterface inputInterface;
                    OutputInterface outputInterface;

                    void Request(const Messaging::Message& message);
                    void Reply(Messaging::Message& message);

                    typedef std::map<uint32, Messaging::Content> ContentMap;
                    ContentMap contextes;
            };
        }
    }
}
