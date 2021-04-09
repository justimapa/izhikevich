#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <string>
#include "random.hpp"


/**
 * @brief A pure virtual class Neuron.
 * 
 * Class defined by 4 dimensionless parameters a,b,c,d. 
 * 2 systems of ordinary differential equations of who's variables are v,u
 * and the current from the network it belongs to.
 */

class Neuron{
    public:
    /**
     * @brief Constructs a new Neuron object
     * 
     * @param type is a string indicating the type of the Neuron 
     */
    Neuron(std::string type);

    /**
     * @brief Destroys the Neuron object
     */
    virtual ~Neuron();

    /**
    * @brief Updates the parameters
    * 
    * Update is 1 simulation step. It updates the paramters of the Neuron using the correct
    * forumla, depending on the firing state of the Neuron
    */
    void update();

    /**
     * @brief Sets the current paramter
     * 
     * @param current is the new current value
     */
    void setCurrent(const double current) {_current = current;};
    
    
    /**
     * @brief Computes the noise produced by the neuron using normal distribution
     * 
     * @return The noise produced by the neuron
     */
    double noise() const {return getW() * (_RNG->normal(0,1));}; 
    /**
     * @brief Describes the firing state of the neuron
     *
     * @return true when v passes the threshold
     * @return false when v is under the threshold
     */
    bool isFiring();

    /**
     * @brief Getter for the _a, _b, _c, _d attributes
     * 
     * @return std::vector<double> {_a, _b, _c, _d}
     */
    std::vector<double> getAttributs();
    /**
     * @brief Getter for the _v, _u,  _current variables
     * 
     * @return std::vector<double> {_v, _u, _current}
     */
    std::vector<double> getVariables();

    /**
     * @brief Getter for the W of the neuron
     * 
     * @return the w of the neuron
     */
    virtual double getW() const = 0;

    /**
     * @brief Pure virtual method returning the factor of the neuron
     * 
     * @return the factor of the neuron
     */
    virtual double factor() const = 0;

    /**
     * @brief Getter for the type of the neuron
     * @return tthe type of the neuron
     */
    std::string getType() const; 


protected:
    ///describes the time scale of the recovery variable u.
    double _a; 
    ///describes the sensitivity of the recovery variable u to the subthreshold of the fluctuation of membrane potential v.
    double _b; 
    ///describes the after-spike reset value of the membrane potential v.
    double _c; 
    ///describes the after-spike reset of the recovery variable u.
    double _d; 
    ///membrane potential of the neuron
    double _v; 
    ///membrane recovery variable 
    double _u; 
    ///synaptic current delivered by surrounding neurons
    double _current; 
    ///type depending on the pattern of spiking and bursting
    std::string _type; 
};


#endif //NEURON_HPP