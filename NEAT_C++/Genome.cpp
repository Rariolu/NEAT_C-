#include "Genome.h"

Genome::Genome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int id)
{
	_inputCount = inputcount;
	_outputCount = outputcount;
	_ltMemoryCount = ltmemorycount;
	_stMemoryCount = stmemorycount;
	std::cout << "NodeCount: " << GetNodeCount() << std::endl;
	for (int i = 0; i < inputcount; i++)
	{
		InputNode* inp = new InputNode(i);
		_inputnodes.push_back(inp);
		_nodes.push_back(inp);
	}
	for (int i = 0; i < outputcount; i++)
	{
		OutputNode* outp = new OutputNode();
		_outputnodes.push_back(outp);
		_nodes.push_back(outp);
	}
	for (int i = 0; i < ltmemorycount; i++)
	{
		OutputMemoryNode* omn = new OutputMemoryNode(true);
		InputMemoryNode* imn = new InputMemoryNode(omn);
		_ltoutputmemorynodes.push_back(omn);
		_ltinputmemorynodes.push_back(imn);
		_nodes.push_back(omn);
		_nodes.push_back(imn);
	}
	for (int i = 0; i < stmemorycount; i++)
	{
		OutputMemoryNode* omn = new OutputMemoryNode(false);
		InputMemoryNode* imn = new InputMemoryNode(omn);
		_stoutputmemorynodes.push_back(omn);
		_stinputmemorynodes.push_back(imn);
		_nodes.push_back(omn);
		_nodes.push_back(imn);
	}
	_memorypresentnode = new MemoryPresentNode(stmemorycount > 0);
	_nodes.push_back(_memorypresentnode);
	std::cout << "NodeCount: " << GetNodeCount() << std::endl;
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
	_nodes = nodes;
	_inputnodes = inputnodes;
	_outputnodes = outputnodes;
	_intermediatenodes = intermediatenodes;
	_ltinputmemorynodes = ltinputmemorynodes;
	_ltoutputmemorynodes = ltoutputmemorynodes;
	_stinputmemorynodes = stinputmemorynodes;
	_stoutputmemorynodes = stoutputmemorynodes;
	_goldennodes = goldennodes;
	_memorypresentnode = memorypresentnode;
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
	if (_nodes.size() > 0)
	{
		std::cout << "Create Node method" << std::endl;
		int prevNodeIndex = previousNode % _nodes.size();
		int nextNodeIndex = nextNode % _nodes.size();
		if (prevNodeIndex != nextNodeIndex)
		{
			AddNode(_nodes[prevNodeIndex], _nodes[nextNodeIndex]);
		}
	}
}

void Genome::CreateIntermediateNode(int inputNode, int outputNode)
{
	if (_nodes.size() > 0)
	{
		Node* inp = _inputnodes[inputNode % _inputnodes.size()];
		Node* out = _outputnodes[outputNode % _outputnodes.size()];
		AddNode(inp, out);
	}
}

void Genome::CreateLink(int source, int destination, double weight)
{
	if (_nodes.size() > 0)
	{
		Node* s = _nodes[source%_nodes.size()];
		Node* d = _nodes[destination%_nodes.size()];
		Node* _s = s->GetDistance() < d->GetDistance() ? s : d;
		Node* _d = s->GetDistance() > d->GetDistance() ? s : d;
		if (_s->GetDistance() != _d->GetDistance())
		{
			Node::Link* link = new Node::Link(_s, _d, weight);
			_s->AddOutput(link);
			_d->AddInput(link);
		}
	}
}

void Genome::AlterLinkWeight(int source, int destination, double weight)
{
	if (_nodes.size() > 0)
	{
		Node* s = _nodes[source%_nodes.size()];
		Node* d = _nodes[destination%_nodes.size()];
		std::vector<Node::Link*> s_outputs = s->GetOutputs();
		for (int i = 0; i < s_outputs.size(); i++)
		{
			if (s_outputs[i]->GetDestination() == d)
			{
				s_outputs[i]->SetWeight(weight);
				return;
			}
		}
	}
}

