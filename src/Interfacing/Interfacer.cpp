#include <Veritas/Orchestra/Interfacing/Interfacer.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;

Interfacer& Interfacer::set(const OutputInterface& interface) {
    outputInterfaces.emplace(interface.getName(), interface);
    return *this;
}

Interfacer& Interfacer::set(const InputInterface& interface) {
    inputInterfaces.emplace(interface.getName(), interface);
    return *this;
}

const Interfacer::InputInterfaces& Interfacer::getInputInterfaces() const { return inputInterfaces; }
const Interfacer::OutputInterfaces& Interfacer::getOutputInterfaces() const { return outputInterfaces; }
