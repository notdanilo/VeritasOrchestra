#include <Veritas/Orchestra/Module.h>
#include <Veritas/Orchestra/ModuleManager.h>

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Data/Encoding/Encoding.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Encoding;

Module::Module(void *address) : Module(Base16().encode(&address, sizeof(address))) {}
Module::Module(const String &address) : address(address) {}
Module::~Module() {}

const String& Module::getAddress() const { return address; }
