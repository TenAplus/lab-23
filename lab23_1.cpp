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

void importDataFromFile(const string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string name;
    int score;
    
    if (!file){
        cout << "Error opening file!" << endl;
        exit(1);
    }
    
    while (file >> name >> score){
        names.push_back(name);
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
    file.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command: "<<endl;
    cin >> command;
    cin >> key;
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    cout <<"---------------------------------"<<endl;
    for (unsigned i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == key) {
            
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout <<"---------------------------------"<<endl;

}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    char grade = key[0];  // Assuming the user inputs a single character grade
    bool found = false;

    for (unsigned i = 0; i < grades.size(); i++) {
        if (grades[i] == grade) {
            cout << "Name: " << names[i] << ", Score: " << scores[i] << ", Grade: " << grades[i] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with grade " << grade << "!" << endl;
    }
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
