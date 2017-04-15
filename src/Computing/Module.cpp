#include <Veritas/Orchestra/Computing/Module.h>
#include <Veritas/Orchestra/Computing/Manager.h>

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Data/Encoding/Encoding.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Encoding;
using namespace Messaging;

Module::Module(const Address &address) : address(address) {}
Module::Module(Address &&address) : address(std::move(address)) {}
Module::~Module() {}

const Address& Module::getAddress() const { return address; }

bool Module::operator==(const Module& module) { return getAddress() == module.getAddress(); }
