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

string changeBlank(string s) {
  string res = "";
  for(int i=0; i<s.size(); ++i) {
    if (s[i] == ' ') res += '_';
    else res += s[i];
  }
  return res;
}

string toString(int number) {
  string res = "";
  for(int i=0; i<2; ++i) {
    res = char(number%10 + '0') + res;
    number /= 10;
  }
  return res;
}

string toDate(string year, int month, int day) {
  return year+"/"+toString(month)+"/"+toString(day);
}

Record records[100005];

int main() {
  string s;
  int k = 0;
  set<string> unique_titles;
  ofstream outputFile;
  while (getline(cin,s)) {
    if (cin.eof()) {
      break;
    }
    
    if (isTitle(s)) {
      string title = changeBlank(getTitle(s));
      getLine2(s, 2);
      unique_titles.insert(title);
      string ano = getAno(s);
      getLine2(s, 1);
      vector<string> anualValues = getAnualValues(s);
      cout<<title<<" "<<ano<<endl;
      for(int i=0; i<anualValues.size(); ++i) {
	cout<<anualValues[i]<<endl;
      }
      getLine2(s, 5);
      vector<vector<string> >dailyValues = getDailyValues(s);
      records[k++] = Record(title, ano, anualValues, dailyValues);
    }
  }

  for(set<string>::iterator it = unique_titles.begin(); it != unique_titles.end(); ++it) {
    string cur_title = *it;
    string file_name = cur_title+".txt"; 
    outputFile.open(file_name.c_str());
    for(int i=0; i<k; ++i) {
      if (records[i].title == cur_title) {
	for(int month=0; month<12; ++month) {
	  for(int day=0; day<31; ++day) {
	    if (records[i].dailyValues[month][day] != "") {
	      outputFile<<toDate(records[i].ano, month+1, day+1)<<" "<<records[i].dailyValues[month][day]<<"\n";
	    }
	  }
	}
      }
    }
      outputFile.close();
  }
  
}
