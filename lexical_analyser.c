//Program:
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[10][10] = {"int", "float", "if", "else", "while", "do", "return", "break", "char", "for"};

int iskeyword (char *str) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main(int input[100], int token[20]) {
    int i = 0, j = 0;
    printf("Enter a line of code: \n");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0') {
        if (isalnum(input[i])) {
            token[j++] = input[i];
        } else {
            if (j != 0) {
                token[j] = '\0';
                j = 0;

                if (iskeyword(token)) {
                    printf("Keyword: %s\n", token);
                } else if (isdigit(token[0])) {
                    printf("Number: %s\n", token);
                } else {
                    printf("Identifier: %s\n", token);
                }
            }

            if (input[i] != ' ' && input[i] != '\n') {
                printf("Special Character: %c\n", input[i]);
            }
            i++;
        }
    }
    return 0;
}
