#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Tuple
{
public:
  vector<string> tuple;
  unsigned int size;
  Tuple();
  void insert(string s);
  bool operator< (const Tuple& r) const
  {
    return tuple < r.tuple;
  }
};