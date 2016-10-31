#pragma once

#include <Veritas/Data/Data.h>
#include "Encoding.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            using Data::Array;
            using Data::Buffer;
            using Data::String;
            class Content {
                public:
                    Content();
                    Content(const int8 content);
                    Content(const int16 content);
                    Content(const int32 content);
                    Content(const int64 content);
                    Content(const float32 content);
                    Content(const float64 content);
                    Content(const String& content);

                    Content(const Buffer& serializedContent);
                    Content(const Buffer& buffer, const Encoding& encoding);
                    Content(const Array<int8>& content);
                    Content(const Array<int16>& content);
                    Content(const Array<int32>& content);
                    Content(const Array<int64>& content);
                    Content(const Array<float32>& content);
                    Content(const Array<float64>& content);

                    Encoding getEncoding() const;
                    uint32 getElements() const;

                    int8 getInt8(uint32 index = 0) const;
                    int16 getInt16(uint32 index = 0) const;
                    int32 getInt32(uint32 index = 0) const;
                    int64 getInt64(uint32 index = 0) const;
                    float32 getFloat32(uint32 index = 0) const;
                    float64 getFloat64(uint32 index = 0) const;
                    String getString() const;

                    Buffer& getBuffer();
                    const Buffer& getBuffer() const;

                    uint32 getSerialSize() const;
                    Buffer serialize() const;
                private:
                    friend class Message;
                    static Content Empty;

                    Encoding encoding;
                    Data::Buffer buffer;
            };
        }
    }
}
