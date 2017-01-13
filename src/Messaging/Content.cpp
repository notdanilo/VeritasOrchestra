#include <Veritas/Orchestra/Messaging/Content.h>
#include <Veritas/Orchestra/Messaging/List.h>
#include <Veritas/Orchestra/Messaging/Number.h>
#include <Veritas/Orchestra/Messaging/Form.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Data;

const Content Content::Empty;

Content::Content() : type(UNKNOWN) {}
Content::Content(const Content &copy) : content(copy.content), type(copy.type) {}
Content::Content(Content&& move) : content(std::move(move.content)), type(move.type) { move.type = UNKNOWN; }

Content::Content(const Form& content) : content(content), type(FORM) {}

Content::Content(const List& content) : content(content), type(LIST) {}
Content::Content(const std::initializer_list<Content> &redirection) : Content(List(redirection)) {}

Content::Content(const Number& content) : content(content), type(NUMBER) {}
Content::Content(const int8  redirection) : Content(Number(redirection)) {}
Content::Content(const int16 redirection) : Content(Number(redirection)) {}
Content::Content(const int32 redirection) : Content(Number(redirection)) {}
Content::Content(const int64 redirection) : Content(Number(redirection)) {}

Content::Content(const uint8  redirection) : Content(Number(redirection)) {}
Content::Content(const uint16 redirection) : Content(Number(redirection)) {}
Content::Content(const uint32 redirection) : Content(Number(redirection)) {}
Content::Content(const uint64 redirection) : Content(Number(redirection)) {}

Content::Content(const float32 redirection) : Content(Number(redirection)) {}
Content::Content(const float64 redirection) : Content(Number(redirection)) {}

Content::Content(const String& content) : content(content), type(TEXT) {}
Content::Content(const char* redirection) : Content(String(redirection)) {}
Content::Content(const char16_t* redirection) : Content(String(redirection)) {}
Content::Content(const char32_t* redirection) : Content(String(redirection)) {}
Content::~Content() {}

Content::operator Form&() { return any_cast<Form>(content); }
Content::operator List&() { return any_cast<List>(content); }
Content::operator Number&() { return any_cast<Number>(content); }
Content::operator String&() { return any_cast<String>(content); }
Content::operator const Form&() const { return any_cast<Form>(content); }
Content::operator const List&() const { return any_cast<List>(content); }
Content::operator const Number&() const { return any_cast<Number>(content); }
Content::operator const String&() const { return any_cast<String>(content); }

Content& Content::operator=(const Content& content) {
    this->content = content.content;
    this->type = content.type;
    return *this;
}

Content& Content::operator=(Content&& content) {
    this->content = std::move(content.content);
    this->type = std::move(content.type);
    content.type = UNKNOWN;
    return *this;
}

Content::TYPE Content::getType() const { return type; }
