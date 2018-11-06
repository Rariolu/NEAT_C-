#ifndef _GOLDENNODE_H

#define _GOLDENNODE_H

enum Operator
{
	NONE,
	ADD,
	SUBTRACT,
	DIVIDE,
	MULTIPLY,
	CONSTANT
};

#include "Node.h"

class GoldenNode : public Node
{
	public:
		GoldenNode(Operator op);
		GoldenNode(Operator, int nodeID);
		~GoldenNode();
		double GetNodeValue(double inputs[]);
		Node* GetClone();
		GoldenNode* GetGoldenClone();
		void AddMainInput(Link* input);
		void SetMainInputs(std::vector<Link*> mainInputs);
		std::vector<Link*> GetMainInputs();
		Operator GetOperator();
		double ConstValue();
		void SetConstValue(double val);
		static std::string GetOpString(Operator op);
		static Operator GetOpValue(std::string text);
		bool IsGold() { return true; }
	private:
		static int GetParameterCount(Operator op);
		Operator _operator;
		static std::map<Operator, std::string> opValues;
		static std::map<std::string, Operator> opStrings;
		std::vector<Link*> _mainInputs;
		static std::map<Operator, int> parameterCounts;
		double _constValue;
};

#endif