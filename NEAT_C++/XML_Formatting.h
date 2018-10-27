#ifndef _XML_FORMATTING_H

#define _XML_FORMATTING_H

#include <fstream>
#include <sstream>
#include <stack>
#include"GenomeManager.h"
#include"Operations.h"
#include<vector>//Remove when possible

enum TagType
{
	OPEN, CLOSE
};

//#define TOSTRING(num) return std::to_string(num);

class XML_Formatting
{
	public:
		static std::string ConvertGenomeToXML(Genome* genome);
		static void SaveGenome(Genome* genome, std::string filepath);
		static std::string ReadFile(std::string filepath);
		static Genome* ParseGenome(std::string filepath);
	private:
		static bool IsTag(std::string text, std::stack<std::string>* elementsstack);
		static std::vector<std::string> OpenTags();
		static std::vector<std::string> CloseTags();
		static std::string GetNameFromTag(std::string tag, TagType tagtype);
		static Genome* ParseGenomeDirect(std::string content);

		static const std::string genomeopentag;
		static const std::string genomeclosetag;
		
		static const std::string inputsopentag;
		static const std::string inputsclosetag;
		
		static const std::string intermediatesopentag;
		static const std::string intermediatesclosetag;
		
		static const std::string outputsopentag;
		static const std::string outputsclosetag;

		static const std::string shortmemorymapopentag;
		static const std::string shortmemorymapclosetag;

		static const std::string longmemorymapopentag;
		static const std::string longmemorymapclosetag;

		static const std::string goldennodesopentag;
		static const std::string goldennodesclosetag;

		static const std::string linksopentag;
		static const std::string linksclosetag;

		static std::vector<std::string> opentags;
		static std::vector<std::string> closetags;
};

#endif