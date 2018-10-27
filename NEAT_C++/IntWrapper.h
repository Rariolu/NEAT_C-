#ifndef _INTWRAPPER_H

#define _INTWRAPPER_H

class IntWrapper
{
public:
	IntWrapper() : IntWrapper(0)
	{

	}
	IntWrapper(int n)
	{
		Number = n;
	}
	~IntWrapper()
	{

	}
	//The number that this class is based around, the God of all values.
	int Number = 0;
};

#endif