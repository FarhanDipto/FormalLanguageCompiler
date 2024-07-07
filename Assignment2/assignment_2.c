#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    SEPARATOR,
    PARENTHESIS,
    NUMBER,
    OTHER
} TokenType;

typedef struct {
    char lexeme[100];  
    TokenType type;
} Token;

TokenType classifyToken(const char *lexeme) {
    if (strcmp(lexeme, "if") == 0 || strcmp(lexeme, "else") == 0 || strcmp(lexeme, "while") == 0) {
        return KEYWORD;
    } else if (isalpha(lexeme[0])) {
        return IDENTIFIER;
    } else if (lexeme[0] == '+' || lexeme[0] == '-' || lexeme[0] == '*' || lexeme[0] == '/') {
        return OPERATOR;
    } else if (lexeme[0] == '(' || lexeme[0] == ')' || lexeme[0] == '{' || lexeme[0] == '}') {
        return PARENTHESIS;
    } else if (lexeme[0] == ',' || lexeme[0] == ';') {
        return SEPARATOR;
    } else if (isdigit(lexeme[0])) {
        return NUMBER;
    } else {
        return OTHER;
    }
}

void printToken(const Token *token, FILE *output1, FILE *output2) {
    fprintf(output1, "%s ", token->lexeme);
    switch(token->type) {
        case KEYWORD: fprintf(output2, "[kw %s] ", token->lexeme); break;
        case IDENTIFIER: fprintf(output2, "[id %s] ", token->lexeme); break;
        case OPERATOR: fprintf(output2, "[op %s] ", token->lexeme); break;
        case SEPARATOR: fprintf(output2, "[sep %s] ", token->lexeme); break;
        case PARENTHESIS: fprintf(output2, "[par %s] ", token->lexeme); break;
        case NUMBER: fprintf(output2, "[num %s] ", token->lexeme); break;
        case OTHER: fprintf(output2, "[unkn %s] ", token->lexeme); break;
    }
}

void tokenize(FILE *input, FILE *output1, FILE *output2) {
    char buffer[100];  
    int bufferIndex = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        if (isspace(c) || c == ';' || c == ',' || c == '=') {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';

                Token token;
                strcpy(token.lexeme, buffer);
                token.type = classifyToken(buffer);

                printToken(&token, output1, output2);

                bufferIndex = 0;
            }
            if (c == ';' || c == ',' || c == '=') {
                fprintf(output1, "%c ", c);
                fprintf(output2, "[sep %c] ", c);
            }
        } else {
            buffer[bufferIndex++] = c;
        }
    }

    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';

        Token token;
        strcpy(token.lexeme, buffer);
        token.type = classifyToken(buffer);

        printToken(&token, output1, output2);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output1 = fopen("output1.txt", "w");
    FILE *output2 = fopen("output2.txt", "w");

    if (input == NULL || output1 == NULL || output2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    tokenize(input, output1, output2);

    fclose(input);
    fclose(output1);
    fclose(output2);

    return 0;
}
