#pragma once

#include <Veritas/Data/Array.h>
#include "Content.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Content;
            class List {
                public:
                    List();
                    List(uint32 size);
                    List(const std::initializer_list<Content>& il);

                    List& setSize(uint32 size);
                    uint32 getSize() const;

                    Content& operator[](uint32 index);
                    const Content& operator[](uint32 index) const;

                    bool operator==(const List& list) const;
                private:
                    Data::Array<Content> list;
            };
        }
    }
}
