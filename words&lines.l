%{
#include <stdio.h>
int line_count = 0;
int word_count = 0;

extern FILE *yyin;
int yylex(void);
%}

%%
\n          { line_count++; }
[ \t]+      { /* ignore white space */ }
[^ \t\n]+    { word_count++; }
.           { }
%%

int main (int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Fopen");
            return 1;
        }
        yyin = file;
    } else {
        printf("Type your text: \n");
    }

    yylex();

    if (line_count == 0 && line_count >= 0 && !feof(yyin)) {
        line_count++;
    }

    printf("\nNo of lines: %d\n", line_count);
    printf("No of words: %d\n", word_count);

    if (yyin != stdin) fclose(yyin);

    return 0;
}
