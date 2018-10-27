#include "Operations.h"

CSRand* Operations::randd = new CSRand();

//std::map<char, int> Operations::nums =
//{
//	std::pair<char,int>('0',0),
//	std::pair<char,int>('1',1),
//	std::pair<char,int>('2',2),
//	std::pair<char,int>('3',3),
//	std::pair<char,int>('4',4),
//	std::pair<char,int>('5',5),
//	std::pair<char,int>('6',6),
//	std::pair<char,int>('7',7),
//	std::pair<char,int>('8',8),
//	std::pair<char,int>('9',9)
//};

double Operations::Sigmoid(double val)
{
	return 1.0 / (1 + exp(-val));
}

double Operations::ReverseSigmoid(double val)
{
	return -log((1 / val) - 1);
}

//char* Operations::StrToCharPointer(string text)
//{
//	char* writable = new char[text.size() + 1];
//	copy(text.begin(), text.end(), writable);
//	writable[text.size()] = '\0';
//	return writable;
//}

char* Operations::StrToCharPointer(std::string text)
{
	int size = text.size();
	char* cstr = new char[size + 1];
	cstr[size] = '\0';
	for (int i = 0; i < size; i++)
	{
		cstr[i] = text[i];
	}
	return cstr;
}

bool Operations::Contains(std::string ogText, std::string excerpt)
{
	return GetIndexOFbefore(ogText, excerpt) > -1;
}

int Operations::GetIndexOFbefore(std::string ogText, std::string excerpt)
{
	int pos = ogText.find(excerpt);
	if (pos >= ogText.length())
	{
		return -1;
	}
	return pos;
}

int Operations::GetIndexOFafter(std::string ogText, std::string excerpt)
{
	int bpos = GetIndexOFbefore(ogText, excerpt);
	if (bpos > -1)
	{
		bpos += excerpt.length();
	}
	return bpos;
}

std::string Operations::GetTextBetween(std::string ogText, std::string a, std::string b)
{
	int aftera = GetIndexOFafter(ogText, a);
	int beforeb = GetIndexOFbefore(ogText, b);
	if ((aftera < 0 || beforeb < 0) || (aftera > beforeb))
	{
		return "";
	}
	int length = beforeb - aftera;
	std::string t = ogText.substr(aftera, length);
	//cout << "t " << t << endl;
	return t;
}

//bool Operations::IsNumber(char c)
//{
//	map<char, int>::iterator n = nums.find(c);
//	return n != nums.end();
//}

bool Operations::TryParse(std::string text, IntWrapper* number)
{
	bool negative = false;
	number->Number = 0;
	for (int i = 0; i < text.length(); i++)
	{
		char c = text[i];
		if (isdigit(c))//IsNumber(c))
		{
			int power = (text.length() - i) - 1;
			//int n = nums.find(c)->second;
			int n = GetNum(c);
			number->Number += n * ((int)pow(10, power));
		}
		else
		{
			if (c == '-' && i == 0)
			{
				negative = true;
			}
			else
			{
				return false;
			}
		}
	}
	if (negative)
	{
		number->Number = -number->Number;
	}
	return true;
}

bool Operations::DoubleTryParse(std::string text, DoubleWrapper* number)
{
	bool negative = false;
	number->Number = 0;
	int dpindex = GetIndexOFbefore(text, ".");
	if (dpindex < 0)
	{
		dpindex = text.length();
	}
	for (int i = 0; i < text.length(); i++)
	{
		char c = text[i];
		if (isdigit(c))//IsNumber(c))
		{
			int power;
			if (i < dpindex)
			{
				power = (dpindex - i) - 1;
			}
			else
			{
				power = ((dpindex + 1) - i) - 1;
			}
			double n = GetNum(c);
			//double n = nums.find(c)->second;
			double acc = n * pow(10, power);
			number->Number += acc;
		}
		else
		{
			if (c != '.' && c != '-')
			{
				return false;
			}
			if (c == '-' && i == 0)
			{
				negative = true;
			}
		}
	}
	if (negative)
	{
		number->Number = -number->Number;
	}
	return true;
}

std::vector<double> Operations::GetVectorFromPointerThingy(double* values, int length)
{
	std::vector<double> output;
	for (int i = 0; i < length; i++)
	{
		output.push_back(values[i]);
	}
	return output;
}

double Operations::Normalise(double x, double min, double max)
{
	return (x - min) / (max - min);
}

double Operations::Normalise(double x)
{
	return Normalise(x, MSMALL, MBIG);
}

double Operations::ReverseNormalise(double x, double min, double max)
{
	return x * (max - min) + min;
}

double Operations::ReverseNormalise(double x)
{
	return ReverseNormalise(x, MSMALL, MBIG);
}

int Operations::GetNum(char c)
{
	return c - '0';
}