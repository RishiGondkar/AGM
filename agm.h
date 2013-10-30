#pragma once

#include <agm_behavior.h>
#include <agm_model.h>
#include <agm_modelSymbols.h>
#include <agm_modelEdge.h>
#include <agm_modelConverter.h>
#include <agm_search.h>


class AGGLRule
{
public:
	std::string name;
	bool active;
	// LHS
	std::vector<std::string> lhsSymbolsNames;
	std::vector<std::string> lhsSymbolsTypes;
	std::vector<std::string> lhsLinksA;
	std::vector<std::string> lhsLinksB;
	std::vector<std::string> lhsLinksLabel;
	/// RHS
	std::vector<std::string> rhsSymbolsNames;
	std::vector<std::string> rhsSymbolsTypes;
	std::vector<std::string> rhsLinksA;
	std::vector<std::string> rhsLinksB;
	std::vector<std::string> rhsLinksLabel;
	// Effect
	std::vector<std::string> symbolsToCreateName;
	std::vector<std::string> symbolsToCreateType;
	std::vector<std::string> symbolsToRemove;
	std::vector<std::string> symbolsToRetypeName;
	std::vector<std::string> symbolsToRetypeType;
	
	std::vector<std::string> addLinksA;
	std::vector<std::string> addLinksB;
	std::vector<std::string> addLinksLabel;
	std::vector<std::string> remLinksA;
	std::vector<std::string> remLinksB;
	std::vector<std::string> remLinksLabel;
	
	void print()
	{
		printf(" Name: %s (%s)\n", name.c_str(), active?"active":"passive");
		if (symbolsToCreateName.size()>0) printf("   Create symbols:\n");
		for (uint i=0; i<symbolsToCreateName.size(); ++i)
		{
			printf("      %s (%s)\n", symbolsToCreateName[i].c_str(), symbolsToCreateType[i].c_str());
		}
		if (symbolsToRemove.size()>0) printf("   Remove symbols:\n");
		for (uint i=0; i<symbolsToRemove.size(); ++i)
		{
			printf("      %s\n", symbolsToRemove[i].c_str());
		}
		if (symbolsToRetypeName.size()>0) printf("   Retype symbols:\n");
		for (uint i=0; i<symbolsToRetypeName.size(); ++i)
		{
			printf("      %s (%s)\n", symbolsToRetypeName[i].c_str(), symbolsToRetypeType[i].c_str());
		}
		if (addLinksA.size()>0) printf("   Create links:\n");
		for (uint i=0; i<addLinksA.size(); ++i)
		{
			printf("      %s---[%s]--->%s\n", addLinksA[i].c_str(), addLinksLabel[i].c_str(), addLinksB[i].c_str());
		}
		if (remLinksA.size()>0) printf("   Remove links:\n");
		for (uint i=0; i<remLinksA.size(); ++i)
		{
			printf("      %s---[%s]--->%s\n", remLinksA[i].c_str(), remLinksLabel[i].c_str(), remLinksB[i].c_str());
		}
	}
	
	void setName(const char *nam)
	{
		name = std::string(nam);
	}

