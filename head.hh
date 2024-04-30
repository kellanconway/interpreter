#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// print functions for debugging
void pl(string str) {
    cout << str << "\n";
}
void logv(vector <string> vect) {
    cout << "{ ";
    for (string i : vect) {
        cout << "\"" << i << "\" "; 
    }
    cout << "}\n";
}


// nice useful little tools

bool stob(string s) {return s == "true";}
char last(string s) {return s[s.size() -1];}

// TODO: make a function that turn a integer into a readable phrase
string numberWord(int num) {
    return "a";
}

void error(int num, string str) {
    cout << "Error\n" << "line " << num << "\n" << str << "\n";
}
void error(string num, string str) {
    cout << "Error\n" << "line " << num << "\n" << str << "\n";
}

char hasQuotes(string s) { // returns the quote type but is false if theres none
    if (s[0] == last(s) && s[0] == '\"' 
     || s[0] == last(s) && s[0] == '\'') {
        return s[0];
    }
    else {return '\0';}
}
bool isNumber(string input) {
    bool a = true;
    for (char i : input) {
        if (isdigit(i)) 
        {} else 
        {a = false;}
    }
    return a;
}

string trim(string str) {
    str.erase(str.begin());
    str.pop_back();
    return str;
}
string typeReturn(string str) 
{
    string b;
    if (str == "true" || str == "false") {
        b = "b"; 
    } else if (hasQuotes(str)) {
        b = "s";
    } else if (isNumber(str)) {
        b = "i";
    }
    return b;
}

// my magnum opus
vector <vector <string>> chop(ifstream &file) { 
    vector <vector <string>> sentences;
    vector <string> words;
    string word;
    string line;
    bool quotes = false;

    while ( getline(file, line) ) {
        for (char i : line) {
            if (i == '\"') {
                (quotes)
                    ? quotes = false
                    : quotes = true;
            }
            if (i == ' ' && !quotes) {
                words.push_back(word);
                word.clear();
            }
            else {
                word += i;
            }
        }
        words.push_back(word);
        word.clear();
        sentences.push_back(words);
        words.clear();
    }
    return sentences;
}