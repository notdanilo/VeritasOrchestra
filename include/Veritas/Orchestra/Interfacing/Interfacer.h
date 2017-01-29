#pragma once

#include "InputInterface.h"
#include "OutputInterface.h"
#include <map>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Interfacer {
                public:
                    typedef std::map<Data::String, Interfacing::InputInterface> InputInterfaces;
                    typedef std::map<Data::String, Interfacing::OutputInterface> OutputInterfaces;

                    Interfacer& set(const OutputInterface& interface);
                    Interfacer& set(const InputInterface& interface);

                    const InputInterfaces& getInputInterfaces() const;
                    const OutputInterfaces& getOutputInterfaces() const;

                private:
                    InputInterfaces inputInterfaces;
                    OutputInterfaces outputInterfaces;
            };
        }
    }
}
