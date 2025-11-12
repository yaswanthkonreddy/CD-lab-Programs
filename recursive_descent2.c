#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int pos = 0;
char lookahead;

void S();
void L();
void LPrime();
void match(char ch);

void match(char ch) {
    if (lookahead == ch) {
        lookahead = input[++pos];
    } else {
        printf("Error: '%c' at position %d\n", lookahead, pos);
    }
}

void S() {
    if (lookahead == '{') {
        match('{');
        L();
        match('}');
    } else if (lookahead == 'a') {
        match('a');
    } else {
        printf("Error: '%c' at position %d\n", lookahead, pos);
    }
}

void L() {
    S();
    LPrime();
}

void LPrime() {
    if (lookahead == ',') {
        match(',');
        S();
        LPrime();
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    lookahead = input[pos];

    S();

    if (lookahead == '#') {
        printf("Parsing successful\n");
    } else {
        printf("Parsing Failed\n");
    }

    return 0;
}
