// This class needs to implement the three relational algebra methods of
// select, project, and rename.
// Queries are made up of these three elements and a table.
#include "relation.h"

Relation::Relation(){}
Relation::Relation(string name){}
Relation::Relation(string name, Schema schems){}
Relation::Relation(string name, set<Tuple> tups){}
Relation::Relation(string name, Schema schems, set<Tuple> tups){}

Relation Relation::select(int posComp, int posVal)
{

}

Relation Relation::select(int posComp, string Val)
{

}

Relation Relation::project(vector<int> &v)
{

}

Relation Relation::finalProject(Predicate finProj)
{

}

Relation Relation::rename(Schema &schems)
{

}

void Relation::uni(Relation &r)
{

}

Relation Relation::join(Relation &r)
{

}

string Relation::printMatches()
{

}

string Relation::schemToString()
{

}

string Relation::tupsToString()
{

}

string Relation::getName()
{

}

set<Tuple> Relation::getTups()
{

}

int Relation::getLength()
{
	
}