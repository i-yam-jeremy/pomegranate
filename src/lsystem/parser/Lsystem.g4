grammar Lsystem;		
lsystem: 'generations' '=' generations=INT ',' 'angle' '=' angle=(FLOAT|INT) ',' 'init' '=' initiator=commands ',' 'rules' ':' lrule (',' lrule)*;
lrule: name=ID '=' body=commands;
commands: (sym | subruleSym)*;
sym: LEFT | RIGHT | ROLL_CW | ROLL_CCW | PITCH_UP | PITCH_DOWN | PUSH | POP;
subruleSym: ID | 'f';

LEFT	: '-';
RIGHT	: '+';
ROLL_CW	: '\\\\';
ROLL_CCW: '/';
PITCH_UP: '&';
PITCH_DOWN: '^';
PUSH	: '[';
POP	: ']';
ID	: [A-Z][a-z]*;
INT     : [0-9]+ ;
FLOAT	: [0-9]+.[0-9]+;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
