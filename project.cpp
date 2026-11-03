#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class Scanner
{
public:
    enum TokenType
    {
        SEMICOLON,
        IF,
        THEN,
        ELSE,
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
        INVALID
    };

    struct Token
    {
        string value;
        string type;
    };

    Token getToken(const string &input)
    {
        TokenType tokenType = INVALID;
        string lower = input;
        for (char &c : lower)
            c = tolower(c);

        if (lower == "if")
            tokenType = IF;
        else if (lower == "then")
            tokenType = THEN;
        else if (lower == "else")
            tokenType = ELSE;
        else if (lower == "end")
            tokenType = END;
        else if (lower == "repeat")
            tokenType = REPEAT;
        else if (lower == "until")
            tokenType = UNTIL;
        else if (lower == "read")
            tokenType = READ;
        else if (lower == "write")
            tokenType = WRITE;
        else if (lower == ":=")
            tokenType = ASSIGN;
        else if (lower == ";")
            tokenType = SEMICOLON;
        else if (lower == "<")
            tokenType = LESSTHAN;
        else if (lower == "=")
            tokenType = EQUAL;
        else if (lower == "+")
            tokenType = PLUS;
        else if (lower == "-")
            tokenType = MINUS;
        else if (lower == "*")
            tokenType = MULT;
        else if (lower == "/")
            tokenType = DIV;
        else if (lower == "(")
            tokenType = OPENBRACKET;
        else if (lower == ")")
            tokenType = CLOSEDBRACKET;
        else if (isIdentifier(lower))
            tokenType = IDENTIFIER;
        else if (isNumber(lower))
            tokenType = NUMBER;

        return {input, tokenTypeToString(tokenType)};
    }

    vector<Token> scanLine(const string &line)
    {
        vector<Token> tokens;
        string currentLexeme;

        for (size_t i = 0; i < line.length(); i++)
        {
            char currentCharacter = line[i];

            if (insideComment)
            {
                if (currentCharacter == '}')
                    insideComment = false;

                continue;
            }

            if (currentCharacter == '{')
            {
                addLexeme(tokens, currentLexeme);
                currentLexeme.clear();
                insideComment = true;
            }
            else if (isspace((currentCharacter)))
            {
                addLexeme(tokens, currentLexeme);
                currentLexeme.clear();
            }
            else if (currentCharacter == ':' &&
                     i + 1 < line.length() &&
                     line[i + 1] == '=')
            {
                addLexeme(tokens, currentLexeme);
                currentLexeme.clear();

                tokens.push_back(getToken(":="));
                i++;
            }
            else if (isSingleCharacterToken(currentCharacter))
            {
                addLexeme(tokens, currentLexeme);
                currentLexeme.clear();

                tokens.push_back(getToken(string(1, currentCharacter)));
            }
            else
            {
                currentLexeme += currentCharacter;
            }
        }

        addLexeme(tokens, currentLexeme);

        return tokens;
    }

private:
    bool insideComment = false;

    void addLexeme(vector<Token> &tokens, const string &lexeme)
    {
        if (!lexeme.empty())
        {
            tokens.push_back(getToken(lexeme));
        }
    }

    bool isSingleCharacterToken(char character)
    {
        return character == ';' ||
               character == '<' ||
               character == '=' ||
               character == '+' ||
               character == '-' ||
               character == '*' ||
               character == '/' ||
               character == '(' ||
               character == ')';
    }

    string tokenTypeToString(TokenType tokenType)
    {
        switch (tokenType)
        {
        case SEMICOLON:
            return "SEMICOLON";
        case IF:
            return "IF";
        case THEN:
            return "THEN";
        case ELSE:
            return "ELSE";
        case END:
            return "END";
        case REPEAT:
            return "REPEAT";
        case UNTIL:
            return "UNTIL";
        case IDENTIFIER:
            return "IDENTIFIER";
        case ASSIGN:
            return "ASSIGN";
        case READ:
            return "READ";
        case WRITE:
            return "WRITE";
        case LESSTHAN:
            return "LESSTHAN";
        case EQUAL:
            return "EQUAL";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULT:
            return "MULT";
        case DIV:
            return "DIV";
        case OPENBRACKET:
            return "OPENBRACKET";
        case CLOSEDBRACKET:
            return "CLOSEDBRACKET";
        case NUMBER:
            return "NUMBER";
        case INVALID:
            return "INVALID";
        default:
            return "invalid";
        }
    }

    bool isNumber(const string &input)
    {
        if (input.empty())
            return false;

        for (char character : input)
        {
            if (!isdigit((character)))
                return false;
        }

        return true;
    }

    bool isIdentifier(const string &input)
    {
        if (input.empty() ||
            !isalpha((input[0])))
        {
            return false;
        }

        for (char character : input)
        {
            if (!isalnum((character)))
                return false;
        }

        return true;
    }
};

void processLine(
    const string &line,
    Scanner &scanner,
    ofstream &outputFile)
{
    vector<Scanner::Token> tokens = scanner.scanLine(line);

    for (const Scanner::Token &token : tokens)
    {
        outputFile << token.value << ", "
                   << token.type << endl;
    }
}

int main()
{
    Scanner scanner;

    string fileName;
    cout << "Enter the input file name: ";
    getline(cin, fileName);

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open input file: "
             << fileName << endl;

        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }

    ofstream outputFile("tokens.txt");

    if (!outputFile)
    {
        cerr << "Error: Could not create tokens.txt." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        processLine(line, scanner, outputFile);
    }

    inputFile.close();
    outputFile.close();

    cout << "Input file processed successfully." << endl;
    cout << "Output written to tokens.txt" << endl;

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}