#include "ExternalInterface.h"

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

void RemoveGenome(int id)
{
	GenomeManager::RemoveGenome(id);
}

void Mutate(int genomeid, int iterations)
{
	Genome* g = GenomeManager::GetGenome(genomeid);
	if (g)
	{
		for (int i = 0; i < abs(iterations); i++)
		{
			double r = Operations::randd->NextDouble();
			const double options = 4;
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
		}
	}
}