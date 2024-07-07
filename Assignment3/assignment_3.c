#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char identifier[50];
    char type[50];
    char data[50];
    char range[50];
    char val[50];
} Table;

int main() {
    FILE *source = fopen("input.txt", "r");
    FILE *destination = fopen("output.txt", "w");
    if (source == NULL || destination == NULL) {
        fprintf(stderr, "Unable to open the file\n");
        return 1;
    }

    char tokenCategory[20], token[20];

    while (fscanf(source, " [%[^]]] [%[^]]]", tokenCategory, token) != EOF) {
        if (strcmp(tokenCategory, "id") != 0) {
            fprintf(destination, "[%s] [%s] ", tokenCategory, token);
        }
    }

    fclose(source);
    fclose(destination);

    // Now, let's generate the symbol table
    source = fopen("output1.txt", "r");
    Table entries[10]; 
    int index = 0;

    while (fscanf(source, " [%[^]]] [%[^]]]", tokenCategory, token) != EOF) {
        if (strcmp(tokenCategory, "id") == 0) {
            strcpy(entries[index].identifier, token);
            strcpy(entries[index].type,"var");
            strcpy(entries[index].range ,"global"); // Assuming global for simplicity
            index++;
        }
        else if(strcmp(tokenCategory,"num")==0){
            strcpy(entries[index-1].val ,token);
        }
        else if(strcmp(tokenCategory,"kw")==0){
            strcpy(entries[index-1].data ,token);
        }
     }

     fclose(source);

     printf("Symbol Table:\n");
     printf("Name\tId Type\tData Type\tScope\tValue\n");

     for(int i=0; i<index; i++) {
         printf("%s\t%s\t%s\t%s\t%s\n", entries[i].identifier,entries[i].type,entries[i].data,entries[i].range,entries[i].val);
     }

     return 0;
}
