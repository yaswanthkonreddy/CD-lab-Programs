//calc.l
% {
#include <stdio.h>
#include "y.tab.h"
#include <stdlib.h> // Implied for atoi
% }

% %

[0-9]+  { yylval = atoi(yytext); return DIGIT; }
\n      { return yytext[0]; }
.       { return yytext[0]; }

% %

//calc.y
Program:
% {
#include <stdio.h>
#include "y.tab.h"
% }
% %
/*
E -> E+E / E*E / (E) / DIGIT
*/
% union
{
    int dval;
}

% token <dval> DIGIT
% start <dval> expr
% type <dval> expr
% type <dval> term
% type <dval> factor

% %

line: expr '\n' { printf("%d\n", $1); exit(0); }
    ;

expr: expr '+' term { $$ = $1 + $3; }
    | term
    ;

term: term '*' factor { $$ = $1 * $3; }
    | factor
    ;

factor: '(' expr ')' { $$ = $2; }
      | DIGIT
      ;

% %

int main()
{
    yyparse();
}

void yyerror (char *s)
{
    printf("%s\n", s);
}
