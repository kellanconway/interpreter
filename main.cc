#include "./head.hh"


int main(int argc, char *argv[]) 
{
    ifstream codeFile(argv[1]);
    vector <vector<string>> fileContent = chop(codeFile); // [i] is sentence, [i][i] is a word
    vector <vector<string>> variables; // { "name", "type", "contents"}     
    vector <string> keywords {
        "say",
        "is"
    };

    // error checking
    if (fileContent.size() == 0) {
        error("none", "Theres nothing here");
        return 1;
    }
    for (int a=0; a < fileContent.size(); a++) {
        vector <string> aa = fileContent[a];
        for (string b : aa) {
            if (b == "") {
                error(a + 1, "inefficient use of white space, do better");
                return 1;
            }
        }
    }
    


    // logic for interpretation
    for (
        int lineNum=0; 
        lineNum < fileContent.size(); 
        lineNum++)
    {
        vector <string> line = fileContent[lineNum];

        if (line[0] == "say") // print statement
        {
            if (line.size() == 1) {
                error(lineNum + 1, "you opened your mouth but it seems nothing came out");
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
                else { // TODO: finish print statement
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