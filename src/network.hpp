#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include <map>
#include <array>
#include "random.hpp"
#include "neuron.hpp"


/**
 * @brief Class that handles the Network of neurons.
 * 
 *  The Network class implements the notion of network, connecting the neurons together and handling the interactions between them.
 * It is defined by a set of neurons and associated connections with their intensities, the mean intensity of the connections and a model for the connections.
*/

class Network {

public:

  /*! @brief Basic constructor.
      Initializes the network by adding the inhibitory & excitatory neurons, given a proportion of excitatory neurons.
      Initializes connections given a model and a mean intensity for the connections.
      @param model the model of connection
      @param nb the number of neurons wanted
      @param p_E the proportion of excitatory neurons
      @param intensity the mean intensity of connection
      @param lambda the mean connectivity between neurons
      @param delta the variability around 1 of distribution of noise
    */
  Network(char model, int nb, double p_E, double intensity, double lambda, double delta);

  /*! @brief Constructor with extended neurons types.
      Initializes the network by adding the neurons, given the different types proportions.
      Initializes connection given a model and a mean intensity for the connections.
      Each type has to be explicitly given, except the RS one, which will be the rest of the neurons.
      @param model the model of connection
      @param nb the number of neurons wanted
      @param p_FS the proportion of neurons of type FS
      @param p_IB the proportion of neurons of type IB
      @param p_RZ the proportion of neurons of type RZ
      @param p_LTS the proportion of neurons of type LTS
      @param p_TC the proportion of neurons of type TC
      @param p_CH the proportion of neurons of type CH
      @param intensity the mean intensity of connection
      @param lambda the mean connectivity between neurons
      @param delta the variability around 1 for the distribution of the noise
    */
  Network(char model, int nb, double p_FS, double p_IB, double p_RZ, double p_LTS, double p_TC, double p_CH, double intensity, double lambda, double delta);

  /*! @brief Destroys all neurons in the set*/
  ~Network();

  /*! @brief Initializes the connections.
  * Determines the number of connections for each neuron, given a mean number of connections and depending on the model chosen.
  * If the model is <b>basic</b> ("b"), the number of connection for each neuron is around the mean and only few of them are making extreme numbers of connections.
  * If the model is <b>constant</b> ("c"), the number of connection for each neuron is the same and equals lambda.
  * If the model is <b>overdisplayed</b> ("o"), the number of connection for each neuron is overdisplayed, meaning that there is less and less neurons making a bigger number of connection.
  * Connects randomly the neurons 
  * @param lambda , the mean parameter used to compute how many connection a number will make.
  */
  void makeConnections(double lambda);

  /*! @brief Updates the neurons*/
  void update();

  /*! @brief Calculates the synaptic current received by the neurons, and sets the new current.
  * @param index The index of the neuron for which we want to caculate the total current.
  */
  void synapticCurrent(int index);

  /*! @brief return a list of 0 & 1, showing if a neuron is firing or not.
  * 0 = did not fire this step of time, 1 = fired this step of time
  * @return the list of neurons saying if each neuron is firing (1) or not (0)
  */
  std::vector<bool> getCurrentstatus() const;

  /*! @brief Getter for the set of the neurons in the network
    * @return the list of neurons composing the network
    */
  std::vector<Neuron*> getNet() const;

  /*! @brief Getter for the connections of neurons in the network
   *  @return the vector of connections of the network
   */
  std::vector<std::map<Neuron*, double>> getCon() const;

  /*! @brief Getter for one neuron of each type, putting it in a list  
   *  @note The order of the type of neurons is "FS", "LTS", "IB", "RZ", "TC", "CH", "RS"
   *  @note If one of the type is not present in the network, the array contains a nullptr at it position.
   *  @return An array containing each type of neuron
   */
  std::array<Neuron*,7> getNeuronsOutput() const;

  /*! @brief Getter for the Valence of a neuron
      @param index to access this specific neuron within the network 
      @return The sum of pondered intensity of current
   */
  double getValence(int index) const;

private:
  ///Collection of all neurons of the network
  std::vector<Neuron*> _network;

  ///Collection of connections to the neurons of corresponding index.
  ///The second parameter of the map is the intensity of the connection.
  std::vector<std::map<Neuron*, double>> _connections;

  ///The mean intensity for the connections
  double _intensity;

  ///The model of the simulation
  char _model;

  ///One neuron of each type present in the simulation to compute the output graphs
  ///The order is FS, LTS, IB, RZ, TC, CH, RS
  std::array<Neuron*,7> _neuronsforoutputs; 
};

#endif //NETWORK_HPP
