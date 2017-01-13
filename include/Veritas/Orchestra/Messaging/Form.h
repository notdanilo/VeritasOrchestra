#pragma once
#include <Veritas/Data/String.h>
#include <map>

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Content;
            class Form {
                public:
                    typedef std::map<Data::String, Content> Contents;

                    Form& set(const Data::String& field, const Content& content);
                    Form& set(const Data::String& field, Content&& content);

                    const Contents& getContents() const;

                    const Content& get(const Data::String& field) const;
                    template <class T> Form& set(const Data::String& field, T&& t) { return set(field, Content(std::forward<T>(t))); }
                private:
                    Contents contents;
            };
        }
    }
}
