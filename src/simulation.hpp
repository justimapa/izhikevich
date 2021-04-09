#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
#include <fstream>
#include <time.h>

/**
 * @brief The \ref Simulation class is the main class of this program.
 * 
 * It constructs the neuron \ref Network according to user-specified parameters, and runs the simulation. 
 * A \ref Simulation is made of a pointer to a network, which is a vector of pointers to neuron objects. These neurons are constructed within the constructor of the network, 
 * depending on the distribution of the different types of neuron the network will contain.
 * The time advances from 0 until it reaches T the end of simulation time. The state of the network is updated at each time by the \ref run method.
 * 
 */
class Simulation {

public : 
    /*!
        @brief Simulation takes the command-line options and extracts the following parameters from them:
        @param _nb the number of neurons in the network (an int)
        @param _p_E the percentage of activatory neurons (a double)
        @param _time the time until the end of the simulation (an int)
        @param _lambda the mean connectivity (a double)
        @param _intensity the mean intensity of the connexions (a double)
        @param _model the model chosen for the connections (a char)
        @param _delta a tunable parameter for neuron noise (a double)
        @param _type the repartition of different types of neurons (a string)
        @param _option can be turned on to generate two supplementary files with data about the neurons of the network
    */
    Simulation(int argc, char** argv);

    /*! @brief Creates a new Simulation using default parameters and an ofstream in which the output will be written.
     *  @param outfile the file for the output
     */
    Simulation(const std::string& outfile);

    /*! @brief Destroys the _network attribute
  */
    ~Simulation();

    /*!
      @brief Runs the simulation and counts the execution time
             Uses attribute _dt as one step of time for the simulation.
      @return the execution time
    */
    int run();

    /*!
      @brief Writes into the ofstream the status of each neuron in the network for every step of time.*/
    void print(int index);

    /*! @brief Writes into a new file the state of the parameters for each neuron.*/ 
    void paramPrint();

    /*! @brief Writes into a new file the _v, _u and _current of one neuron of each type present in the simulation for each step of time.
        @param file the ofstream used for print the variables 
     */ 
    void samplePrint(std::ofstream& file);

    /*! @brief Reads the line passed as argument and extracts each proportion for the given types of neuron
        @param line from which we can extract informations
        @param fs,ib,rz,lts,tc,ch are the proportions of neurons initialized to zero and are set if they match the line given in argument
        @note Throws a logic error if the sum of all proportions is greater than 1
     */ 
    void readLine(std::string& line,  double& fs, double& ib, double& rz, double& lts, double& tc, double& ch);

    /*! @brief Initialisation of the sample file
     *  @param p_E proportion of excitatory Neurons
     */
    void initializeSample(double p_E);

    /*! @brief Initialisation of the sample.
     *  @param p_FS proportion of FS Neurons
     *  @param p_LTS proportion of LTS Neurons
     *  @param p_IB proportion of IB Neurons
     *  @param p_RZ proportion of RZ Neurons
     *  @param p_TC proportion of TC Neurons
     *  @param p_CH proportion of CH Neurons
 */
    void initializeSample(double p_FS, double p_LTS, double p_IB, double p_RZ, double p_TC, double p_CH);

private :
    ///number of step of the \ref simulation
    double _time;
    ///associated network
    Network *_net;
    ///file in which the output will be printed
    std::ofstream _outfile;
    ///name of this file
    std::string _filename;
    ///saves the choice of the user for supplementary files
    bool _options;
};

#endif //SIMULATION_HPP