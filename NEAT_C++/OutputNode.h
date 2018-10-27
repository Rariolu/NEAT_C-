#ifndef _OUTPUTNODE_H
#define _OUTPUTNODE_H

#include "Node.h"
class OutputNode : public Node
{
	public:
		OutputNode();
		OutputNode(int nodeID);
		~OutputNode();
		Node* GetClone();
		OutputNode* GetONNode();
};

#endif