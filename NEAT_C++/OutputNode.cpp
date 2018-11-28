#include "OutputNode.h"

OutputNode::OutputNode() : OutputNode(nodenum++)
{

}

OutputNode::OutputNode(int nodeID) : Node(nodeID)
{
	distanceFromStart = maxDistance;
}

OutputNode::~OutputNode()
{

}

Node* OutputNode::GetClone()
{
	if (!_clone)
	{
		_clone = new OutputNode(GetNodeID());
	}
	return _clone;
}

OutputNode* OutputNode::GetONNode()
{
	return (OutputNode*)GetClone();
}

double OutputNode::GetDistance()
{
	return maxDistance;
}

void OutputNode::Train(double inputs[], double desiredOutput)
{
	std::vector<Link*> inputLinks = GetInputs();
	double output = GetNodeValue(inputs);
	double error = desiredOutput - output;
	double delta = error * output;
	for (int i = 0; i < inputLinks.size(); i++)
	{
		inputLinks[i]->Train(delta, inputs);
	}
}