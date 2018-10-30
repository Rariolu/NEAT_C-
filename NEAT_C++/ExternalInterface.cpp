#include "ExternalInterface.h"

int TestDLL()
{
	return 5;
}

bool GenomeExists(int id)
{
	return GenomeManager::GetGenome(id);
}

int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
{
	return GenomeManager::CreateNewGenome(inputcount, outputcount, ltmemorycount, stmemorycount);
}

int CloneGenome(int genomeid)
{
	return GenomeManager::CloneGenome(genomeid);
}

int CreateNewGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid)
{
	return GenomeManager::CreateNewGenomeID(inputcount, outputcount, ltmemorycount, stmemorycount,genomeid);
}

int CloneGenomeWithID(int genomeid, int newgenomeid)
{
	return GenomeManager::CloneGenome(genomeid, newgenomeid);
}

extern "C" void SaveGenome(int id, char* filepath)
{
	Genome* genome = GenomeManager::GetGenome(id);
	if (genome)
	{
		XML_Formatting::SaveGenome(genome, std::string(filepath));
	}
}

bool ParseGenome(char* filepath)
{
	std::string file = std::string(filepath);
	Genome* genome = XML_Formatting::ParseGenome(file);
	if (genome)
	{
		GenomeManager::InsertGenome(genome->ID(), genome);
	}
	return genome;
}

void RemoveGenome(int id)
{
	GenomeManager::RemoveGenome(id);
}

double GetOutputFromGenome(int genome, int inputcount, double inputs[], int outputnum)
{
	Genome* _genome = GenomeManager::GetGenome(genome);
	if (_genome)
	{
		return _genome->GetOutput(inputs, outputnum);
	}
	return 0;
}

void ResetMemory(int genomeid)
{
	Genome* genome = GenomeManager::GetGenome(genomeid);
	if (genome)
	{
		genome->ResetMemory();
	}
}

void Mutate(int genomeid, int iterations)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		for (int i = 0; i < abs(iterations); i++)
		{
			double r = Operations::randd->NextDouble();
			const double options = 5;
			int s = Operations::randd->Next(g->GetNodeCount());
			int d = Operations::randd->Next(g->GetNodeCount());
			double w = Operations::randd->NextDouble(-25, 25);
			if (r < 1 / options)
			//Remove Node
			{
				int n = Operations::randd->Next(g->GetIntermediateNodeCount());
				g->RemoveNode(n);
			}
			else if (r < 2 / options)
			//Create Node
			{
				g->CreateNode(s, d);
			}
			else if (r < 3 / options)
			//Create Link
			{
				g->CreateLink(s, d, w);
			}
			else if (r < 4 / options)
			//Alter Link Weight
			{
				g->AlterLinkWeight(s, d, w);
			}
			else if (r < 5 / options)
			//Remove Link
			{
				g->RemoveLink(s, d);
			}
		}
	}
}

void RemoveNode(int genomeid, int intermediateindex)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		g->RemoveNode(intermediateindex);
	}
}

void CreateNode(int genomeid, int previousNode, int nextNode)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		g->CreateNode(previousNode, nextNode);
	}
}

void CreateLink(int genomeid, int source, int destination, double weight)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		g->CreateLink(source, destination, weight);
	}
}

void AlterLinkWeight(int genomeid, int source, int destination, double weight)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		g->AlterLinkWeight(source, destination, weight);
	}
}

void RemoveLink(int genomeid, int source, int destination)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		g->RemoveLink(source, destination);
	}
}