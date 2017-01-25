#pragma once

#include <Veritas/Data/Data.h>

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class List;
            class Form;
            class Number;
            class Address;
            class Content {
                public:
                    enum TYPE { UNKNOWN, FORM, LIST, NUMBER, TEXT, ADDRESS };

                    Content();
                    Content(const Content& copy);
                    Content(Content&& move);

                    Content(const Form& form);

                    Content(const List& array);
                    Content(const std::initializer_list<Content>& redirection);

                    Content(const Number& number);
                    Content(const int8  redirection);
                    Content(const int16 redirection);
                    Content(const int32 redirection);
                    Content(const int64 redirection);

                    Content(const uint8  redirection);
                    Content(const uint16 redirection);
                    Content(const uint32 redirection);
                    Content(const uint64 redirection);

                    Content(const float32 redirection);
                    Content(const float64 redirection);

                    template <class T> Content(const Data::Array<T>& redirection) : Content(Number(redirection)) {}

                    Content(const Data::String& string);
                    Content(const char* redirection);
                    Content(const char16_t* redirection);
                    Content(const char32_t* redirection);

                    Content(const Address& address);
                    ~Content();

                    Content& operator=(const Content& copy);
                    Content& operator=(Content&& move);

                    TYPE getType() const;

                    bool operator==(const Content& content) const;
                    bool operator!=(const Content& content) const;

                    operator Form&();
                    operator List&();
                    operator Number&();
                    operator Data::String&();
                    operator Address&();
                    operator const Form&() const;
                    operator const List&() const;
                    operator const Number&() const;
                    operator const Data::String&() const;
                    operator const Address&() const;

                    static const Content Empty;
                private:
                    TYPE type;
                    any content;
            };
        }
    }
}
