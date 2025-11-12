#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 5

char *NT[N] = {"E", "E'", "T", "T'", "F"};

char *G[N][3] = {
    {"TE'", "NULL"},
    {"+TE'", "e", "NULL"},
    {"FT'", "NULL"},
    {"*FT'", "e", "NULL"},
    {"(E)", "id", "NULL"}
};

char FIRST[N][10];
int count[N];

int idx(char *xs) {
    for (int i = 0; i < N; i++) {
        if (strcmp(NT[i], xs) == 0) return i;
    }
    return -1;
}

bool isNT(char *xs) {
    return idx(xs) != -1;
}

void addFirst(int i, char c) {
    for (int j = 0; j < count[i]; j++) {
        if (FIRST[i][j] == c) return;
    }
    FIRST[i][count[i]++] = c;
}

void computeFirst(int i) {
    for (int p = 0; G[i][p] != NULL; p++) {
        char *xprod = G[i][p];
        char sym[3];
        int j = 0;
        bool allEps = true;

        while (xprod[j] != '\0') {
            if (xprod[j+1] == '\'') {
                sym[0] = xprod[j];
                sym[1] = xprod[j+1];
                sym[2] = '\0';
                j += 2;
            } else {
                sym[0] = xprod[j];
                sym[1] = '\0';
                j += 1;
            }

            if (strcmp(sym, "e") == 0) {
                addFirst(i, 'e');
                break;
            }

            if (!isNT(sym)) {
                char term = (strcmp(sym, "id") == 0) ? '!' : sym[0];
                addFirst(i, term);
                allEps = false;
                break;
            }

            int k = idx(sym);
            if (k != -1) {
                if (count[k] == 0) {
                    computeFirst(k);
                }

                bool hasEps = false;
                for (int m = 0; m < count[k]; m++) {
                    if (FIRST[k][m] == 'e') {
                        hasEps = true;
                    } else {
                        addFirst(i, FIRST[k][m]);
                    }
                }

                if (!hasEps) {
                    allEps = false;
                    break;
                }
            }
        }

        if (allEps) {
            addFirst(i, 'e');
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        computeFirst(i);
    }

    printf("Output:\n");
    for (int i = 0; i < N; i++) {
        printf("FIRST (%s) = { ", NT[i]);
        for (int j = 0; j < count[i]; j++) {
            char current_char = FIRST[i][j];

            if (current_char == '!') {
                printf("id");
            } else {
                printf("%c", current_char);
            }

            if (j < count[i] - 1) {
                printf(", ");
            }
        }
        printf(" }\n");
    }

    return 0;
}
