#include "Rule.h"

using namespace std;

Rule::Rule(Predicate headPred)
{
	this->headPred = headPred;
}

void Rule::add_to_preds(Predicate pred)
{
	preds.push_back(pred);
}