#include "GenomeManager.h"

int GenomeManager::_id = 0;
std::map<int, Genome*> GenomeManager::genomes;

int GenomeManager::CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
{
	return CreateNewGenomeID(inputcount, outputcount, ltmemorycount, stmemorycount, _id++);
}

int GenomeManager::CreateNewGenomeID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid)
{
	if (GetGenome(genomeid))
	{
		return -1;
	}
	Genome* genome = new Genome(inputcount, outputcount, ltmemorycount, stmemorycount, genomeid);
	InsertGenome(genomeid, genome);
	return genomeid;
}

Genome* GenomeManager::GetGenome(int id)
{
	//std::cout << "GetGenome called" << std::endl;
	std::map<int, Genome*>::iterator i = genomes.find(id);
	if (i != genomes.end())
	{
		//std::cout << "Genome found" << std::endl;
		return i->second;
	}
	return NULL;
}

int GenomeManager::CloneGenome(int genomeid)
{
	int newgenomeid = _id++;
	return CloneGenome(genomeid, newgenomeid);
}

int GenomeManager::CloneGenome(int genomeid, int newgenomeid)
{
	//std::cout << "Clone called " << genomeid << std::endl;
	if (GetGenome(newgenomeid))
	{
		return -1;
	}
	Genome* genome = GetGenome(genomeid);
	//std::cout << "GetGenome returned a value" << std::endl;
	if (genome)
	{
		//std::cout << "Genome isn't null" << std::endl;
		Genome* newGenome = genome->Clone(newgenomeid);
		InsertGenome(newgenomeid, newGenome);
		return newgenomeid;
	}
	return 0;
}

void GenomeManager::InsertGenome(int id, Genome* genome)
{
	if (!GetGenome(id))
	{
		genomes.insert(std::make_pair(id, genome));
	}
}

void GenomeManager::RemoveGenome(int id)
{
	std::map<int, Genome*>::iterator i = genomes.find(id);//std::find(genomes.begin(), genomes.end(), id);
	if (i != genomes.end())
	{
		delete i->second;
		genomes.erase(i);
	}
}

int GenomeManager::Count()
{
	return (int)genomes.size();
}

void GenomeManager::IDCheck(int id)
{
	if (id > _id)
	{
		_id = id + 1;
	}
}