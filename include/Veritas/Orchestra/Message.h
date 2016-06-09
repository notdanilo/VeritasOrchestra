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

                        void on(const Veritas::Data::String& message, void (*callback)(const Message&), void* CallbackData = 0);
                    private:
                        struct Callback {
                            Callback(void (*f)(const Message& m), void* userData);

                            void operator()(Message& m);

                            void (*f)(const Message& m);
                            void* userData;
                        };

                        typedef std::list<Callback> Callbacks;
                        typedef std::map<Veritas::Data::String, Callbacks*> CallbacksMap;
                        friend class Message;
                        void dispatch(const Veritas::Data::String& messageName) const;
                        void dispatch(const Veritas::Data::String& messageName, Message &message) const;

                        CallbacksMap map;
                };

                Message& set(const Veritas::Data::String& field, void *data);
                void* get(const Veritas::Data::String& field) const;

                template <class T>
                Message& set(const Veritas::Data::String& field, T data) {
                    union void_T { T t; void* v; };
                    void_T vt; vt.t = data;
                    return set(field, vt.v);
                }

                template <class T>
                T get(const Veritas::Data::String& field) const {
                    union void_T { T t; void* v; };
                    void_T vt; vt.v = get(field);
                    return vt.t;
                }

                template <class T>
                void dispatch(T* target, const Veritas::Data::String& name) { set("Target", target); ((Listener*) target)->dispatch(name, *this); set("Target", 0); }

            private:
                std::map<Veritas::Data::String, void*> map;
        };
    }
}
