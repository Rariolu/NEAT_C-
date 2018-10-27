#include "CSRand.h"

CSRand::CSRand() : CSRand((int)time(NULL))
{

}

CSRand::CSRand(int Seed)
{
	//cout << Seed << endl;
	Reseed(Seed);
}

void CSRand::Reseed(int Seed)
{
	//SeedArray.clear();\
		
//cout << "Seeded with value: " << Seed << endl;
	SeedArray[56] = {};
	int ii;
	int mj, mk;
	int subtraction;
	if (Seed == MSMALL)
	{
		subtraction = MBIG;
	}
	else
	{
		subtraction = abs(Seed);
	}
	mj = MSEED - subtraction;

	SeedArray[55] = mj;
	mk = 1;

	for (int i = 1; i < 55; i++)
	{
		ii = (21 * i) % 55;
		SeedArray[ii] = mk;
		mk = mj - mk;
		if (mk < 0)
		{
			mk += MBIG;
		}
		mj = SeedArray[ii];
	}
	for (int k = 1; k < 5; k++)
	{
		for (int i = 1; i < 56; i++)
		{
			SeedArray[i] -= SeedArray[1 + (i + 30) % 55];
			if (SeedArray[i] < 0)
			{
				SeedArray[i] += MBIG;
			}
		}
	}
	inext = 0;
	inextp = 21;
	Seed = 1;
}

CSRand::~CSRand()
{
	//SeedArray.clear();
}

int CSRand::InternalSample()
{
	//cout << "InternalSample called" << endl;
	int retVal;
	int locINext = inext;
	int locINextp = inextp;
	if (++locINext >= 56)
	{
		locINext = 1;
	}
	if (++locINextp >= 56)
	{
		locINextp = 1;
	}
	retVal = SeedArray[locINext] - SeedArray[locINextp];
	if (retVal == MBIG)
	{
		retVal--;
	}
	if (retVal < 0)
	{
		retVal += MBIG;
	}
	SeedArray[locINext] = retVal;
	inext = locINext;
	inextp = locINextp;
	//cout << "InternalSample ended" << endl;
	return retVal;
}

double CSRand::Sample()
{
	return InternalSample()*(1.0 / MBIG);
}

int CSRand::Next()
{
	return InternalSample();
}

double CSRand::GetSampleForLargeRange()
{
	int result = InternalSample();
	bool negative = (InternalSample() % 2 == 0);
	if (negative)
	{
		result = -result;
	}
	double d = result;
	d += MBIG - 1;
	d /= 2 * (uint32_t)MBIG - 1;
	return d;
}

int CSRand::Next(int minValue, int maxValue)
{
	if (maxValue < minValue)
	{
		int temp = minValue;
		minValue = maxValue;
		maxValue = temp;
	}
	long range = (long)maxValue - minValue;
	if (range <= (long)MBIG)
	{
		return ((int)(Sample() * range) + minValue);
	}
	return (int)((long)(GetSampleForLargeRange()*range) + minValue);
}

int CSRand::Next(int maxValue)
{
	return (int)(Sample()*maxValue);
}

int CSRand::NextWithIgnorance(int maxValue, int ignored)
{
	int next = Next(maxValue);
	if (next == ignored)
	{
		bool overmax = (ignored + 1 >= maxValue);
		bool undermin = (ignored - 1 < 0);
		if (!(overmax && undermin))
		{
			if (overmax)
			{
				next--;
			}
			else if (undermin)
			{
				next++;
			}
			else
			{
				if (Next(2) == 0)
				{
					next++;
				}
				else
				{
					next--;
				}
			}
		}
		else
		{
			std::cout << "Value cannot be modified. It is not God's will." << std::endl;
		}
	}
	return next;
}

double CSRand::NextDouble()
{
	return Sample();
}

double CSRand::NextDouble(double minValue, double maxValue)
{
	if (maxValue < minValue)
	{
		double temp = minValue;
		minValue = maxValue;
		maxValue = temp;
	}
	double range = maxValue - minValue;
	return minValue + (NextDouble()*range);
}

double CSRand::NextWeight()
{
	return 2 * NextDouble() - 1;
}

bool CSRand::NextBool()
{
	return Next(2) == 0;
}