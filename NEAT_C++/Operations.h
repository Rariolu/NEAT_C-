#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include <stdlib.h> /* srand, rand */
#include <time.h>   
#include <math.h>
#include<map>
#include"CSRand.h"
//#include"ConsoleManager.h"
#include"IntWrapper.h"
#include"DoubleWrapper.h"
#include<vector>//Remove when possible
//using namespace std;
#include"ConsoleManager.h"

class Operations
{
	public:
		//This version is kinda shitty but it'll do for now. Remember to delete pointer afterwards.
		static char* StrToCharPointer(std::string text);
		static double Sigmoid(double val);
		static double ReverseSigmoid(double val);
		static bool Contains(std::string ogText, std::string excerpt);
		static int GetIndexOFbefore(std::string ogText, std::string excerpt);
		static int GetIndexOFafter(std::string ogText, std::string excerpt);
		static std::string GetTextBetween(std::string ogText, std::string a, std::string b);
		static bool TryParse(std::string text, IntWrapper* number);
		static bool DoubleTryParse(std::string text, DoubleWrapper* number);
		//static bool IsNumber(char c);
		static std::vector<double> GetVectorFromPointerThingy(double* values, int length);
		static double Normalise(double x, double min, double max);
		static double Normalise(double x);
		static double ReverseNormalise(double x, double min, double max);
		static double ReverseNormalise(double x);
		//static int num;
		static CSRand* randd;
		//static std::map<char, int> nums;
		static int GetNum(char c);

	private:
		static const int MBIG = 2147483647;
		static const int MSMALL = -2147483647;
};

#endif