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

}