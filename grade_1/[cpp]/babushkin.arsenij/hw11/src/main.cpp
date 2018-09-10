#include "employees.h"

using namespace std;

int main() {
    EmployeesArray all;
    string s;
    while ((cin >> s) && s != "exit") {
        if (s == "load") {
            string fname;
            cin >> fname;
            const char *_fname = fname.c_str();
            ifstream in(_fname, std::ios::binary);
            all.load(in);
        }
        if (s == "list") {
            cout << all;
        }
        if (s == "add") {
            cin >> all;
        }
        if (s == "save") {
            string fname;
            cin >> fname;
            const char *_fname = fname.c_str();
            ofstream out(_fname, std::ios::binary);
            all.save(out);
        }
    }
}