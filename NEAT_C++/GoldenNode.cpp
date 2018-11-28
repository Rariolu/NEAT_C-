#include "GoldenNode.h"

std::map<Operator,int> GoldenNode::parameterCounts =
{
	std::pair<Operator,int>(ADD,2),
	std::pair<Operator,int>(SUBTRACT,2),
	std::pair<Operator,int>(DIVIDE,2),
	std::pair<Operator,int>(MULTIPLY,2),
	std::pair<Operator,int>(CONSTANT,0),
	std::pair<Operator,int>(BINARY,0)
};

std::map<Operator,std::string> GoldenNode::opValues = 
{
	std::pair<Operator,std::string>(ADD,"ADD"),
	std::pair<Operator,std::string>(SUBTRACT,"SUBTRACT"),
	std::pair<Operator,std::string>(DIVIDE,"DIVIDE"),
	std::pair<Operator,std::string>(MULTIPLY,"MULTIPLY"),
	std::pair<Operator,std::string>(CONSTANT,"CONSTANT"),
	std::pair<Operator,std::string>(BINARY,"BINARY")
};

std::map<std::string,Operator> GoldenNode::opStrings =
{
	std::pair<std::string,Operator>("ADD",ADD),
	std::pair<std::string,Operator>("SUBTRACT",SUBTRACT),
	std::pair<std::string,Operator>("DIVIDE",DIVIDE),
	std::pair<std::string,Operator>("MULTIPLY",MULTIPLY),
	std::pair<std::string,Operator>("CONSTANT",CONSTANT),
	std::pair<std::string,Operator>("BINARY",BINARY)
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

double GoldenNode::GetNodeValue(double inputs[])
{
	if (memorised)
	{
		return memorisedOutput;
	}
	int paramcount = GetParameterCount(_operator);
	std::vector<double> params;
	for (int i = 0; i < paramcount && _mainInputs.size() > 0; i++)
	{
		Link* link = _mainInputs[i%_mainInputs.size()];
		double inp = link->GetSource()->GetNodeValue(inputs);
		double weight = link->GetWeight();
		double rNorm = Operations::ReverseNormalise(inp*weight);
		params.push_back(rNorm);
	}
	double mult = GetInputs().size() > paramcount ? GetSigmoid(inputs) : 1;
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
		case BINARY:
			return mult > 0.5 ? 1 : 0;
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
		GetGoldenClone()->SetConstValue(_constValue);
	}
	return _clone;
}

GoldenNode* GoldenNode::GetGoldenClone()
{
	return (GoldenNode*)GetClone();
}

void GoldenNode::AddMainInput(Link* input)
{
	_mainInputs.push_back(input);
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
	std::map<Operator, std::string>::iterator iter = opValues.find(op);
	if (iter != opValues.end())
	{
		return iter->second;
	}
	return "NONE";
	//return opValues[op];
}

Operator GoldenNode::GetOpValue(std::string text)
{
	std::map<std::string, Operator>::iterator iter = opStrings.find(text);
	if (iter != opStrings.end())
	{
		return iter->second;
	}
	return NONE;
	//return opStrings[text];
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