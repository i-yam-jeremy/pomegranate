grammar Lsystem;		
lsystem: generations=INT ',' initiator=commands ',' lrule (',' lrule)*;
lrule: name=ID '=' body=commands;
commands: (sym | subruleSym)*;
sym: MINUS | PLUS | LBRACK | RBRACK;
subruleSym: ID;

MINUS	: '-';
PLUS	: '+';
LBRACK	: '[';
RBRACK	: ']';
ID	: [A-Z][a-z]*;
INT     : [0-9]+ ;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
