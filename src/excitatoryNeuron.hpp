#ifndef EXCITATORYNEURON_HPP
#define EXCITATORYNEURON_HPP
#include "neuron.hpp"

/**
 * @brief An ExcitatoryNeuron class.
 * 
 * A type of neuron inheriting from the pure virtual class Neuron.
 */
class ExcitatoryNeuron :public Neuron
{
    public:
    /**
     * @brief Construct a new Excitatory Neuron object
     * 
     * @param delta The delta of uniform distribution determining the noise 
     * @param type A string containing the type of excitatory neuron 
     * 
     * @note type has a default parameter "RS"
     */
    ExcitatoryNeuron(double delta, std::string type = "RS");

    /**
     * @brief Destroy the Excitatory Neuron object
     */
    virtual ~ExcitatoryNeuron() override;

    /**
     * @brief A getter for the W of the Neuron
     * 
     * @return the W of the Excitatory Neuron
     */   
    virtual double getW() const override;

    /**
     * @brief A getter for the factor of the Neuron

     * @return the factor of the Excitatory Neuron
     */
    virtual double factor() const override;

};

#endif //EXCITATORYNEURON_HPP