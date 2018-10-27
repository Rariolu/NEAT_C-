#ifndef _CSRAND_H
#define _CSRAND_H

#include<iostream>
#include<vector>
#include<time.h>
#include<math.h>

//using namespace std;

class CSRand
{
public:
	CSRand();
	CSRand(int Seed);
	~CSRand();
	virtual int Next();
	virtual int Next(int minValue, int maxValue);
	virtual int Next(int maxValue);
	virtual int NextWithIgnorance(int maxValue, int ignoredvalue);
	virtual double NextDouble();
	virtual double NextDouble(double minValue, double maxValue);
	double NextWeight();
	bool NextBool();
	void Reseed(int Seed);
protected:
	virtual double Sample();
private:
	
	const int MBIG = 2147483647;
	const int MSMALL = -2147483647;
	const int MSEED = 161803398;
	const int MZ = 0;
	int inext;
	int inextp;
	int SeedArray[56] = {};

	int InternalSample();
	double GetSampleForLargeRange();
};

#endif