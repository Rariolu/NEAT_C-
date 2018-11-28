#include "Node.h"

int Node::nodenum = 0;

const int Node::maxDistance = 10000;

Node::Node() : Node(nodenum++)
{
	
}

Node::Node(int id)
{
	nodeid = id;
	SetDistance(Operations::randd->NextDouble(1,9999));
}

Node::~Node()
{
	//for (int i = 0; i < _inputs.size(); i++)
	//{
	//	if (_inputs[i])
	//	{
	//		delete _inputs[i];
	//	}
	//}
	//_inputs.clear();
}

void Node::AddInput(Node* node)
{
	if (!ContainsInput(node))
	{
		Link* link = new Link(node, this);
		AddInput(link);
		node->AddOutput(link);
	}
}

void Node::AddInput(Link* link)
{
	_inputs.push_back(link);
}

void Node::AddOutput(Node* node)
{
	if (!ContainsOutput(node))
	{
		Link* link = new Link(this, node);
		AddOutput(link);
		node->AddInput(link);
	}
}

void Node::AddOutput(Link* link)
{
	_outputs.push_back(link);
}

bool Node::ContainsInput(Node* node)
{
	for (int i = 0; i < _inputs.size(); i++)
	{
		if (_inputs[i]->GetSource() == node)
		{
			return true;
		}
	}
	return false;
}

bool Node::ContainsOutput(Node* node)
{
	for (int i = 0; i < _outputs.size(); i++)
	{
		if (_outputs[i]->GetDestination() == node)
		{
			return true;
		}
	}
	return false;
}

std::vector<Node::Link*> Node::GetInputs()
{
	return _inputs;
}

std::vector<Node::Link*> Node::GetOutputs()
{
	return _outputs;
}

void Node::CheckNodeNum(int value)
{
	if (nodenum < value)
	{
		nodenum = value + 1;
	}
}

double Node::GetNodeValue(double inputs[])
{
	if (memorised)
	{
		return memorisedOutput;
	}
	return Memorise(GetSigmoid(inputs));
	//double sum = 0;
	//for (int i = 0; i < _inputs.size(); i++)
	//{
	//	Link* link = _inputs[i];
	//	Node* source = link->GetSource();
	//	sum += source->GetNodeValue(inputs);
	//}
	//double v = Operations::Sigmoid(sum);
	//if (!IsGold())
	//{
	//	return Memorise(v);
	//}
	//return v;
}

double Node::GetSigmoid(double inputs[])
{
	//std::cout << nodeid << " creating output...distance is: "<<GetDistance() << std::endl;
	double sum = 0;
	for (int i = 0; i < _inputs.size(); i++)
	{
		Link* link = _inputs[i];
		Node* source = link->GetSource();
		sum += source->GetNodeValue(inputs);
	}
	return Operations::Sigmoid(sum);
}

void Node::ResetMemory()
{
	memorised = false;
	memorisedOutput = 0;
}

void Node::RemoveInput(Link* link)
{
	if (_inputs.size() > 0)
	{
		std::vector<Link*>::iterator iter = std::find(_inputs.begin(), _inputs.end(), link);
		if (iter != _inputs.end())
		{
			iter = _inputs.erase(iter);
		}
		else
		{
			std::cout << "From " << nodeid << " tried to delete the input of " << link->GetSource()->GetNodeID() << " but it doesn't seem to exist" << std::endl;
		}
	}
}

void Node::RemoveInput(int index)
{
	if (_inputs.size() > 0)
	{
		std::vector<Link*>::iterator iter = _inputs.begin() + (index % _inputs.size());
		if (iter != _inputs.end())
		{
			iter = _inputs.erase(iter);
		}
	}
}

void Node::RemoveOutput(Link* link)
{
	if (_outputs.size() > 0)
	{
		std::vector<Link*>::iterator iter = std::find(_outputs.begin(), _outputs.end(), link);
		if (iter != _outputs.end())
		{
			iter = _outputs.erase(iter);
		}
		else
		{
			std::cout << "From " << nodeid << " tried to delete the output of " << link->GetDestination()->GetNodeID() << " but it doesn't seem to exist" << std::endl;
		}
	}
}

void Node::RemoveOutput(int index)
{
	if (_outputs.size() > 0)
	{
		std::vector<Link*>::iterator iter = _outputs.begin() + (index%_outputs.size());
		if (iter != _outputs.end())
		{
			iter = _outputs.erase(iter);
		}
	}
}

void Node::DeleteLinks()
{
	//std::cout << "Deleting inputs for " << nodeid << std::endl;
	for (int i = 0; i < _inputs.size(); i++)
	{
		_inputs[i]->GetSource()->RemoveOutput(_inputs[i]);
		delete _inputs[i];
		_inputs[i] = NULL;
	}
	_inputs.clear();
	//std::cout << "Deleting outputs for " << nodeid << std::endl;
	for (int i = 0; i < _outputs.size(); i++)
	{
		_outputs[i]->GetDestination()->RemoveInput(_outputs[i]);
		delete _outputs[i];
		_outputs[i] = NULL;
	}
	_outputs.clear();
}

double Node::GetDistance()
{
	return distanceFromStart;
}

void Node::SetDistance(double d)
{
	distanceFromStart = d;
}

void Node::SetInputWeight(int index, double weight)
{
	if (_inputs.size() > 0)
	{
		_inputs[index % _inputs.size()]->SetWeight(weight);
	}
}

void Node::SetOutputWeight(int index, double weight)
{
	if (_outputs.size() > 0)
	{
		_outputs[index % _outputs.size()]->SetWeight(weight);
	}
}

int Node::GetNodeID()
{
	return nodeid;
}

Node* Node::GetClone()
{
	if (!_clone)
	{
		_clone = new Node(nodeid);
		_clone->SetDistance(GetDistance());
	}
	return _clone;
}

void Node::RandomiseDistance()
{
	RandomiseDistance(1, 9999);
}

void Node::RandomiseDistance(double min, double max)
{
	SetDistance(Operations::randd->NextDouble(min, max));
}

double Node::Memorise(double value)
{
	memorised = true;
	return memorisedOutput = value;
}