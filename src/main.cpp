#include <iostream>
#include "random.hpp"
#include "simulation.hpp"
#include <stdexcept>

Random* _RNG = new Random();

int main(int argc, char** argv){
    try {
        Simulation sim(argc, argv);
        sim.run();
        if (_RNG) delete _RNG;
    } catch (const std::exception &e) {
        return 1;
    }
    return 0;
}