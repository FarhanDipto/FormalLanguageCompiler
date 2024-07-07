#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void E();
void T();
void F();
bool isD(char);
bool isN(char);

char str[1000];
int i, l;
bool f;

void E() {
    T();
    if (str[i] == '+') {
        i++;
        T();
    }
    else if (str[i] == '-') {
        i++;
        T();
    }
}

void T() {
    F();
    if (str[i] == '*') {
        i++;
        F();
    }
    else if (str[i] == '/') {
        i++;
        F();
    }
}

void F() {
    if (isD(str[i]) || isN(str[i])) {
        i++;
    }
    else if (str[i] == '(') {
        i++;
        E();
        if (str[i] == ')') {
            i++;
            E();
        }
    }
}

bool isD(char c) {
    return (c >= 'a' && c <= 'e');
}

bool isN(char c) {
    return isdigit(c);
}

int main() {
  while(1){
    printf("Enter a string to check: ");
    scanf("%s", str);

    i = 0;
    l = strlen(str);
    f = true;

    E();

    if (i == l && f) {
        printf("The input string follows the grammar.\n");
    } else {
        printf("The input string does not follow the grammar.\n");
    }
  }
    return 0;
}


