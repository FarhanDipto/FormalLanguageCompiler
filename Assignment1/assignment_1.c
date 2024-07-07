#include <stdio.h>

int main(void) {
    FILE *fp1, *fp2;
    int c;
    int multiLineComment = 0;
    int singleLineComment = 0;
    int stringLiteral = 0;

    fp1 = fopen("input.c", "r");
    fp2 = fopen("output.txt", "w");

    if (!fp1) {
        printf("Unable to open the source file.\n");
        return 0;
    }

    if (!fp2) {
        printf("Unable to open the output file.\n");
        return 0;
    }

    while((c = fgetc(fp1)) != EOF) {
        if (multiLineComment && c == '*' && fgetc(fp1) == '/') {
            multiLineComment = 0;
        } else if (singleLineComment && c == '\n') {
            singleLineComment = 0;
        } else if (!multiLineComment && !singleLineComment && c == '"') {
            stringLiteral = !stringLiteral;
            fputc(c, fp2);
        } else if (!multiLineComment && !singleLineComment && c == '/' && fgetc(fp1) == '*') {
            multiLineComment = 1;
        } else if (!multiLineComment && !singleLineComment && c == '/' && fgetc(fp1) == '/') {
            singleLineComment = 1;
        } else if (!multiLineComment && !singleLineComment && !stringLiteral && (c == ' ' || c == '\t' || c == '\n')) {
            continue;
        } else if (!multiLineComment && !singleLineComment) {
            fputc(c, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("Comments and whitespace have been removed from the source file.\n");

    return 0;
}


