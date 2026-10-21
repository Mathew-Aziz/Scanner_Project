#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;


class Scanner
{
public:
    enum TokenType
    {
        SEMICOLON,
        IF,
        THEN,
        END,
        REPEAT,
        UNTIL,
        IDENTIFIER,
        ASSIGN,
        READ,
        WRITE,
        LESSTHAN,
        EQUAL,
        PLUS,
        MINUS,
        MULT,
        DIV,
        OPENBRACKET,
        CLOSEDBRACKET,
        NUMBER,
    };

public:
    Scanner(TokenType s)
    {
        currentStatus = s;
    }
    
    bool isNumber(string s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}
    void getToken(string input)
    {
        {
        }
    }
};


int main()
{
    Scanner p(Scanner::IF);
    p.getToken("if");

    return 0;
}
