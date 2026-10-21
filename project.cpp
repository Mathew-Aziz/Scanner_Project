#include <iostream>
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
    TokenType getToken(string input)
    {
        if (input == "if")
            return IF;
        if (input == "then")
            return THEN;
        if (input == "end")
            return END;
        if (input == "repeat")
            return REPEAT;
        if (input == "until")
            return UNTIL;
        if (input == "read")
            return READ;
        if (input == "write")
            return WRITE;
        if (input == ":=")
            return ASSIGN;
        if (input == ";")
            return SEMICOLON;
        if (input == "<")
            return LESSTHAN;
        if (input == "=")
            return EQUAL;

        if (isIdentifier(input))
            return IDENTIFIER;
        if (isNumber(input))
            return NUMBER;
    }

    bool isNumber(string s)
    {
        if (s.empty())
            return false;

        for (char c : s)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }

        return true;
    }

    bool isIdentifier(string input)
    {
        if (input.empty() || !isalpha(input[0]))
            return false;

        for (char c : input)
        {
            if (!isalnum(c))
                return false;
        }

        return true;
    }
};

int main()
{
    Scanner p;

    Scanner::TokenType token = p.getToken("if");

    cout << token << endl; // Prints the enum's integer value

    return 0;
}
