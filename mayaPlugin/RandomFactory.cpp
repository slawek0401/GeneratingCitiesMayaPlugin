#include "RandomFactory.h"



RandomFactory::RandomFactory()
{
	std::default_random_engine e2(r());
	e1 = e2;
}


RandomFactory::~RandomFactory()
{
}

double RandomFactory::getLogNormalValue(double mi, double sigma) {
	static std::random_device r;
	static std::default_random_engine e1(r());
	std::lognormal_distribution<> dist(mi, sigma);
	double random = dist(e1);
	return random;
}

double RandomFactory::getNormalValue(double mi, double sigma) {
	static std::random_device r;
	static std::default_random_engine e1(r());
	std::normal_distribution<> normal_dist(mi, sigma);
	double random = normal_dist(e1);
	return random;
}
int RandomFactory::getLinearValue(int from, int to) {
	static std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribution(from, to);
	return distribution(generator);
}