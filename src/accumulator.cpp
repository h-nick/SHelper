#include "include/accumulator.h"
#include <QDebug>

// Done to avoid linkage errors.
template void createACMFreqVector(_vct<int> &, _vct<int> &);
template void createACMFreqVector(_vct<double> &, _vct<double> &);

template<typename T>
void createACMFreqVector(_vct<T> & mainFreq, _vct<T> & ACMFreq)
{
	_vct<T>::const_iterator const_itr = mainFreq.begin();
	T accumulatedSum = 0;

	for(; const_itr != mainFreq.end(); const_itr++)
	{
		accumulatedSum += *const_itr;
		ACMFreq.push_back(accumulatedSum);
	}
}

// NOTE: Apparently template functions have an issue if they are called from within a class.