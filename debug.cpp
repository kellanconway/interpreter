#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// for debugging
void log(int i) {cout << i << "\n";}
void log(bool b) {cout << b << "\n";}
void log(string s) {cout << s << "\n";}
void log(double d) {cout << d << "\n";}

bool stob(string s) {return s == "true";}
char last(string s) {return s[s.size() -1];}

void error(int num, string str) {
    cout << "Error!!\n" << "line: " << num << "\n" << str << "\n";
}
void error(string num, string str) {
    cout << "Error!!\n" << "line: " << num << "\n" << str << "\n";
}

// stroke of genius
char hasQuotes(string s) {
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

string trim(string quotes) {
    quotes.erase(quotes.begin());
    quotes.pop_back();
    return quotes;
}

string typeReturn(string s) 
{
    string b;
    if (s == "true" || s == "false") {
        b = "b"; 
    } else if (hasQuotes(s)) {
        b = "s";
    } else if (isNumber(s)) {
        b = "i";
    }
    return b;
}



// this will turn the entire inner contents of a file into one string
string stringifyFile(ifstream &file) 
{
    string line, total;
    while ( getline(file, line) ) {
        total += line;
    }
    return total;
}

// regex at home, but will specifically detect for commas
vector<string> wordify(string bigString) {
    string word;
    vector<string> total;
    bool quotes = false;

    for (char i : bigString) 
    {   
        if (i == '\"') {
            (quotes)
                ? quotes = false
                : quotes = true;
        }
        if (i == ' ' && !quotes) 
        {   
            if (word[word.length() - 1] == ',') 
            { // checks if the last word ends with a comma, prevents the comma being one behind
                word.pop_back();
                total.push_back(word);
                total.push_back(",");
                word.clear();
            } else {
                total.push_back(word);
                word.clear();
            }
        } else {
            word += i;
        }
    }
    total.push_back(word);
    word.clear();
    return total;

}
// despite this being difficult to gaze with the naked eye, smoothly creates a multidimesional string vector
// it breaks it down into words and sentences, with commas denoting line breaks
vector<vector<string>> sentencize(vector<string> words) {

    vector<vector<string>> sentences;
    vector<string> placeholder;
    
    for (string i : words) {

        if (i == ",") {
            sentences.push_back(placeholder);
            placeholder.clear();
        } else {
            placeholder.push_back(i);
        }

    }
    sentences.push_back(placeholder);
    placeholder.clear();

    return sentences;
}

int main(int argc, char *argv[]) 
{
    ifstream codeFile(argv[1]);
    string fileString = stringifyFile(codeFile);
    if (fileString == "") {error("none", "Theres nothing here");return 1;} // error 1
    vector <vector <string>> fileContent = sentencize(wordify(fileString)); // the entire file, line by line, word by word
    vector< vector <string> > variables; // this vector will take the format { "name", "type", "contents"}     

    vector <string> keywords {
        "say",
        "is"
    };

    // logic for interpretation
    for (
        int lineNum=0; 
        lineNum < fileContent.size(); 
        lineNum++
    )
    {
        vector <string> line = fileContent[lineNum];

        if (line[0] == "say") // print statement
        {
            if (line.size() == 1) {
                error(lineNum, "you opened your mouth but it seems nothing came out");
                return 1;
            }
            for (int b=1; b < line.size(); b++)
            {
                string ab = line[b];
                if (hasQuotes(ab) == '\"') {
                    cout << trim(ab) << " ";
                }
                else if (hasQuotes(ab) == '\'')
                    cout << trim(ab);
                else {
                    cout << "no quotes " ;
                }
            }
            cout << "\n";
            // if (hasQuotes(a[1])) {
            //     cout << trim(a[1]) << "\n";
            // } else {
            //     for (vector <string> b : variables) 
            //     {
            //         if (b[0] == a[1]) {
            //             (b[1] == "s")  
            //                 ? cout << trim(b[2]) << "\n"
            //                 : cout << b[2] << "\n";
            //         }
            //     }
            // }
        }
        else if (line[1] == "is") 
        {
            string type = typeReturn(line[2]);
            variables.push_back({line[0], type, line[2]});
        }
        else {
            error("all of them", "what am I even looking at");
            return 1;
        }
    }
    codeFile.close();
    return 0;
}