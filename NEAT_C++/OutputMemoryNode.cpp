#include "OutputMemoryNode.h"

OutputMemoryNode::OutputMemoryNode() : OutputMemoryNode(false)
{

}

OutputMemoryNode::OutputMemoryNode(bool longterm) : OutputMemoryNode(longterm,nodenum++)
{

}

OutputMemoryNode::OutputMemoryNode(bool longterm, int nodeID) : Node(nodeID)
{
	_longterm = longterm;
	distanceFromStart = maxDistance;
}

OutputMemoryNode::~OutputMemoryNode()
{

}

double OutputMemoryNode::GetNodeValue(double inputs[])
{
	return previousIterationOutput = Memorise(Node::GetNodeValue(inputs));
}

double OutputMemoryNode::GetPreviousIterationOutput()
{
	return previousIterationOutput;
}

void OutputMemoryNode::SetValue(double val)
{
	previousIterationOutput = val;
}

Node* OutputMemoryNode::GetClone()
{
	if (!_clone)
	{
		OutputMemoryNode* clonetemp = new OutputMemoryNode(_longterm, GetNodeID());
		if (_longterm)
		{
			clonetemp->SetValue(previousIterationOutput);
		}
		_clone = clonetemp;
	}
	return _clone;
}

OutputMemoryNode* OutputMemoryNode::GetOMNClone()
{
	return (OutputMemoryNode*)GetClone();
}