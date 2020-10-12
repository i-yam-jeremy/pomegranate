grammar Lsystem;		
lsystem: 'generations' '=' generations=INT ',' 'angle' '=' angle=(FLOAT|INT) ',' 'init' '=' initiator=commands ',' 'rules' ':' lrule (',' lrule)*;
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
FLOAT	: [0-9]+.[0-9]+;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
