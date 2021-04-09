#ifndef INHIBITORYNEURON_HPP
#define INHIBITORYNEURON_HPP
#include "neuron.hpp"

/**
 * @brief An InhibitoryNeuron class.
 * 
 * A type of neuron inheriting from the pure virtual class Neuron.
 */
class InhibitoryNeuron :public Neuron
{
    public:
    /**
     * @brief Construct a new Inhibitory Neuron object
     * 
     * @param delta The delta of uniform distribution determining the noise
     * @param type A string containing the type of inhibitory neuron 
     * @note type has a default parameter "FS"
     */
    InhibitoryNeuron(double delta, std::string type = "FS");

    /**
     * @brief Destroy the Inhibitory Neuron object
     * 
     */
    virtual ~InhibitoryNeuron() override;

    /**
     * @brief A getter for the W of the Neuron
     * 
     * @return the W of the Inhibitory Neuron
     */

    virtual double getW() const override;

    /**
     * @brief A getter for the factor of the Neuron
     * 
     * @return the factor of the Neuron
     */
    virtual double factor() const override;

};

#endif //INHIBITORYNEURON_HPP