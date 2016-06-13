#pragma once

#include <Veritas/Data/String.h>

#include <map>
#include <iostream>
#include <list>

namespace Veritas {
    namespace Orchestra {
        class Message {
            public:
                class Listener {
                    public:
                        ~Listener();

                        void on(const Veritas::Data::String& message, void (*callback)(const Message&), const Veritas::any& callbackData = Veritas::any());
                    private:
                        struct Callback {
                            Callback(void (*f)(const Message& m), const Veritas::any& callbackData);

                            void operator()(Message& m);

                            void (*f)(const Message& m);
                            Veritas::any callbackData;
                        };

                        typedef std::list<Callback> Callbacks;
                        typedef std::map<Veritas::Data::String, Callbacks*> CallbacksMap;
                        friend class Message;
                        void dispatch(const Veritas::Data::String& messageName) const;
                        void dispatch(const Veritas::Data::String& messageName, Message &message) const;

                        CallbacksMap map;
                };

                Message& set(const Veritas::Data::String& field, const Veritas::any& any);
                Veritas::any get(const Veritas::Data::String& field) const;

                template <class T>
                T get(const Veritas::Data::String& field) const { return any_cast<T>(get(field)); }

                template <class T>
                void dispatch(T* target, const Veritas::Data::String& name) { set("Target", target); ((Listener*) target)->dispatch(name, *this); set("Target", 0); }

            private:
                std::map<Veritas::Data::String, Veritas::any> map;
        };
    }
}
