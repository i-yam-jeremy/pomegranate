grammar Lsystem;		
lsystem: 
	'generations' '=' generations=INT ','
	'angle' '=' angle=numWithDev ','
	('ringvertexcount' '=' ringvertexcount=INT ',')?
	('ringsperworlddist' '=' ringsperworlddist=num ',')?
	('minringspersegment' '=' minringspersegment=INT ',')?
	'init' '=' initiator=commands ','
	('leafable' '=' leafablerule=commands ',')?
	'rules' ':' lrule (',' lrule)*;
lrule: name=ID ('[' isleaf='leaf' ']')? ('[' isleafable='leafable' ']')? '=' body=commands;
commands: (sym | subruleSym | scaleLength)*;
sym: ( LEFT | RIGHT | ROLL_CW | ROLL_CCW | PITCH_UP | PITCH_DOWN | PUSH | POP | SCALE_ALL | SCALE_RADIUS ) ( '(' arg1=numWithDev ')' )?;
subruleSym: ID | 'f';
scaleLength: '"' '(' value=numWithDev ')';
numWithDev: value=num ('dev' dev=num)?;
num: FLOAT|INT;

LEFT	: '-';
RIGHT	: '+';
ROLL_CW	: '\\\\';
ROLL_CCW: '/';
PITCH_UP: '&';
PITCH_DOWN: '^';
SCALE_ALL: '@';
SCALE_RADIUS: '`';
PUSH	: '[';
POP	: ']';
ID	: [A-Z][a-z]*;
INT     : [0-9]+ ;
FLOAT	: [0-9]+.[0-9]+;
WS : (' ' | '\t' | '\r' | '\n')+ -> channel(HIDDEN);