void Genome::RemoveLink(int source, int destination)
{
	if (GetNodeCount() > 0)
	{
		Node* s = _nodes[source%GetNodeCount()];
		Node* d = _nodes[destination%GetNodeCount()];
		std::vector<Node::Link*> s_outputs = s->GetOutputs();
		for (int i = 0; i < s_outputs.size(); i++)
		{
			if (s_outputs[i]->GetDestination() == d)
			{
				s->RemoveOutput(i);
				d->RemoveInput(s_outputs[i]);
				return;
			}
		}
	}
}

Genome* Genome::Clone(int genomeid)
{
	//std::cout << "Clone method called" << std::endl;
	std::vector<Node*> cloneNodes;
	//std::cout << "Begin node cloning" << std::endl;
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
	//std::cout << "Input node cloning" << std::endl;
	for (int i = 0; i < _inputnodes.size(); i++)
	{
		cloneInputs.push_back(_inputnodes[i]->GetINClone());
	}
	std::vector<OutputNode*> cloneOutputs;
	//std::cout << "Output node cloning" << std::endl;
	for (int i = 0; i < _outputnodes.size(); i++)
	{
		cloneOutputs.push_back(_outputnodes[i]->GetONNode());
	}
	std::vector<Node*> cloneIntermediates;
	//std::cout << "Intermediate node cloning" << std::endl;
	for (int i = 0; i < _intermediatenodes.size(); i++)
	{
		cloneIntermediates.push_back(_intermediatenodes[i]->GetClone());
	}
	std::vector<InputMemoryNode*> cloneSTINPMems;
	//std::cout << "STINPMEM node cloning" << std::endl;
	for (int i = 0; i < _stinputmemorynodes.size(); i++)
	{
		cloneSTINPMems.push_back(_stinputmemorynodes[i]->GetIMNClone());
	}
	std::vector<OutputMemoryNode*> cloneSTOUTMems;
	//std::cout << "STOUTMEM node cloning" << std::endl;
	for (int i = 0; i < _stoutputmemorynodes.size(); i++)
	{
		cloneSTOUTMems.push_back(_stoutputmemorynodes[i]->GetOMNClone());
	}
	std::vector<InputMemoryNode*> cloneLTINPMems;
	//std::cout << "LTINPMEM node cloning" << std::endl;
	for (int i = 0; i < _ltinputmemorynodes.size(); i++)
	{
		cloneLTINPMems.push_back(_ltinputmemorynodes[i]->GetIMNClone());
	}
	std::vector<OutputMemoryNode*> cloneLTOUTMems;
	//std::cout << "LTOUTMEM node cloning" << std::endl;
	for (int i = 0; i < _ltoutputmemorynodes.size(); i++)
	{
		cloneLTOUTMems.push_back(_ltoutputmemorynodes[i]->GetOMNClone());
	}
	std::vector<GoldenNode*> cloneGoldenNodes;
	//std::cout << "Gold node cloning" << std::endl;
	for (int i = 0; i < _goldennodes.size(); i++)
	{
		cloneGoldenNodes.push_back(_goldennodes[i]->GetGoldenClone());
	}
	//std::cout << "Memory Present Node cloning" << std::endl;
	MemoryPresentNode* cloneMPNode = _memorypresentnode->GetMPClone();
	Genome* genome = new Genome(_inputCount, _outputCount, _ltMemoryCount, _stMemoryCount, genomeid);
	//std::cout << "Genome created" << std::endl;
	genome->SetNodes(cloneNodes, cloneInputs, cloneOutputs, cloneIntermediates, cloneLTINPMems, cloneLTOUTMems, cloneSTINPMems, cloneSTOUTMems, cloneGoldenNodes, cloneMPNode);
	//std::cout << "Nodes set" << std::endl;
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

int Genome::GetNodeCount()
{
	return _nodes.size();
}

int Genome::GetIntermediateNodeCount()
{
	return _intermediatenodes.size();
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