	void setActive(const char *act)
	{
		std::string acti(act);
		if (acti == "active")
			active = true;
		else if (acti == "passive")
			active = false;
		else
		{
			printf("Wrong active/passive\n");
			exit(-1);
		}
	}
	void addSymbol(bool left, std::string name, std::string type)
	{
		if (left)
		{
			lhsSymbolsNames.push_back(name);
			lhsSymbolsTypes.push_back(type);
		}
		else
		{
			rhsSymbolsNames.push_back(name);
			rhsSymbolsTypes.push_back(type);
		}
	}
	void addLink(bool left, std::string a, std::string b, std::string label)
	{
		if (left)
		{
			lhsLinksA.push_back(a);
			lhsLinksB.push_back(b);
			lhsLinksLabel.push_back(label);
		}
		else
		{
			rhsLinksA.push_back(a);
			rhsLinksB.push_back(b);
			rhsLinksLabel.push_back(label);
		}
	}
	void computeEffects()
	{
		//printf("symbol creation\n");
		/// Symbol deletion
		for (uint32_t i=0; i<rhsSymbolsNames.size(); i++)
		{
			bool found = false;
			for (uint32_t j=0; j<lhsSymbolsNames.size() and not found; j++)
			{
				if (rhsSymbolsNames[i] == lhsSymbolsNames[j])
					found = true;
			}
			if (found)
			{
				symbolsToRemove.push_back(rhsSymbolsNames[i]);
			}
		}
		//printf("symbol deletion\n");
		/// Symbol deletion
		for (uint32_t i=0; i<lhsSymbolsNames.size(); i++)
		{
			bool found = false;
			uint32_t j;
			for (j=0; j<rhsSymbolsNames.size() and not found; j++)
			{
				if (lhsSymbolsNames[i] == rhsSymbolsNames[j])
				{
					found = true;
					break;
				}
			}
			if (not found)
			{
				symbolsToCreateName.push_back(lhsSymbolsNames[i]);
				symbolsToCreateType.push_back(lhsSymbolsTypes[i]);
			}
		}
		//printf("typing\n");
		/// Type changes
		for (uint32_t i=0; i<lhsSymbolsNames.size(); i++)
		{
			bool found = false;
			for (uint32_t j=0; j<symbolsToCreateName.size() and not found; j++)
			{
				if (lhsSymbolsNames[i] == symbolsToCreateName[j]) found = true;
			}
			for (uint32_t j=0; j<symbolsToRemove.size() and not found; j++)
			{
				if (lhsSymbolsNames[i] == symbolsToRemove[j]) found = true;
			}
			// If they remain
			if (not found)
			{
				for (uint32_t k=0; k<rhsSymbolsNames.size(); k++)
				{
					if (lhsSymbolsNames[i] == rhsSymbolsNames[k])
					{
						if (lhsSymbolsTypes[i] != rhsSymbolsTypes[k])
						{
							symbolsToRetypeName.push_back(lhsSymbolsNames[i]);
							symbolsToRetypeType.push_back(rhsSymbolsTypes[k]);
						}
					}
				}
			}
		}
		//printf("link creation\n");
		/// Link creation
		for (uint32_t j=0; j<rhsLinksLabel.size(); j++)
		{
			bool found = false;
			for (uint32_t i=0; i<lhsLinksLabel.size() and not found; i++)
			{
				if (lhsLinksA[i] == rhsLinksA[j])
				{
					if (lhsLinksLabel[i] == rhsLinksLabel[j])
					{
						if (lhsLinksB[i] == rhsLinksB[j])
						{
							found = true;
						}
					}
				}
			}
			if (found)
			{
				addLinksA.push_back(lhsLinksA[j]);
				addLinksB.push_back(lhsLinksB[j]);
				addLinksLabel.push_back(lhsLinksLabel[j]);
			}
		}
		//printf("link deletion\n");
		/// Link deletion
		for (uint32_t i=0; i<lhsLinksLabel.size(); i++)
		{
			bool found = false;
			for (uint32_t j=0; j<rhsLinksLabel.size() and not found; j++)
			{
				if (lhsLinksA[i] == rhsLinksA[j])
				{
					if (lhsLinksLabel[i] == rhsLinksLabel[j])
					{
						if (lhsLinksB[i] == rhsLinksB[j])
						{
							found = true;
						}
					}
				}
			}
			if (found)
			{
				remLinksA.push_back(lhsLinksA[i]);
				remLinksB.push_back(lhsLinksB[i]);
				remLinksLabel.push_back(lhsLinksLabel[i]);
			}
		}
		//printf("gocha!\n");
	}

	void clear() 
	{
		name = "";
		active = true;
		lhsSymbolsNames.clear();
		lhsSymbolsTypes.clear();
		lhsLinksA.clear();
		lhsLinksB.clear();
		lhsLinksLabel.clear();
		rhsSymbolsNames.clear();
		rhsSymbolsTypes.clear();
		rhsLinksA.clear();
		rhsLinksB.clear();
		rhsLinksLabel.clear();

		symbolsToCreateName.clear();
		symbolsToCreateType.clear();
		symbolsToRemove.clear();
		addLinksA.clear();
		addLinksB.clear();
		addLinksLabel.clear();
		remLinksA.clear();
		remLinksB.clear();
		remLinksLabel.clear();
		symbolsToRetypeName.clear();
		symbolsToRetypeType.clear();
	}
};

bool parseAGGL(const char *path, AGM *agm, std::vector <AGGLRule> *rules);

class AGM
{
friend class AGMSearch;
public:
	typedef boost::shared_ptr<AGM> SPtr;
	AGM(const AGM::SPtr &src);
	AGM(std::string agglfile, std::string pddlFileFull_, std::string pddlFilePartial_);
	void print();

	bool checkModel(AGMModel::SPtr model);
	bool proposeModel(AGMModel::SPtr model);
	bool updateModel(AGMModelSymbol);

	std::string pddlProblemForTarget(const AGMModel::SPtr &target, int32_t unknowns, const std::string domainName, const std::string problemName);

// private:
	std::string pddlFileFull, pddlFilePartial;
	std::string fullPDDLContent, partialPDDLContent;
	AGMModel currentModel;
	void loadFromFile(std::string pddlFileFull_, std::string pddlFilePartial_);

	AGGLRule &rule(int);
	uint32_t size() { return rules.size(); }
	
	void addAttribute(std::string key, std::string value);
	void addAttribute(const char *key, const char *value);
	void addAttribute(std::string key, int value);
	void addAttribute(const char *key, int value);
	std::map<std::string, std::string> attributes;
private:
	void readFileToString(std::string &file, std::string &content);
	std::vector <AGGLRule> rules;
};


