#ifndef _INPUTMEMORYNODE_H
#define _INPUTMEMORYNODE_H

#include "OutputMemoryNode.h"

class InputMemoryNode : public Node
{
	public:
		InputMemoryNode(OutputMemoryNode* outputmemorynode);
		InputMemoryNode(OutputMemoryNode* outputmemorynode, int nodeID);
		~InputMemoryNode();
		double GetNodeValue(double inputs[]);
		OutputMemoryNode* GetOutputMemoryNode();
		Node* GetClone();
		InputMemoryNode* GetIMNClone();
		double GetDistance();
	private:
		OutputMemoryNode* _outputMemoryNode;
};

#endif