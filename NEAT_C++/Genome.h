#ifndef _GENOME_H
#define _GENOME_H

#include"InputNode.h"
#include"OutputNode.h"
#include"InputMemoryNode.h"
#include"OutputMemoryNode.h"
#include"MemoryPresentNode.h"
#include"GoldenNode.h"
#include<vector>
#include<map>

class Genome
{
	public:
		Genome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int id);
		~Genome();
		int ID();
		std::vector<Node*> Nodes();
		std::vector<InputNode*> InputNodes();
		std::vector<OutputNode*> OutputNodes();
		std::vector<Node*> IntermediateNodes();
		std::vector<InputMemoryNode*> LTInputMemoryNodes();
		std::vector<OutputMemoryNode*> LTOutputMemoryNodes();
		std::vector<InputMemoryNode*> STInputMemoryNodes();
		std::vector<OutputMemoryNode*> STOutputMemoryNodes();
		std::vector<GoldenNode*> GoldenNodes();
		MemoryPresentNode* MPNode();
		double GetOutput(double inputs[], int outputnum);
		void ResetMemory();
		void SetNodes(std::vector<Node*> nodes, std::vector<InputNode*> inputnodes, std::vector<OutputNode*> outputnodes, std::vector<Node*> intermediatenodes, std::vector<InputMemoryNode*> ltinputmemorynodes, std::vector<OutputMemoryNode*> ltoutputmemorynodes, std::vector<InputMemoryNode*> stinputmemorynodes, std::vector<OutputMemoryNode*> stoutputmemorynodes, std::vector<GoldenNode*> goldennodes, MemoryPresentNode* memorypresentnode);
		
		void RemoveNode(int intermediateindex);
		void CreateNode(int previousNode, int nextNode);
		void CreateIntermediateNode(int inputNode, int outputNode);
		void CreateLink(int source, int destination, double weight);
		void AlterLinkWeight(int source, int destination, double weight);
		void RemoveLink(int source, int destination);
		Genome* Clone(int genomeid);

		int GetInputCount();
		int GetOutputCount();
		int GetLTMemoryCount();
		int GetSTMemoryCount();
		int GetNodeCount();
		int GetIntermediateNodeCount();
	private:
		int _id;
		std::vector<Node*> _nodes;
		std::vector<InputNode*> _inputnodes;
		std::vector<OutputNode*> _outputnodes;
		std::vector<Node*> _intermediatenodes;
		std::vector<InputMemoryNode*> _ltinputmemorynodes;
		std::vector<OutputMemoryNode*> _ltoutputmemorynodes;
		std::vector<InputMemoryNode*> _stinputmemorynodes;
		std::vector<OutputMemoryNode*> _stoutputmemorynodes;
		std::vector<GoldenNode*> _goldennodes;
		MemoryPresentNode* _memorypresentnode;
		int _inputCount;
		int _outputCount;
		int _ltMemoryCount;
		int _stMemoryCount;
		void AddNode(Node* prevnode, Node* nextnode);
		void AddNode(Node* node);
		void RemoveNode(Node* node);
};

#endif