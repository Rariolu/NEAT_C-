#ifndef _INPUTNODE_H
#define _INPUTNODE_H

#include "Node.h"
class InputNode : public Node
{
	public:
		InputNode(int inputIndex);
		InputNode(int inputIndex, int nodeID);
		~InputNode();
		int GetInputIndex();
		Node* GetClone();
		InputNode* GetINClone();
		double GetNodeValue(double inputs[]);
		double GetDistance();
	private:
		int _inputIndex;
};

#endif