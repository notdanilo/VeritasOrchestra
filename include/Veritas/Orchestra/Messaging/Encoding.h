#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Data/Buffer.h>

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            using Data::Buffer;
            class Encoding {
                public:
                    enum TYPE { INT, FLOAT };
                    Encoding(TYPE type, uint8 exponent);

                    TYPE getType() const;
                    uint8 getExponent() const;
                private:
                    uint8 info;
            };
        }
    }
}
