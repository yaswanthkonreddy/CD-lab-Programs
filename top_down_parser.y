//parse.y
Program:
// parser.y
% {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror (const char *s);
int yylex();
% }

% token ID
% token PLUS STAR LPAREN RPAREN

%%

E: E PLUS T_Prime
 | T E_Prime
 ;

E_Prime: PLUS T E_Prime
 | /* epsilon */
 ;

T: F T_Prime
 ;

T_Prime: STAR F T_Prime
 | /* epsilon */
 ;

F: LPAREN E RPAREN
 | ID
 ;

line: E '\n' { printf("Valid Expression \n"); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "yyerror: %s\n", s);
}

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

//lexer.l
// lexer.l
% {
#include "y.tab.h"
#include <stdio.h>
% }

%%

"+" { return PLUS; }
"*" { return STAR; }
"(" { return LPAREN; }
")" { return RPAREN; }
[a-zA-Z][a-zA-Z0-9]* { return ID; }
" " | \t { /* ignore spaces */ }
\n { return '\n'; }
. { yyerror("Invalid character"); }

%%

int yywrap () {
    return 1;
}
*/
