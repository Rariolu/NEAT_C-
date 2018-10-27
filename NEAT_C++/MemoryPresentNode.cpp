#include "MemoryPresentNode.h"

MemoryPresentNode::MemoryPresentNode(bool stmNodesPresent) : MemoryPresentNode(stmNodesPresent,nodenum++)
{

}

MemoryPresentNode::MemoryPresentNode(bool stmNodesPresent, int nodeID) : Node(nodeID), _stmNodesPresent(stmNodesPresent)
{
	distanceFromStart = 0;
}

MemoryPresentNode::~MemoryPresentNode()
{

}

bool MemoryPresentNode::STMNodesPresent()
{
	return _stmNodesPresent;
}

double MemoryPresentNode::GetNodeValue(double input[])
{
	double val = firstIteration || (!_stmNodesPresent) ? 0 : 1;
	firstIteration = false;
	return Memorise(val);
}

Node* MemoryPresentNode::GetClone()
{
	if (!_clone)
	{
		_clone = new MemoryPresentNode(_stmNodesPresent, GetNodeID());
	}
	return _clone;
}

MemoryPresentNode* MemoryPresentNode::GetMPClone()
{
	return (MemoryPresentNode*)GetClone();
}