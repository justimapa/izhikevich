#include "inhibitoryNeuron.hpp"
#include <stdexcept>
#include "constants.hpp"
#include "random.hpp"
#include <iostream>


InhibitoryNeuron::InhibitoryNeuron(double delta, std::string type)
:Neuron(type)
{
    try {
        double lowerbound(1 - delta);
        double upperbound(1 + delta);
        if (type == "LTS") {
            _a = _LTS_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _LTS_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _LTS_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _LTS_D_*_RNG->uniform_double(lowerbound, upperbound);
            }
        else if (type == "FS") {
            _a = _FS_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _FS_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _FS_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _FS_D_*_RNG->uniform_double(lowerbound, upperbound);
        }
        else {
           throw std::domain_error("The Inhibitory " + type + " neuron does not exist");
        }
        _v = _INIT_V_;
        _u = _b*_v;
    } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            throw e.what();
    }
}

InhibitoryNeuron::~InhibitoryNeuron()
{}

double InhibitoryNeuron::getW() const {
    return _INHIB_W_;
}
double InhibitoryNeuron::factor() const {
    return _INHIB_FACTOR_;
}