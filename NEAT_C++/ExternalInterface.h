#ifndef _EXTERNAL_INTERFACE_H
#define _EXTERNAL_INTERFACE_H

#include "URGH.h"
#include "XML_Formatting.h"

extern "C"
{
	//Test method
	EXTERN_TEMPLATE int TestDLL();

	EXTERN_TEMPLATE bool GenomeExists(int id);
	EXTERN_TEMPLATE int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount);
	EXTERN_TEMPLATE int CloneGenome(int genomeid);
	EXTERN_TEMPLATE int CreateNewGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid);
	EXTERN_TEMPLATE int CloneGenomeWithID(int genomeid, int newgenomeid);
	EXTERN_TEMPLATE void SaveGenome(int id, std::string filepath);//char* filepath);
	EXTERN_TEMPLATE int ParseGenome(char* filepath);
	EXTERN_TEMPLATE void RemoveGenome(int id);
	EXTERN_TEMPLATE double GetOutputFromGenome(int genome, int inputcount, double inputs[], int outputnum);
	EXTERN_TEMPLATE void ResetMemory(int genomeid);
	EXTERN_TEMPLATE void Mutate(int genomeid, int iterations);
	//Individual mutation methods
	EXTERN_TEMPLATE void RemoveNode(int genomeid, int intermediateindex);
	EXTERN_TEMPLATE void CreateNode(int genomeid, int previousNode, int nextNode);
	EXTERN_TEMPLATE void CreateLink(int genomeid, int source, int destination, double weight);
	EXTERN_TEMPLATE void AlterLinkWeight(int genomeid, int source, int destination, double weight);
	EXTERN_TEMPLATE void RemoveLink(int genomeid, int source, int destination);
	EXTERN_TEMPLATE void CreateIntermediateNode(int genomeid, int inputNode, int outputNode);
	EXTERN_TEMPLATE void Train(int genomeid, double input[], double outputs[]);


	//Get genome properties
	EXTERN_TEMPLATE int InputCount(int genomeid);
	EXTERN_TEMPLATE int OutputCount(int genomeid);
	EXTERN_TEMPLATE int LTMemoryCount(int genomeid);
	EXTERN_TEMPLATE int STMemoryCount(int genomeid);

	EXTERN_TEMPLATE int NodeCount(int genomeid);
	EXTERN_TEMPLATE int IntermediateNodeCount(int genomeid);
}

#endif