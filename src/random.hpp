#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <vector>
#include <algorithm>

/*!
  @brief This is a Random number class based on standard c++-11 generators. 
  It provides functions to generate random numbers.
*/

class Random {
    
public:
/*! @name Initializing
  The generator \ref rng is a Mersenne twister *mt19937* engine. 
  A seed *s>0* can be provided, by default it is seeded with a *random_device*.
*/
///@{
    Random(unsigned long int s = 0);
///@}

/*! @name Distributions
  These functions fill a given container with random numbers according to the specified distribution. 
  @note The default parameters are the standard parameters of these distributions.
*/
///@{
    template<class T> void uniform_double(T&, double lower = 0, double upper = 1);
    template<class T> void uniform_int(T&, int lower = 0, int upper = 100);
    template<class T> void normal(T&, double mean = 0, double sd = 1);
    template<class T> void exponential(T&, const double rate = 1);
    template<class T> void poisson(T&, double mean = 1);
///@}

    /**
     * @brief Uses uniform distribution for double
     * @note Default parameters are the standard parameters for this distribution
     * @return single random number
     */
    double uniform_double(double lower = 0, double upper = 1);

    /**
     * @brief Uses uniform distribution for int
     * @note Default parameters are the standard parameters for this distribution
     * @return single random number
     */
    int uniform_int(int lower = 0, int upper = 100);
    
    /**
     * @brief Uses normal distribution
     * @note Default parameters are the standard parameters for this distribution
     * @return single random number
     */
    double normal(double mean = 0, double sd = 1);
    
    /**
     * @brief Uses exponential distribution
     * @note Default parameters are the standard parameters for this distribution
     * @return single random number
     */
    double exponential(const double rate = 1);

    /**
     * @brief Uses poisson distribution
     * @note Default parameters are the standard parameters for this distribution
     * @return single random number
     */
    int poisson(double mean = 1);

    /**
     * @brief Uses bernouilli experiment
     * @note Default parameter is the standard parameter for this distribution
     * @return single random boolean
     */
    bool bernoulli(double p = 0.5);

private:
    std::mt19937 _rng;
    long int _seed;
};

template<class T> void Random::uniform_double(T &res, double lower, double upper) {
    std::uniform_real_distribution<> unif(lower, upper);
    for (auto I = res.begin(); I != res.end(); I++) *I = unif(_rng);
}

template<class T> void Random::uniform_int(T& res, int lower, int upper){
	std::uniform_int_distribution<> unif(lower, upper);
    for (auto I = res.begin(); I != res.end(); I++) *I = unif(_rng);
}

template<class T> void Random::normal(T &res, double mean, double sd) {
    std::normal_distribution<> norm(mean, sd);
    for (auto I = res.begin(); I != res.end(); I++) *I = norm(_rng);
}

template<class T> void Random::exponential(T& res, const double rate) {
	std::exponential_distribution<> exp(rate);
    for (auto I = res.begin(); I != res.end(); I++) *I = exp(_rng);
}

template<class T> void Random::poisson(T& res, double mean) {
	std::poisson_distribution<> pois(mean);
    for (auto I = res.begin(); I != res.end(); I++) *I = pois(_rng);
}

extern Random* _RNG;

#endif //RANDOM_H
