#include "agm_modelSymbols.h"
#include "agm_modelEdge.h"
#include "agm_model.h"

AGMModelSymbol::AGMModelSymbol(AGMModel *model, std::string typ, int32_t id)
{
	init(model, typ, id);
}

AGMModelSymbol::AGMModelSymbol(AGMModel *model, int32_t identifier, std::string typ)
{
	init(model, identifier, typ);
}

AGMModelSymbol::AGMModelSymbol(AGMModel *model, int32_t identifier, std::string typ, std::map<std::string, std::string> atr)
{
	init(model, identifier, typ, atr);
}

AGMModelSymbol::AGMModelSymbol(AGMModel::SPtr model, std::string typ, int32_t id)
{
	init(model.get(), typ, id);
}

AGMModelSymbol::AGMModelSymbol(AGMModel::SPtr model, int32_t identifier, std::string typ)
{
	init(model.get(), identifier, typ);
}

AGMModelSymbol::AGMModelSymbol(AGMModel::SPtr model, int32_t identifier, std::string typ, std::map<std::string, std::string> atr)
{
	init(model.get(), identifier, typ, atr);
}

void AGMModelSymbol::init(AGMModel *model, std::string typ, int32_t id)
{
	if (model == NULL)
	{
		fprintf(stdout, "AGMModelSymbol::init: error: MODEL NULL!!\n");
		exit(-1);
	}

	symbolType = typ;
	if (id==-1)
	{
		identifier = model->getNewId();
// 		printf("Got new ID from pool: %d\n", identifier);
	}
	else
		identifier = id;

	model->insertSymbol(this);

// 	printf("new symbol: %s [%d] (%p)\n", symbolType.c_str(), identifier, this);
}

void AGMModelSymbol::init(AGMModel *model, int32_t id, std::string typ)
{
	if (model == NULL)
	{
		fprintf(stdout, "AGMModelSymbol::init: error: MODEL NULL!!\n");
		exit(-1);
	}

	if (id==-1)
	{
		identifier = model->getNewId();
// 		printf("Got new ID from pool: %d\n", identifier);
	}
	else
		identifier = id;

	symbolType = typ;

	model->insertSymbol(this);

// 	printf("new symbol: %s [%d] (%p)\n", symbolType.c_str(), identifier, this);
}

void AGMModelSymbol::init(AGMModel *model, int32_t id, std::string typ, std::map<std::string, std::string> atr)
{
	if (model == NULL)
	{
		fprintf(stdout, "AGMModelSymbol::init: error: MODEL NULL!!\n");
		exit(-1);
	}

	identifier = id;
	symbolType = typ;
	attributes = atr;

	if (model != NULL)
		model->insertSymbol(this);

// 	printf("new symbol: %s [%d] (%p)\n", symbolType.c_str(), identifier, this);
}



AGMModelSymbol::~AGMModelSymbol()
{
// 	printf("delete symbol: %s [%d] (%p)\n", symbolType.c_str(), identifier, this);
}

bool AGMModelSymbol::operator==(const AGMModelSymbol &p) const
{
	if (symbolType == p.symbolType)
		return true;
	return false;
}

std::string AGMModelSymbol::toString() const
{
	std::ostringstream stringStream;
	stringStream << symbolType << "_" << identifier;
	return stringStream.str();
}

std::string AGMModelSymbol::typeString() const
{
	std::ostringstream stringStream;
	stringStream << symbolType;
  return stringStream.str();
}



void AGMModelSymbol::setType(std::string t)
{
	symbolType = t;
}


void AGMModelSymbol::setIdentifier(int32_t t)
{
	identifier = t;
}

void AGMModelSymbol::setAttribute(std::string a, std::string v)
{
	attributes[a] = v;
}

std::string AGMModelSymbol::getAttribute(std::string a)
{
	return attributes[a];
}



AGMModelSymbol::iterator::iterator(AGMModel *m, AGMModelSymbol *s)
{
	index = -1;
	symRef = s;
	modelRef = m;
}

AGMModelSymbol::iterator::iterator(iterator &iter)
{
	index = iter.index;
	symRef = iter.symRef;
	modelRef = iter.modelRef;
}

AGMModelSymbol::iterator AGMModelSymbol::iterator::begin(AGMModel *m, AGMModelSymbol *s)
{
	iterator iter(m, s);
	iter.index = -1; // -1 is a special case which makes the iterator start over
	iter++;
	return iter;
}

AGMModelSymbol::iterator AGMModelSymbol::iterator::end(AGMModel *m, AGMModelSymbol *s)
{
	iterator iter(m, s);
	iter.index = -10;
	return iter;
}

bool AGMModelSymbol::iterator::operator==(const iterator &rhs)
{
	return index == rhs.index;
}

bool AGMModelSymbol::iterator::operator!=(const iterator &rhs)
{
	return index != rhs.index;
}

AGMModelSymbol::iterator AGMModelSymbol::iterator::operator++()
{
	if (modelRef == NULL) AGMMODELEXCEPTION(std::string("Attempting to use uninitialized iterator!"));
// printf("AGMModelSymbol::iterator +++++++++++ %d (there are %d)\n", index, (int)modelRef->edges.size());
	// The end can't be incremented
	if (index == -10)
		return *this;

	// Now, increment until we reach a related edge
	const int32_t t=modelRef->edges.size();
	while (index < t-1)
	{
		index++;
// 		printf("++   (%d)----->(%d)\n", modelRef->edges[index].symbolPair.first, modelRef->edges[index].symbolPair.second);
		if (modelRef->edges[index].symbolPair.first == symRef->identifier or modelRef->edges[index].symbolPair.second == symRef->identifier)
		{
// 			printf("yes\n");
			return *this;
		}
		else
		{
// 			printf("nope\n");
		}
	}
// 	printf("wooooooooooooooooo %d   (there are %d)\n", index, (int)modelRef->edges.size());
	// Didn't find any edge
	index = -10;
	return *this;
}

AGMModelSymbol::iterator AGMModelSymbol::iterator::operator++(int32_t times)
{
	AGMModelSymbol::iterator it = *this;
	operator++();
	return it;
}

AGMModelEdge AGMModelSymbol::iterator::operator*()
{
	if (modelRef == NULL) AGMMODELEXCEPTION(std::string("Attempting to use uninitialized iterator!"));
	return modelRef->edges[index];
}

AGMModelEdge AGMModelSymbol::iterator::operator->()
{
	if (modelRef == NULL) AGMMODELEXCEPTION(std::string("Attempting to use uninitialized iterator!"));
	return modelRef->edges[index];
}

