#ifndef _OUTPUTMEMORY_H
#define _OUTPUTMEMORY_H

#include "Node.h"
class OutputMemoryNode : public Node
{
	public:
		OutputMemoryNode();
		OutputMemoryNode(bool longterm);
		OutputMemoryNode(bool longterm, int nodeID);
		~OutputMemoryNode();
		double GetNodeValue(double inputs[]);
		double GetPreviousIterationOutput();
		void SetValue(double val);
		Node* GetClone();
		OutputMemoryNode* GetOMNClone();
	private:
		bool _longterm = false;
		double previousIterationOutput = 0;
};

#endif