#include "InputNode.h"

InputNode::InputNode(int inputIndex) : InputNode(inputIndex,nodenum++)
{

}

InputNode::InputNode(int inputIndex, int nodeID) : Node(nodeID)
{
	_inputIndex = inputIndex;
	distanceFromStart = 0;
}

InputNode::~InputNode()
{

}

int InputNode::GetInputIndex()
{
	return _inputIndex;
}

Node* InputNode::GetClone()
{
	if (!_clone)
	{
		_clone = new InputNode(_inputIndex, GetNodeID());
	}
	return _clone;
}

InputNode* InputNode::GetINClone()
{
	return (InputNode*)GetClone();
}

double InputNode::GetNodeValue(double inputs[])
{
	return Memorise(inputs[_inputIndex]);
}

double InputNode::GetDistance()
{
	return 0;
}