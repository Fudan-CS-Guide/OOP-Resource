#include <iostream>
#include <fstream>
#include "FamilyMart.h"

// modify this file to test your logics
// TODO 
using namespace std;
int main() {
    FamilyMart *test_mart = new FamilyMart();
    ofstream output;
    output.open("testlog.txt", ios::out);
    for (int i = 0; i < 31; i++){
        cout << i << endl;
        test_mart->purchase_file("../test_cases/" + to_string(i) + "_pur.txt");
        test_mart->sell_file("../test_cases/" + to_string(i) + "_sel.txt");
        output << i << " day : turnover:" << test_mart->show_turnover() << endl;
    }
    
    output.close();
    delete test_mart;
    
    return 0;
}