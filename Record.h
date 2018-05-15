#include<bits/stdc++.h>
using namespace std;
#ifndef RECORD_H
#define RECORD_H

class Record {
  string title;
  string ano;
  vector<string> anualValues;
  vector<vector<string> >dailyValues;
  vector<string> totalValues;
  public:
    Record(string _title, string _ano);
  
};

Record::Record(string _title, string _ano) {
  title = _title;
  ano = _ano;
}

#endif
