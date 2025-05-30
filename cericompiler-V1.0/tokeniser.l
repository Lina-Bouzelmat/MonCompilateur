%{
// This is our Lexical tokeniser 
// It should be compiled into cpp with :
// flex++ -d -otokeniser.cpp tokeniser.l 
// And then compiled into object with
// g++ -c tokeniser.cpp
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

#include "tokeniser.h"
#include <iostream>

using namespace std;

%}

%option noyywrap
%option c++
%option yylineno

stringconst  \"[^\n"]+\"
ws      [ \t\n\r]+
comment "//".*\n
alpha   [A-Za-z]
digit   [0-9]
floatnumber  {digit}+"."{digit}+
number  {digit}+
chartoken    \'[^\']\'
id	{alpha}({alpha}|{digit})*
addop	(\+|\-|\|\|)
mulop	(\*|\/|%|\&\&)
relop	(\<|\>|"=="|\<=|\>=|!=)
unknown [^\"A-Za-z0-9 \n\r\t\(\)\<\>\=\!\%\&\|\}\-\;\.]+
keyword "BEGIN"|"END"|"IF"|"THEN"|"ELSE"|"WHILE"|"DO"|"FOR"|"TO"|"DISPLAY"|"VAR"|"BOOLEAN"|"INTEGER"|"DOUBLE"|"CHAR"|"CASE"|"OF"|"CONST"|"TRUE"|"FALSE"|"MOD"
%%

{comment}   {/* ignore les commentaires */};
"NOT"       return NOT;
{keyword}	return KEYWORD;
{addop}		return ADDOP;
{mulop}		return MULOP;
{relop}		return RELOP;
{floatnumber}	return NUMBER;
{chartoken}	return CHARCONST;
{number}	return NUMBER;
{id}		return ID;
{stringconst}	return STRINGCONST;
"["		return RBRACKET;
"]"		return LBRACKET;
","		return COMMA;
";"		return SEMICOLON;
"."		return DOT;
":"     return COLON;
"="     return EQUAL;
":="	return ASSIGN;
"("		return RPARENT;
")"		return LPARENT;
"!"		return NOT;
<<EOF>>		return FEOF;
{ws}    {/* skip blanks and tabs */};
"(*"    { /* Skip comments between '(*' and '*)' */
		int c;
		while((c = yyinput()) != 0){
     			if(c == '*'){
     	    			if((c = yyinput()) == ')')
    	        			break;
    	     			else
  	          			unput(c);
  	   		}	
		}
	};

{unknown}	return UNKNOWN;

%%

