#include "excitatoryNeuron.hpp"
#include <stdexcept>
#include "constants.hpp"
#include "random.hpp"
#include <iostream>


ExcitatoryNeuron::ExcitatoryNeuron(double delta, std::string type)
:Neuron(type)
{
    try {
        double lowerbound(1 - delta);
        double upperbound(1 + delta);
        if (type == "RS") {
            _a = _RS_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _RS_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _RS_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _RS_D_*_RNG->uniform_double(lowerbound, upperbound);
            }
        else if (type == "IB") {
            _a = _IB_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _IB_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _IB_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _IB_D_*_RNG->uniform_double(lowerbound, upperbound);
            }
        else if (type == "CH") {
            _a = _CH_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _CH_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _CH_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _CH_D_*_RNG->uniform_double(lowerbound, upperbound);
            }
        else if(type == "TC") {
            _a = _TC_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _TC_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _TC_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _TC_D_*_RNG->uniform_double(lowerbound, upperbound);
        }
        else if(type == "RZ") {
            _a = _RZ_A_*_RNG->uniform_double(lowerbound, upperbound);
            _b = _RZ_B_*_RNG->uniform_double(lowerbound, upperbound);
            _c = _RZ_C_*_RNG->uniform_double(lowerbound, upperbound);
            _d = _RZ_D_*_RNG->uniform_double(lowerbound, upperbound);
        }
        else {
           throw std::domain_error("The " + type + " neuron does not exist");
        }
        _v = _INIT_V_;
        _u = _b*_v;
    } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            throw e.what();
    }
}

ExcitatoryNeuron::~ExcitatoryNeuron(){

}
double ExcitatoryNeuron::getW() const{
    return _EXCIT_W_;
}
double ExcitatoryNeuron::factor()const{
    return _EXCIT_FACTOR_;
}