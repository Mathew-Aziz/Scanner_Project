#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

        if (input == "if")
            tokenType = IF;
        else if (input == "then")
            tokenType = THEN;
        else if (input == "else")
            tokenType = ELSE;
        else if (input == "end")
            tokenType = END;
        else if (input == "repeat")
            tokenType = REPEAT;
        else if (input == "until")
            tokenType = UNTIL;
        else if (input == "read")
            tokenType = READ;
        else if (input == "write")
            tokenType = WRITE;
        else if (input == ":=")
            tokenType = ASSIGN;
        else if (input == ";")
            tokenType = SEMICOLON;
        else if (input == "<")
            tokenType = LESSTHAN;
        else if (input == "=")
            tokenType = EQUAL;
        else if (input == "+")
            tokenType = PLUS;
        else if (input == "-")
            tokenType = MINUS;
        else if (input == "*")
            tokenType = MULT;
        else if (input == "/")
            tokenType = DIV;
        else if (input == "(")
            tokenType = OPENBRACKET;
        else if (input == ")")
            tokenType = CLOSEDBRACKET;
        else if (isIdentifier(input))
            tokenType = IDENTIFIER;
        else if (isNumber(input))
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
            else if (isspace(static_cast<unsigned char>(currentCharacter)))
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
            if (!isdigit(static_cast<unsigned char>(character)))
                return false;
        }

        return true;
    }

    bool isIdentifier(const string &input)
    {
        if (input.empty() ||
            !isalpha(static_cast<unsigned char>(input[0])))
        {
            return false;
        }

        for (char character : input)
        {
            if (!isalnum(static_cast<unsigned char>(character)))
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
    ofstream outputFile("tokens.txt");

    if (!outputFile)
    {
        cerr << "Error: Could not create tokens.txt." << endl;
        return 1;
    }

    string fileName;
    cout << "Enter the input file name: ";
    getline(cin, fileName);

    ifstream inputFile(fileName);

    if (!inputFile)
    {
        cerr << "Error: Could not open input file: "
             << fileName << endl;

        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        processLine(line, scanner, outputFile);
    }

    inputFile.close();

    cout << "Input file processed successfully." << endl;
    outputFile.close();

    cout << "Output written to tokens.txt" << endl;

    return 0;
}