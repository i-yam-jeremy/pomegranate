grammar Lsystem;		
lsystem: initiator=commands ',' lrule*;
lrule: name=ID '=' body=commands;
commands: (sym | subruleSym | stackCommand)*;
sym: MINUS | PLUS;
subruleSym: ID;
stackCommand: LBRACK cmd=commands RBRACK;

MINUS	: '-';
PLUS	: '+';
LBRACK	: '[';
RBRACK	: ']';
ID	: [A-Z][a-z]*;
INT     : [0-9]+ ;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
