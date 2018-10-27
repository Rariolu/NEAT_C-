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