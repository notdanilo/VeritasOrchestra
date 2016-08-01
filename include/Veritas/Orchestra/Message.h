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

                        void receive(Message &message) const;

                        CallbacksMap map;
                };
                Message(const Veritas::Data::String& name);

                void setName(const Veritas::Data::String& name);
                Veritas::Data::String getName() const;

                Veritas::any getSource() const;
                Veritas::any getDestiny() const;
                Veritas::any getCallbackData() const;

                Message& set(const Veritas::Data::String& field, const Veritas::any& any);
                Veritas::any get(const Veritas::Data::String& field) const;

                template <class T>
                T get(const Veritas::Data::String& field) const { return any_cast<T>(get(field)); }

                template <class T>
                void dispatch(T* source, T* destiny) {
                    setSource(source);
                    setDestiny(destiny);

                    ((Listener*) destiny)->receive(*this);

                    setSource(Veritas::any());
                    setDestiny(Veritas::any());
                }
            private:
                Message& setSource(Veritas::any source);
                Message& setDestiny(Veritas::any destiny);
                Message& setCallbackData(Veritas::any callbackData);

                Veritas::Data::String name;
                std::map<Veritas::Data::String, Veritas::any> map;

                Veritas::any source, destiny, callbackData;
        };
    }
}
