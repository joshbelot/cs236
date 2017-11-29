#pragma once
#include "predicate.h"

using namespace std;

class Rule
{
private:
	Predicate headPred;
	vector<Predicate> preds;
public:
	Rule(Predicate head);
	void add_to_preds(Predicate pred);
};