#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <vector>
template<typename T>
using _vct = std::vector<T>;

template<typename T>
void createACMFreqVector(_vct<T> & mainFreq, _vct<T> & ACMFreq);
#endif // ACCUMULATOR_H
