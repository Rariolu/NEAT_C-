#include "InputMemoryNode.h"

InputMemoryNode::InputMemoryNode(OutputMemoryNode* outputmemorynode) : InputMemoryNode(outputmemorynode,nodenum++)
{
	
}

InputMemoryNode::InputMemoryNode(OutputMemoryNode* outputmemorynode, int nodeID) : Node(nodeID)
{
	distanceFromStart = 0;
}

InputMemoryNode::~InputMemoryNode()
{

}

double InputMemoryNode::GetNodeValue(double inputs[])
{
	return _outputMemoryNode->GetPreviousIterationOutput();
}

OutputMemoryNode* InputMemoryNode::GetOutputMemoryNode()
{
	return _outputMemoryNode;
}

Node* InputMemoryNode::GetClone()
{
	if (!_clone)
	{
		_clone = new InputMemoryNode(_outputMemoryNode->GetOMNClone(), GetNodeID());
	}
	return _clone;
}

InputMemoryNode* InputMemoryNode::GetIMNClone()
{
	return (InputMemoryNode*)GetClone();
}
double InputMemoryNode::GetDistance()
{
	return 0;
}