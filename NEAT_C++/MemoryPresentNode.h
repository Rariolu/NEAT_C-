#ifndef _MEMORYPRESENTNODE_H
#define _MEMORYPRESENTNODE_H

#include "Node.h"
class MemoryPresentNode : public Node
{
	public:
		MemoryPresentNode(bool stmNodesPresent);
		MemoryPresentNode(bool stmNodesPresent, int nodeID);
		~MemoryPresentNode();
		bool STMNodesPresent();
		double GetNodeValue(double inputs[]);
		Node* GetClone();
		MemoryPresentNode* GetMPClone();
		double GetDistance();
	private:
		bool firstIteration = true;
		bool _stmNodesPresent;
};

#endif