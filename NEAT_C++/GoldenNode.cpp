#include "GoldenNode.h"

std::map<Operator,int> GoldenNode::parameterCounts =
{
	std::pair<Operator,int>(ADD,2),
	std::pair<Operator,int>(SUBTRACT,2),
	std::pair<Operator,int>(DIVIDE,2),
	std::pair<Operator,int>(MULTIPLY,2),
	std::pair<Operator,int>(CONSTANT,0)
};

std::map<Operator,std::string> GoldenNode::opValues = 
{
	std::pair<Operator,std::string>(ADD,"ADD"),
	std::pair<Operator,std::string>(SUBTRACT,"SUBTRACT"),
	std::pair<Operator,std::string>(DIVIDE,"DIVIDE"),
	std::pair<Operator,std::string>(MULTIPLY,"MULTIPLY"),
	std::pair<Operator,std::string>(CONSTANT,"CONSTANT")
};

GoldenNode::GoldenNode(Operator op) : GoldenNode(op,nodenum++)
{

}

GoldenNode::GoldenNode(Operator op, int nodeID) : Node(nodeID)
{
	_operator = op;
}

GoldenNode::~GoldenNode()
{
	
}

double GoldenNode::GetValue(double inputs[])
{
	int paramcount = GetParameterCount(_operator);
	std::vector<double> params;
	for (int i = 0; i < paramcount && _mainInputs.size() > 0; i++)
	{
		double inp = _mainInputs[i%_mainInputs.size()]->GetSource()->GetNodeValue(inputs);
		double rNorm = Operations::ReverseNormalise(inp);
		params.push_back(rNorm);
	}
	double mult = GetInputs().size() > paramcount ? Node::GetNodeValue(inputs) : 1;
	switch (_operator)
	{
		case ADD:
			return mult*Operations::Normalise(params[0] + params[1]);
		case SUBTRACT:
			return mult*Operations::Normalise(params[0] - params[1]);
		case DIVIDE:
			return mult*Operations::Normalise(params[0] / params[1]);
		case MULTIPLY:
			return mult*Operations::Normalise(params[0] * params[1]);
		case CONSTANT:
			return mult*_constValue;
		default:
			return mult;
	}
}

Node* GoldenNode::GetClone()
{
	if (!_clone)
	{
		_clone = new GoldenNode(_operator, GetNodeID());
		GetGoldenClone()->SetMainInputs(_mainInputs);
	}
	return _clone;
}

GoldenNode* GoldenNode::GetGoldenClone()
{
	return (GoldenNode*)GetClone();
}

void GoldenNode::SetMainInputs(std::vector<Link*> mainInputs)
{
	_mainInputs = mainInputs;
}

std::vector<Node::Link*> GoldenNode::GetMainInputs()
{
	return _mainInputs;
}

Operator GoldenNode::GetOperator()
{
	return _operator;
}

double GoldenNode::ConstValue()
{
	return _constValue;
}

void GoldenNode::SetConstValue(double val)
{
	_constValue = val;
}

std::string GoldenNode::GetOpString(Operator op)
{
	return opValues[op];
}

int GoldenNode::GetParameterCount(Operator op)
{
	std::map<Operator, int>::iterator i = parameterCounts.find(op);
	if (i != parameterCounts.end())
	{
		return i->second;
	}
	return 0;
}