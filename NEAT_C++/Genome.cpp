#include "Genome.h"

Genome::Genome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int id)
{

}

Genome::~Genome()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		delete _nodes[i];
	}
}

int Genome::ID()
{
	return _id;
}

std::vector<Node*> Genome::Nodes()
{
	return _nodes;
}

std::vector<InputNode*> Genome::InputNodes()
{
	return _inputnodes;
}
std::vector<OutputNode*> Genome::OutputNodes()
{
	return _outputnodes;
}
std::vector<Node*> Genome::IntermediateNodes()
{
	return _intermediatenodes;
}
std::vector<InputMemoryNode*> Genome::LTInputMemoryNodes()
{
	return _ltinputmemorynodes;
}
std::vector<OutputMemoryNode*> Genome::LTOutputMemoryNodes()
{
	return _ltoutputmemorynodes;
}
std::vector<InputMemoryNode*> Genome::STInputMemoryNodes()
{
	return _stinputmemorynodes;
}
std::vector<OutputMemoryNode*> Genome::STOutputMemoryNodes()
{
	return _stoutputmemorynodes;
}
std::vector<GoldenNode*> Genome::GoldenNodes()
{
	return _goldennodes;
}
MemoryPresentNode* Genome::MPNode()
{
	return _memorypresentnode;
}
//std::map<int, Node*> Genome::GetNodeMap()
//{
//	//return _nodemap;
//}

double Genome::GetOutput(double inputs[], int outputnum)
{
	if (_outputnodes.size() < 1)
	{
		return 0;
	}
	return _outputnodes[outputnum%_outputCount]->GetNodeValue(inputs);
}

void Genome::ResetMemory()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->ResetMemory();
	}
}

void Genome::SetNodes(std::vector<Node*> nodes, std::vector<InputNode*> inputnodes, std::vector<OutputNode*> outputnodes, std::vector<Node*> intermediatenodes, std::vector<InputMemoryNode*> ltinputmemorynodes, std::vector<OutputMemoryNode*> ltoutputmemorynodes, std::vector<InputMemoryNode*> stinputmemorynodes, std::vector<OutputMemoryNode*> stoutputmemorynodes, std::vector<GoldenNode*> goldennodes, MemoryPresentNode* memorypresentnode)
{

}



void Genome::RemoveNode(int intermediateindex)
{
	if (_intermediatenodes.size() > 0)
	{
		Node* n = _intermediatenodes[intermediateindex%_intermediatenodes.size()];
		RemoveNode(n);
	}
}

void Genome::CreateNode(int previousNode, int nextNode)
{
	int prevNodeIndex = previousNode % _nodes.size();
	int nextNodeIndex = nextNode % _nodes.size();
	if (prevNodeIndex != nextNodeIndex)
	{
		AddNode(_nodes[prevNodeIndex], _nodes[nextNodeIndex]);
	}
}

void Genome::CreateLink(int source, int destination, double weight)
{

}

void Genome::AlterLinkWeight(int source, int destination, double weight)
{
	Node* s = _nodes[source%_nodes.size()];
	Node* d = _nodes[destination%_nodes.size()];
	std::vector<Node::Link*> s_outputs = s->GetOutputs();
}

Genome* Genome::Clone(int genomeid)
{
	std::vector<Node*> cloneNodes;
	for (int i = 0; i < _nodes.size(); i++)
	{
		Node* _clonenode = _nodes[i]->GetClone();
		std::vector<Node::Link*> _outputs = _nodes[i]->GetOutputs();
		for (int j = 0; j < _outputs.size(); j++)
		{
			_outputs[j]->GetClone();
		}
		cloneNodes.push_back(_clonenode);
	}
	std::vector<InputNode*> cloneInputs;
	for (int i = 0; i < _inputnodes.size(); i++)
	{
		cloneInputs.push_back(_inputnodes[i]->GetINClone());
	}
	std::vector<OutputNode*> cloneOutputs;
	for (int i = 0; i < _outputnodes.size(); i++)
	{
		cloneOutputs.push_back(_outputnodes[i]->GetONNode());
	}
	std::vector<Node*> cloneIntermediates;
	for (int i = 0; i < _intermediatenodes.size(); i++)
	{
		cloneIntermediates.push_back(_intermediatenodes[i]->GetClone());
	}
	std::vector<InputMemoryNode*> cloneSTINPMems;
	for (int i = 0; i < _stinputmemorynodes.size(); i++)
	{
		cloneSTINPMems.push_back(_stinputmemorynodes[i]->GetIMNClone());
	}
	std::vector<OutputMemoryNode*> cloneSTOUTMems;
	for (int i = 0; i < _stoutputmemorynodes.size(); i++)
	{
		cloneSTOUTMems.push_back(_stoutputmemorynodes[i]->GetOMNClone());
	}
	std::vector<InputMemoryNode*> cloneLTINPMems;
	for (int i = 0; i < _ltinputmemorynodes.size(); i++)
	{
		cloneLTINPMems.push_back(_ltinputmemorynodes[i]->GetIMNClone());
	}
	std::vector<OutputMemoryNode*> cloneLTOUTMems;
	for (int i = 0; i < _ltoutputmemorynodes.size(); i++)
	{
		cloneLTOUTMems.push_back(_ltoutputmemorynodes[i]->GetOMNClone());
	}
	std::vector<GoldenNode*> cloneGoldenNodes;
	for (int i = 0; i < _goldennodes.size(); i++)
	{
		cloneGoldenNodes.push_back(_goldennodes[i]->GetGoldenClone());
	}
	MemoryPresentNode* cloneMPNode = _memorypresentnode->GetMPClone();
	Genome* genome = new Genome(_inputCount, _outputCount, _ltMemoryCount, _stMemoryCount, genomeid);
	genome->SetNodes(cloneNodes, cloneInputs, cloneOutputs, cloneIntermediates, cloneLTINPMems, cloneLTOUTMems, cloneSTINPMems, cloneSTOUTMems, cloneGoldenNodes, cloneMPNode);
	return genome;
}

int Genome::GetInputCount()
{
	return _inputCount;
}

int Genome::GetOutputCount()
{
	return _outputCount;
}

int Genome::GetLTMemoryCount()
{
	return _ltMemoryCount;
}

int Genome::GetSTMemoryCount()
{
	return _stMemoryCount;
}

void Genome::AddNode(Node* prevnode, Node* nextnode)
{
	if (prevnode->GetDistance() != nextnode->GetDistance())
	{
		Node* smallerDistance = prevnode->GetDistance() < nextnode->GetDistance() ? prevnode : nextnode;
		Node* largerDistance = prevnode->GetDistance() > nextnode->GetDistance() ? nextnode : prevnode;
		Node* n = new Node();
		n->RandomiseDistance(smallerDistance->GetDistance(), largerDistance->GetDistance());
		n->AddInput(smallerDistance);
		n->AddOutput(largerDistance);
		AddNode(n);
	}
}

void Genome::AddNode(Node* node)
{
	_nodes.push_back(node);
	_intermediatenodes.push_back(node);
}

void Genome::RemoveNode(Node* node)
{
	node->DeleteLinks();
	std::vector<Node*>::iterator inti = std::find(_intermediatenodes.begin(), _intermediatenodes.end(), node);
	if (inti != _intermediatenodes.end())
	{
		_intermediatenodes.erase(inti);
	}
	std::vector<Node*>::iterator ni = std::find(_nodes.begin(), _nodes.end(), node);
	if (ni != _nodes.end())
	{
		_nodes.erase(ni);
	}
}