
#include "stdafx.h"
#include <iostream>
#include "Token.h"
#include "Parse.h"

using namespace std;

int main() 
{
    Scan scanner;
    string s = string("C:\\Users\\bluec\\Downloads\\woocode.txt");
    // cout << "input the code file: ";
    // cin >> s;
    scanner.srcfile = s;
    scanner.outfile = "out.txt";
    scanner.getToken();
    Parse ptest(scanner.list_token, "asm.txt", "main.txt");
    ptest.test();

    return 0;
}

