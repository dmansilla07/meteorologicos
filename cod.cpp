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

string getEstacion(string &s) {
  return trimString(s.substr(104,9));
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

string toString(int number, int x) {
  string res = "";
  for(int i=0; i<x; ++i) {
    res = char(number%10 + '0') + res;
    number /= 10;
  }
  return res;
}

int toInt(string &s) {
  int x = 0;
  for(int i=0; i<s.size(); ++i) {
    x = x*10 + (s[i]-'0');
  }
  return x;
}

string toDate(string year, int month, int day) {
  return year+"/"+toString(month, 2)+"/"+toString(day, 2);
}

bool isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool isValidDay(unsigned short year,unsigned short month,unsigned short day){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}

string getFirstValue(string s) {
  string res = "";
  for(int i=0; i<s.size(); ++i) {
    if (s[i] == ' ') return res;
    res += s[i];
  }
  return res;
}


Record records[100005];

int main() {
  string s;
  int k = 0;
  set<string> unique_titles;
  set<string> unique_estacion;
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
      string estacion = getEstacion(s);
      getLine2(s, 1);
      vector<string> anualValues = getAnualValues(s);
      cout<<title<<" "<<ano<<endl;
      for(int i=0; i<anualValues.size(); ++i) {
	//	cout<<anualValues[i]<<endl;
      }
      getLine2(s, 5);
      vector<vector<string> >dailyValues = getDailyValues(s);
      records[k++] = Record(title, estacion, ano, anualValues, dailyValues);
    }
  }

  for(set<string>::iterator it = unique_titles.begin(); it != unique_titles.end(); ++it) {
    unique_estacion.clear();
    string cur_title = *it;
    for(int i=0; i<k; ++i) {
      if (records[i].title == cur_title) {
	unique_estacion.insert(records[i].estacion);
	//cout<<records[i].estacion<<endl;
      }
    }
    
    for(set<string>::iterator it2 = unique_estacion.begin(); it2 != unique_estacion.end(); ++it2) {
      string cur_estacion = *it2;
      //cout<<cur_estacion<<endl;
      string file_name = cur_title+"EST_"+cur_estacion+".txt"; 
      // cout<<file_name<<endl;
      outputFile.open(file_name.c_str());
      outputFile<<cur_estacion<<"\n";
      for(int year = 1979; year<= 2018; ++year) {
	bool encontro = 0;
	for(int i=0; i<k; ++i) {
	  if (records[i].ano == toString(year, 4) && records[i].title == cur_title && records[i].estacion == cur_estacion) {
	    encontro = 1;
	    for(int month=0; month<12; ++month) {
	      for(int day=0; day<31; ++day) {	
	        if (isValidDay(year, month+1, day+1) && records[i].dailyValues[month][day] != "") {
	          outputFile<<toDate(records[i].ano, month+1, day+1)<<" "<<getFirstValue(records[i].dailyValues[month][day])<<"\n";
	        } else {
	          if (isValidDay(year, month+1, day+1))
		    outputFile<<toDate(records[i].ano, month+1, day+1)<<" "<<" "<<"\n";
	        }
	      }
	    }
	  }
	}
	if (encontro == 0) {
	  for(int month=0; month<12; ++month) {
	      for(int day=0; day<31; ++day) {	
		if(isValidDay(year, month+1, day+1))
		  outputFile<<toDate(toString(year, 4), month+1, day+1)<<" "<<" "<<"\n";
	      }
	    }
	}
      }
      outputFile.close();
    }
    /*
    string file_name = cur_title+"EST_"+estacion".txt"; 
    outputFile.open(file_name.c_str());
    outputFile<<estacion<<"\n";
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
    }*/
    outputFile.close();
  }
  
}
