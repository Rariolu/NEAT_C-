#include "XML_Formatting.h"

const std::string XML_Formatting::genomeopentag = "<genome>";
const std::string XML_Formatting::genomeclosetag = "</genome>";

const std::string XML_Formatting::inputsopentag = "<inputs>";
const std::string XML_Formatting::inputsclosetag = "</inputs>";

const std::string XML_Formatting::intermediatesopentag = "<intermediates>";
const std::string XML_Formatting::intermediatesclosetag = "</intermediates>";

const std::string XML_Formatting::outputsopentag = "<outputs>";
const std::string XML_Formatting::outputsclosetag = "</outputs>";

const std::string XML_Formatting::shortmemorymapopentag = "<stmemory>";
const std::string XML_Formatting::shortmemorymapclosetag = "</stmemory>";

const std::string XML_Formatting::longmemorymapopentag = "<ltmemory>";
const std::string XML_Formatting::longmemorymapclosetag = "</ltmemory>";

const std::string XML_Formatting::goldennodesopentag = "<goldennodes>";
const std::string XML_Formatting::goldennodesclosetag = "</goldennodes>";

const std::string XML_Formatting::linksopentag = "<links>";
const std::string XML_Formatting::linksclosetag = "</links>";

std::vector<std::string> XML_Formatting::opentags;
std::vector<std::string> XML_Formatting::closetags;

std::string XML_Formatting::ConvertGenomeToXML(Genome* genome)
{
	int id = genome->ID();

	std::string content = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

	content += genomeopentag + "\n";

	content += "\t<ID>" + std::to_string(id) + "</ID>\n";

	int inputcount = genome->GetInputCount();
	int outputcount = genome->GetOutputCount();

	int ltmemorycount = genome->GetLTMemoryCount();
	int stmemorycount = genome->GetSTMemoryCount();

	content += "\t<InputCount>" + std::to_string(inputcount) + "</InputCount>\n";

	content += "\t<OutputCount>" + std::to_string(outputcount) + "</OutputCount>\n";
	content += "\t<STMemoryCount>" + std::to_string(stmemorycount) + "</STMemoryCount>\n";

	content += "\t<LTMemoryCount>" + std::to_string(ltmemorycount) + "</LTMemoryCount>\n";
	
	content += "\t<MemoryPresentNode>" + std::to_string(genome->MPNode()->GetNodeID()) + "</MemoryPresentNode>\n";

	content += "\t" + inputsopentag + "\n";

	std::vector<InputNode*> inputs = genome->InputNodes();

	for (std::vector<InputNode*>::iterator inp = inputs.begin(); inp < inputs.end(); inp++)
	{
		int id = (*inp)->GetNodeID();
		int inputindex = (*inp)->GetInputIndex();
		content += "\t\t<input id=\"" + std::to_string(id) + "\" inpindex=\"" + std::to_string(inputindex) + "\"/>\n";
	}

	content += "\t" + inputsclosetag + "\n";

	content += "\t" + intermediatesopentag + "\n";

	std::vector<Node*> intermediates = genome->IntermediateNodes();

	for (std::vector<Node*>::iterator interim = intermediates.begin(); interim < intermediates.end(); interim++)
	{
		int id = (*interim)->GetNodeID();
		double distance = (*interim)->GetDistance();
		content += "\t\t<intermediate id=\"" + std::to_string(id) + "\" distance=\"" + std::to_string(distance) + "\"/>\n";
	}

	content += "\t" + intermediatesclosetag + "\n";

	content += "\t" + outputsopentag + "\n";

	std::vector<OutputNode*> outputs = genome->OutputNodes();

	for (std::vector<OutputNode*>::iterator output = outputs.begin(); output < outputs.end(); output++)
	{
		int id = (*output)->GetNodeID();
		content += "\t\t<output id=\"" + std::to_string(id) + "\"/>\n";
	}

	content += "\t" + outputsclosetag + "\n";

	content += "\t" + shortmemorymapopentag + "\n";

	for (int i = 0; i < genome->GetSTMemoryCount(); i++)
	{
		InputMemoryNode* imn = genome->STInputMemoryNodes()[i];
		OutputMemoryNode* omn = imn->GetOutputMemoryNode();
		int inpid = imn->GetNodeID();
		int outid = omn->GetNodeID();
		content += "\t\t<memory input=\"" + std::to_string(inpid) + "\" output=\"" + std::to_string(outid) + "\"/>\n";
	}

	content += "\t" + shortmemorymapclosetag + "\n";

	content += "\t" + longmemorymapopentag + "\n";

	for (int i = 0; i < genome->GetLTMemoryCount(); i++)
	{
		InputMemoryNode* imn = genome->LTInputMemoryNodes()[i];
		OutputMemoryNode* omn = imn->GetOutputMemoryNode();
		int inpid = imn->GetNodeID();
		int outid = omn->GetNodeID();
		double val = omn->GetPreviousIterationOutput();
		content += "\t\t<memory input=\"" + std::to_string(inpid) + "\" output=\"" + std::to_string(outid) + "\" value=\"" + std::to_string(val) + "\"/>\n";
	}

	content += "\t" + longmemorymapclosetag + "\n";

	content += "\t" + goldennodesopentag + "\n";

	std::vector<GoldenNode*> goldenNodes = genome->GoldenNodes();

	for (int i = 0; i < goldenNodes.size(); i++)
	{
		GoldenNode* gn = goldenNodes[i];
		int id = gn->GetNodeID();
		Operator op = gn->GetOperator();
		std::vector<Node::Link*> maininputs = gn->GetMainInputs();
		content += "\t\t<gold id=\""+std::to_string(id)+"\" operation";
	}

	content += "\t" + goldennodesclosetag + "\n";
	
	content += "\t" + linksopentag + "\n";

	std::vector<Node*> nodes = genome->Nodes();

	for (std::vector<Node*>::iterator node = nodes.begin(); node < nodes.end(); node++)
	{
		std::vector<Node::Link*> inputlinks = (*node)->GetInputs();
		if (inputs.size() > 0)
		{
			for (std::vector<Node::Link*>::iterator inp = inputlinks.begin(); inp < inputlinks.end(); inp++)
			{
				Node* source = (*inp)->GetSource();
				Node* destination = (*inp)->GetDestination();
				double weight = (*inp)->GetWeight();
				if (source != NULL && destination != NULL)
				{
					int s = source->GetNodeID();
					int d = destination->GetNodeID();
					content += "\t\t<link source=\"" + std::to_string(s) + "\" destination=\"" + std::to_string(d) + "\" weight=\"" + std::to_string(weight) + "\"/>\n";
				}
			}
		}
	}

	content += "\t" + linksclosetag + "\n";

	content += genomeclosetag + "\n";

	return content;
}

