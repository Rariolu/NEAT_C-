#ifndef  _GENOME_MANAGER_H
#define _GENOME_MANAGER_H

#include<map>
#include"Genome.h"

class GenomeManager
{
	public:
		static int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount);
		static int CreateNewGenomeID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid);
		static Genome* GetGenome(int id);
		static int CloneGenome(int genomeid);
		static int CloneGenome(int genomeid, int newgenomeid);
		static void InsertGenome(int id, Genome* genome);
		static void RemoveGenome(int id);
		static int Count();
		static void IDCheck(int id);
	private:
		static int _id;
		static std::map<int, Genome*> genomes;
};

#endif