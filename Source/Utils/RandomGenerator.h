#ifndef RandomGenerator_H
#define RandomGenerator_H

#include <random>

class RandomGenerator
{
public:
	template<class T>
	T static GetRandomNumber(T min, T max)
	{
		std::random_device randomDevice;
		std::mt19937 engine(randomDevice());
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(engine);
	}
};
#endif