void XML_Formatting::SaveGenome(Genome* genome, std::string filepath)
{
	std::string content = ConvertGenomeToXML(genome);
	std::ofstream file;
	file.open(filepath, std::ios::out);
	file << content;
	file.close();
	std::cout << "Saved " << filepath << std::endl;
}

std::string XML_Formatting::ReadFile(std::string filepath)
{
	//https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();
	return content;
}

Genome* XML_Formatting::ParseGenome(std::string filepath)
{
	std::string content = ReadFile(filepath);
	Genome* genome = ParseGenomeDirect(content);
	if (genome)
	{
		GenomeManager::InsertGenome(genome->ID(), genome);
	}
	return genome;
}

bool XML_Formatting::IsTag(std::string text, std::stack<std::string>* elementsstack)
{
	std::vector<std::string> opentags = OpenTags();
	for (std::vector<std::string>::iterator opentag = opentags.begin(); opentag < opentags.end(); opentag++)
	{
		if (Operations::Contains(text, (*opentag)))
		{
			elementsstack->push((*opentag));
			return true;
		}
	}
	std::vector<std::string> closetags = CloseTags();
	for (std::vector<std::string>::iterator closetag = closetags.begin(); closetag < closetags.end(); closetag++)
	{
		if (Operations::Contains(text, (*closetag)))
		{
			std::string opname = GetNameFromTag(elementsstack->top(), OPEN);
			std::string closname = GetNameFromTag((*closetag), CLOSE);
			if (opname == closname)
			{
				elementsstack->pop();
			}
			return true;
		}
	}
	return false;
}

std::vector<std::string> XML_Formatting::OpenTags()
{
	if (opentags.size() < 1)
	{
		opentags.push_back(genomeopentag);
		opentags.push_back(inputsopentag);
		opentags.push_back(intermediatesopentag);
		opentags.push_back(outputsopentag);
		opentags.push_back(linksopentag);
	}
	return opentags;
}

std::vector<std::string> XML_Formatting::CloseTags()
{
	if (closetags.size() < 1)
	{
		closetags.push_back(genomeclosetag);
		closetags.push_back(inputsclosetag);
		closetags.push_back(intermediatesclosetag);
		closetags.push_back(outputsclosetag);
		closetags.push_back(shortmemorymapclosetag);
		closetags.push_back(longmemorymapclosetag);
		closetags.push_back(linksclosetag);
	}
	return closetags;
}

std::string XML_Formatting::GetNameFromTag(std::string tag, TagType tagtype)
{
	std::string op = tagtype == OPEN ? "<" : "</";
	std::string t = "";
	if (!(Operations::Contains(tag, op) && Operations::Contains(tag, ">")))
	{
		t = tag.substr(tagtype, tag.length() - 1);
	}
	return t;
}

Genome* XML_Formatting::ParseGenomeDirect(std::string content)
{
	Genome* genome = NULL;
	bool idset = false;
	bool inputcountset = false;
	bool outputcountset = false;
	bool ltmemcountset = false;
	bool stmemcountset = false;
	bool memorypresentset = false;
	int id;
	int inputcount;
	int outputcount;
	int ltmemcount;
	int stmemcount;
	int memorypresent;
	std::string line;
	std::stack<std::string>* elements = new std::stack<std::string>();
	std::istringstream stream(content);

	std::vector<std::pair<int,int>> links;
	while (std::getline(stream, line))
	{
		if (!IsTag(line, elements))
		{
			if (elements->size() > 0)
			{
				if (elements->top() == genomeopentag)
				{

				}
				else if (elements->top() == inputsopentag)
				{

				}
				else if (elements->top() == intermediatesopentag)
				{

				}
				else if (elements->top() == outputsopentag)
				{

				}
				else if (elements->top() == shortmemorymapopentag)
				{

				}
				else if (elements->top() == longmemorymapopentag)
				{

				}
				else if (elements->top() == goldennodesopentag)
				{

				}
				else if (elements->top() == linksopentag)
				{

				}
			}
		}
	}
	return genome;
}