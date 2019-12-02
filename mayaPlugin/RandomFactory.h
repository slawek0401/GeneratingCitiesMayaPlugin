#pragma once

#include <random>

class RandomFactory
{

	std::random_device r;
	std::default_random_engine e1;

public:
	RandomFactory();
	~RandomFactory();

	double getLogNormalValue(double mi=0, double sigma=0.25);
	double getNormalValue(double mi = 6, double sigma = 4);
	int getLinearValue(int from, int to);
};

