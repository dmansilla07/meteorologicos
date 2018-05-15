#include "Record.h"

using namespace std;

const int kIniAnualV[] = {14, 45, 79, 122};
const int kIniDailyV[] = {20, 29, 38, 47, 56, 65, 74, 83, 92, 101, 110, 120};

string trimString(string s) {
  int n = s.size();
  int l = 0, r = n-1;
  while (s[l] == ' ') l++;
  while (s[r] == ' ') r--;
  return s.substr(l, r-l+1);
}

bool isTitle(string &s) {
  if (s.size() < 125) return false;
  string targ = s.substr(112);
  if (targ == "NACIONAL AMBIENTAL") return true;
  else return false;
}

string getTitle(string &s) {
  return trimString(s.substr(0, 100));
}

string getAno(string &s) {
  return trimString(s.substr(59, 9));
}

void getLine2(string &s, int veces) {
  while (veces--) getline(cin,s);
}

vector<string> getAnualValues(string &s) {
  vector<string> anualValues;
  for(int i=0; i<11; ++i) {
    if (i%4==0) {
      getline(cin,s);
      while (s.size() <= 130) s = s + " ";
    }
    anualValues.push_back(trimString(s.substr(kIniAnualV[i%4], 20)));
  }
  return anualValues;
}

vector<vector<string> > getDailyValues(string &s) {
  vector<vector<string> >dailyValues(31, vector<string> (31, " "));
  for(int i=0; i<31; ++i) {
    getline(cin, s);
    while (s.size() <= 120) s = s + " ";
    for(int j=0; j<12; ++j) {
      dailyValues[j][i] = trimString(s.substr(kIniDailyV[j], 8));
    }
  }
  return dailyValues;
}

int main() {
  string s;
  while (getline(cin,s)) {
    if (cin.eof()) {
      break;
    }
    
    if (isTitle(s)) {
      string title = getTitle(s);
      getLine2(s, 2);
      string ano = getAno(s);
      getLine2(s, 1);
      vector<string> anualValues = getAnualValues(s);
      cout<<title<<" "<<ano<<endl;
      for(int i=0; i<anualValues.size(); ++i) {
	cout<<anualValues[i]<<endl;
      }
      getLine2(s, 5);
      vector<vector<string> >dailyValues = getDailyValues(s);
      
    }
  }
}
