#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &name, vector<int> &score, vector<char> &grade ){
    string text;
    char format [] = "%[^:]: %d %d %d";
    ifstream source;
    source.open(filename);

    char nameuse[50];
    int Score1,Score2,Score3;
    while(getline(source,text)){
        const char *A=text.c_str();
        sscanf(A,format,nameuse,&Score1,&Score2,&Score3);
        name.push_back(string(nameuse));
        score.push_back(int(Score1+Score2+Score3));
        grade.push_back(score2grade(int(Score1+Score2+Score3)));
    }
}

void getCommand(string &comm,string &keyy){
    string text;
    char com[50],kee[50];
    char format[] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,text);
    const char *text1 = text.c_str();
    sscanf(text1,format,com,kee);
    comm = com;
    keyy = kee;
}

void searchName(vector<string> name ,vector<int> score,vector<char> grade,string key){
    int count = 0;
    cout << "---------------------------------" << "\n";
    for(int n = 0; n  < int(name.size()) ; n++){
        if (toUpperStr(name.at(n)).compare(toUpperStr(key)) == 0){
        cout << name.at(n) << "'s score = " << score.at(n) << "\n";  
        cout << name.at(n) << "'s grade = " << grade.at(n) << "\n";
        }
        else count++;
    }
    if(count == 26) cout << "Cannot found." << "\n";
    cout << "---------------------------------" << "\n";
}

void searchGrade(vector<string> name ,vector<int> score,vector<char> grade,string key){
    cout << "---------------------------------" << "\n";
    for(int n = 0; n  < int(name.size()) ; n++)
        if (grade.at(n) == (key[0])){
           cout << name.at(n) << " (" << score.at(n) << ")" << "\n";
        }
    cout << "---------------------------------" << "\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}