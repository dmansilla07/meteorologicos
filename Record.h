#include<bits/stdc++.h>
using namespace std;
#ifndef RECORD_H
#define RECORD_H

class Record {
 public:
  string title;
  string ano;
  vector<string> anualValues;
  vector<vector<string> >dailyValues;
  
  Record(string _title, string _ano, vector<string> _anualValues, vector<vector<string> > _dailyValues);
  Record();
};

Record::Record(string _title, string _ano, vector<string> _anualValues, vector<vector<string> > _dailyValues) {
  title = _title;
  ano = _ano;
  anualValues = _anualValues;
  dailyValues = _dailyValues;
}

Record::Record() {
}

#endif
