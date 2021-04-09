#include "random.hpp"

Random::Random(unsigned long int s) : _seed(s) {
    if (_seed == 0) {
        std::random_device rd;
        _seed = rd();
    }
    _rng.seed(_seed);
}

double Random::exponential(const double rate) {
	std::exponential_distribution<> exp(rate);
	return exp(_rng);
}

double Random::normal(double mean, double sd) {
	std::normal_distribution<> norm(mean, sd);
	return norm(_rng);
}

int Random::poisson(double mean) {
	std::poisson_distribution<> pois(mean);
	return pois(_rng);
}

double Random::uniform_double(double lower, double upper) {
	std::uniform_real_distribution<> unif(lower, upper);
	return unif(_rng);
}

int Random::uniform_int (int lower, int upper) {
	std::uniform_int_distribution<> unif(lower, upper);
	return unif(_rng);
}

bool Random::bernoulli(double p) {
    std::bernoulli_distribution bernou(p);
    return bernou(_rng);
}