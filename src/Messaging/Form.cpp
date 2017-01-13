#include <Veritas/Orchestra/Messaging/Form.h>
#include <Veritas/Orchestra/Messaging/Content.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Data;

Form& Form::set(const String &field, const Content &content) {
    contents[field] = content;
    return *this;
}

Form& Form::set(const String &field, Content &&content) {
    contents[field] = std::move(content);
    return *this;
}

const Content& Form::get(const String &field) const {
    try { return contents.at(field); }
    catch (...) { return Content::Empty; }
}

const Form::Contents& Form::getContents() const { return contents; }
