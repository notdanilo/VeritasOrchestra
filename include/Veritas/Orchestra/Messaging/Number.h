#pragma once

#include <Veritas/Data/Array.h>
#include "Encoding.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Number {
                public:
                    Number(uint8 n);
                    Number(uint16 n);
                    Number(uint32 n);
                    Number(uint64 n);

                    Number(int8 n);
                    Number(int16 n);
                    Number(int32 n);
                    Number(int64 n);

                    Number(float32 n);
                    Number(float64 n);

                    Number(Data::Array<uint8> n);
                    Number(Data::Array<uint16> n);
                    Number(Data::Array<uint32> n);
                    Number(Data::Array<uint64> n);

                    Number(Data::Array<int8> n);
                    Number(Data::Array<int16> n);
                    Number(Data::Array<int32> n);
                    Number(Data::Array<int64> n);

                    Number(Data::Array<float32> n);
                    Number(Data::Array<float64> n);
                    Number();
                    ~Number();

                    Encoding getEncoding() const;

                    Data::Buffer& getBuffer();
                    const Data::Buffer& getBuffer() const;

                    operator uint8() const;
                    operator uint16() const;
                    operator uint32() const;
                    operator uint64() const;

                    operator int8() const;
                    operator int16() const;
                    operator int32() const;
                    operator int64() const;

                    operator float32() const;
                    operator float64() const;
                private:
                    Encoding encoding;
                    Data::Buffer buffer;
            };
        }
    }
}
