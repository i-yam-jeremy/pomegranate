grammar Lsystem;		
lsystem: initiator=commands ',' lrule*;
lrule: ID '=' commands;
commands: (sym | stackCommand)*;
sym: ID | MINUS | PLUS;
stackCommand: LBRACK (sym | stackCommand)* RBRACK;

MINUS	: '-';
PLUS	: '+';
LBRACK	: '[';
RBRACK	: ']';
ID	: [A-Z][a-z]*;
INT     : [0-9]+ ;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
