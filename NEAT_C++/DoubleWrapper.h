#ifndef _DOUBLEWRAPPER_H

#define _DOUBLEWRAPPER_H

class DoubleWrapper
{
public:
	DoubleWrapper() : DoubleWrapper(0)
	{

	}
	DoubleWrapper(double n)
	{
		Number = n;
	}
	~DoubleWrapper()
	{

	}
	double Number = 0;
};

#endif