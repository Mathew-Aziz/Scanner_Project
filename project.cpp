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

    Token getToken(const string& input)
    {
        TokenType tokenType = INVALID;

        if (input == "if")
            tokenType = IF;
        else if (input == "then")
            tokenType = THEN;
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

    vector<Token> scanLine(const string& line)
    {
        vector<Token> tokens;
        string currentLexeme;

        for (size_t i = 0; i < line.length(); i++)
        {
            char currentCharacter = line[i];

            if (isspace(static_cast<unsigned char>(currentCharacter)))
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
    void addLexeme(vector<Token>& tokens, const string& lexeme)
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
            return "semicolon";
        case IF:
            return "if";
        case THEN:
            return "then";
        case END:
            return "end";
        case REPEAT:
            return "repeat";
        case UNTIL:
            return "until";
        case IDENTIFIER:
            return "Identifier";
        case ASSIGN:
            return "assign";
        case READ:
            return "read";
        case WRITE:
            return "write";
        case LESSTHAN:
            return "less-than";
        case EQUAL:
            return "equal";
        case PLUS:
            return "plus";
        case MINUS:
            return "minus";
        case MULT:
            return "multiply";
        case DIV:
            return "divide";
        case OPENBRACKET:
            return "open-bracket";
        case CLOSEDBRACKET:
            return "closed-bracket";
        case NUMBER:
            return "number";
        case INVALID:
            return "invalid";
        default:
            return "invalid";
        }
    }

    bool isNumber(const string& input)
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

    bool isIdentifier(const string& input)
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
    const string& line,
    Scanner& scanner,
    ofstream& outputFile)
{
    vector<Scanner::Token> tokens = scanner.scanLine(line);

    for (const Scanner::Token& token : tokens)
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

    int choice;

    cout << "Choose input method:" << endl;
    cout << "1. Read source code from a file" << endl;
    cout << "2. Enter source code manually" << endl;
    cout << "Enter your choice: ";

    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
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
    }
    else if (choice == 2)
    {
        string line;

        cout << endl;
        cout << "Enter source-code lines one at a time." << endl;
        cout << "Press Enter on an empty line to finish input." << endl;
        cout << "-----------------------------------------------" << endl;

        while (true)
        {
            cout << "> ";
            getline(cin, line);

            if (line.empty())
                break;

            processLine(line, scanner, outputFile);
        }

        cout << "Manual input processed successfully." << endl;
    }
    else
    {
        cerr << "Error: Invalid choice." << endl;
        return 1;
    }

    outputFile.close();

    cout << "Output written to tokens.txt" << endl;

    return 0;
}