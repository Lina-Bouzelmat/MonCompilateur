//  A compiler from a very simple Pascal-like structured language LL(k)
//  to 64-bit 80x86 Assembly langage
//  Copyright (C) 2019 Pierre Jourlin
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

// Build with "make compilateur"


#include <string>
#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <FlexLexer.h>
#include "tokeniser.h"
#include <cstring>


using namespace std;

enum OPREL {EQU, DIFF, INF, SUP, INFE, SUPE, WTFR};
enum OPADD {ADD, SUB, OR, WTFA};
enum OPMUL {MUL, DIV, MOD, AND ,WTFM};
enum TYPE {UNSIGNED_INT, BOOLEAN, ERROR_TYPE};
TOKEN current;				// Current token


FlexLexer* lexer = new yyFlexLexer; // This is the flex tokeniser
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

	
set<string> DeclaredVariables;
map<string, TYPE> VariableTypes;

unsigned long TagNumber=0;

bool IsDeclared(const char *id){
	return VariableTypes.find(id)!=VariableTypes.end();
}

TYPE GetVariableType(const char *id) {
    if (!IsDeclared(id))
        return ERROR_TYPE;
    return VariableTypes[id];
}

void Error(string s){
	cerr << "Ligne n°"<<lexer->lineno()<<", lu : '"<<lexer->YYText()<<"'("<<current<<"), mais ";
	cerr<< s << endl;
	exit(-1);
}

void TypeError(string s){
    cerr << "Erreur de type: " << s << endl;
    exit(-1);
}
// Program := [DeclarationPart] StatementPart
// DeclarationPart := "[" Letter {"," Letter} "]"
// StatementPart := Statement {";" Statement} "."
// Statement := AssignementStatement
// AssignementStatement := Letter "=" Expression

// Expression := SimpleExpression [RelationalOperator SimpleExpression]
// SimpleExpression := Term {AdditiveOperator Term}
// Term := Factor {MultiplicativeOperator Factor}
// Factor := Number | Letter | "(" Expression ")"| "!" Factor
// Number := Digit{Digit}

// AdditiveOperator := "+" | "-" | "||"
// MultiplicativeOperator := "*" | "/" | "%" | "&&"
// RelationalOperator := "==" | "!=" | "<" | ">" | "<=" | ">="  
// Digit := "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"
// Letter := "a"|...|"z"
	
		
TYPE Identifier(void){
	TYPE t = GetVariableType(lexer->YYText());
    if (t == ERROR_TYPE)
        Error("Variable non déclarée: " + string(lexer->YYText()));
    
    cout << "\tpush " << lexer->YYText() << endl;
    current = (TOKEN) lexer->yylex();
    return t;
}

TYPE Number(void){
	cout << "\tpush $" << atoi(lexer->YYText()) << endl;
	current = (TOKEN) lexer->yylex();
	return UNSIGNED_INT;
}

TYPE Expression(void);			// Called by Term() and calls Term()

TYPE Factor(void){
	TYPE t;
	if(current==RPARENT){
		current=(TOKEN) lexer->yylex();
		t=Expression();
		if(current!=LPARENT)
			Error("')' était attendu");		// ")" expected
		else{
			current=(TOKEN) lexer->yylex();
			return t;
		}
	}
	if(current==NUMBER){
			return Number(); 
		}
	     	else if(current==ID){
			return Identifier(); 
		}
		else{
			Error("'(' ou chiffre ou lettre attendue");
			return ERROR_TYPE;
		}
	return t;
}

// MultiplicativeOperator := "*" | "/" | "%" | "&&"
OPMUL MultiplicativeOperator(void){
	OPMUL opmul;
	if(strcmp(lexer->YYText(),"*")==0)
		opmul=MUL;
	else if(strcmp(lexer->YYText(),"/")==0)
		opmul=DIV;
	else if(strcmp(lexer->YYText(),"%")==0)
		opmul=MOD;
	else if(strcmp(lexer->YYText(),"&&")==0)
		opmul=AND;
	else opmul=WTFM;
	current=(TOKEN) lexer->yylex();
	return opmul;
}

// Term := Factor {MultiplicativeOperator Factor}
TYPE Term(void){
	OPMUL mulop;
	TYPE t1=Factor();
	while(current==MULOP){
		mulop=MultiplicativeOperator();		// Save operator in local variable
		TYPE t2=Factor();
		if(mulop == AND) {
			// Convertir UNSIGNED_INT en BOOLEAN implicitement pour les opérations logiques
			if(t1 != BOOLEAN && t1 != UNSIGNED_INT) {
				Error("Opérateur && requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
			}
			if(t2 != BOOLEAN && t2 != UNSIGNED_INT) {
				Error("Opérateur && requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
			}
			t1 = BOOLEAN; // Le résultat est toujours BOOLEAN
		} else {
			// Pour les autres opérations, on garde la vérification de type stricte
			if(t1 != t2) {
				Error("Type non compatible pour une op multiplicative");
			}
			if(t1 != UNSIGNED_INT) {
				Error("Opérateurs *, / et % requièrent des opérandes de type UNSIGNED_INT");
			}
		}
		cout << "\tpop %rbx"<<endl;	// get first operand
		cout << "\tpop %rax"<<endl;	// get second operand
		switch(mulop){
			case AND:
				cout << "\tmulq	%rbx"<<endl;	// a * b -> %rdx:%rax
				cout << "\tpush %rax\t# AND"<<endl;	// store result
				break;
			case MUL:
				cout << "\tmulq	%rbx"<<endl;	// a * b -> %rdx:%rax
				cout << "\tpush %rax\t# MUL"<<endl;	// store result
				break;
			case DIV:
				cout << "\tmovq $0, %rdx"<<endl; 	// Higher part of numerator  
				cout << "\tdiv %rbx"<<endl;			// quotient goes to %rax
				cout << "\tpush %rax\t# DIV"<<endl;		// store result
				break;
			case MOD:
				cout << "\tmovq $0, %rdx"<<endl; 	// Higher part of numerator  
				cout << "\tdiv %rbx"<<endl;			// remainder goes to %rdx
				cout << "\tpush %rdx\t# MOD"<<endl;		// store result
				break;
			default:
				Error("opérateur multiplicatif attendu");
		}
	}
	return t1;
}

// AdditiveOperator := "+" | "-" | "||"
OPADD AdditiveOperator(void){
	OPADD opadd;
	if(strcmp(lexer->YYText(),"+")==0)
		opadd=ADD;
	else if(strcmp(lexer->YYText(),"-")==0)
		opadd=SUB;
	else if(strcmp(lexer->YYText(),"||")==0)
		opadd=OR;
	else opadd=WTFA;
	current=(TOKEN) lexer->yylex();
	return opadd;
}

// SimpleExpression := Term {AdditiveOperator Term}
TYPE SimpleExpression(void){
	OPADD adop;
	TYPE t1 = Term();
	while(current==ADDOP){
		adop=AdditiveOperator();		// Save operator in local variable
		TYPE t2 = Term();
		if(adop == OR) {
			// Convertir UNSIGNED_INT en BOOLEAN implicitement pour les opérations logiques
			if(t1 != BOOLEAN && t1 != UNSIGNED_INT) {
				Error("Opérateur || requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
			}
			if(t2 != BOOLEAN && t2 != UNSIGNED_INT) {
				Error("Opérateur || requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
			}
			t1 = BOOLEAN; // Le résultat est toujours BOOLEAN
		} else {
			// Pour les autres opérations, on garde la vérification de type stricte
			if(t1 != t2) {
				Error("TYPE incompatible pour une op additive");
			}
			if(t1 != UNSIGNED_INT) {
				Error("Opérateurs + et - requièrent des opérandes de type UNSIGNED_INT");
			}
		}
		cout << "\tpop %rbx"<<endl;	// get first operand
		cout << "\tpop %rax"<<endl;	// get second operand
		switch(adop){
			case OR:
				cout << "\taddq	%rbx, %rax\t# OR"<<endl;// operand1 OR operand2
				break;			
			case ADD:
				cout << "\taddq	%rbx, %rax\t# ADD"<<endl;	// add both operands
				break;			
			case SUB:
				cout << "\tsubq	%rbx, %rax\t# SUB"<<endl;	// substract both operands
				break;
			default:
				Error("opérateur additif inconnu");
		}
		cout << "\tpush %rax"<<endl;			// store result
	}
	return t1;

}

// DeclarationPart := "[" Ident {"," Ident} "]"
void DeclarationPart(void){
	if(current!=RBRACKET)
		Error("caractère '[' attendu");
	cout << "\t.data"<<endl;
	cout << "\t.align 8"<<endl;
	
	current=(TOKEN) lexer->yylex();
	if(current!=ID)
		Error("Un identificater était attendu");
	cout << lexer->YYText() << ":\t.quad 0"<<endl;
	DeclaredVariables.insert(lexer->YYText());
	VariableTypes[lexer->YYText()] = UNSIGNED_INT;

	current=(TOKEN) lexer->yylex();
	while(current==COMMA){
		current=(TOKEN) lexer->yylex();
		if(current!=ID)
			Error("Un identificateur était attendu");
		cout << lexer->YYText() << ":\t.quad 0"<<endl;
		DeclaredVariables.insert(lexer->YYText());
		VariableTypes[lexer->YYText()] = UNSIGNED_INT;
		current=(TOKEN) lexer->yylex();
	}
	if(current!=LBRACKET)
		Error("caractère ']' attendu");
	current=(TOKEN) lexer->yylex();
	//return UNSIGNED_INT;

}

// RelationalOperator := "==" | "!=" | "<" | ">" | "<=" | ">="  
OPREL RelationalOperator(void){
	OPREL oprel;
	if(strcmp(lexer->YYText(),"==")==0)
		oprel=EQU;
	else if(strcmp(lexer->YYText(),"!=")==0)
		oprel=DIFF;
	else if(strcmp(lexer->YYText(),"<")==0)
		oprel=INF;
	else if(strcmp(lexer->YYText(),">")==0)
		oprel=SUP;
	else if(strcmp(lexer->YYText(),"<=")==0)
		oprel=INFE;
	else if(strcmp(lexer->YYText(),">=")==0)
		oprel=SUPE;
	else oprel=WTFR;
	current=(TOKEN) lexer->yylex();
	return oprel;
}

// Expression := SimpleExpression [RelationalOperator SimpleExpression]
TYPE Expression(void){
	OPREL oprel;
	TYPE t1 = SimpleExpression();
	if(current==RELOP){
		oprel=RelationalOperator();
		TYPE t2 = SimpleExpression();
		if(t1 != t2){
			Error("Type incompatibles pour expression relationnelle");
		}
		cout << "\tpop %rax"<<endl;
		cout << "\tpop %rbx"<<endl;
		cout << "\tcmpq %rax, %rbx"<<endl;
		switch(oprel){
			case EQU:
				cout << "\tje Vrai"<<++TagNumber<<"\t# If equal"<<endl;
				break;
			case DIFF:
				cout << "\tjne Vrai"<<++TagNumber<<"\t# If different"<<endl;
				break;
			case SUPE:
				cout << "\tjae Vrai"<<++TagNumber<<"\t# If above or equal"<<endl;
				break;
			case INFE:
				cout << "\tjbe Vrai"<<++TagNumber<<"\t# If below or equal"<<endl;
				break;
			case INF:
				cout << "\tjb Vrai"<<++TagNumber<<"\t# If below"<<endl;
				break;
			case SUP:
				cout << "\tja Vrai"<<++TagNumber<<"\t# If above"<<endl;
				break;
			default:
				Error("Opérateur de comparaison inconnu");
		}
		cout << "\tpush $0\t\t# False"<<endl;
		cout << "\tjmp Suite"<<TagNumber<<endl;
		cout << "Vrai"<<TagNumber<<":\tpush $0xFFFFFFFFFFFFFFFF\t\t# True"<<endl;	
		cout << "Suite"<<TagNumber<<":"<<endl;
		return BOOLEAN;
	}
	return t1;
}

// AssignementStatement := Identifier ":=" Expression
void AssignementStatement(void){
	string variable;
	if(current!=ID)
		Error("Identificateur attendu");
	if(!IsDeclared(lexer->YYText())){
		cerr << "Erreur : Variable '"<<lexer->YYText()<<"' non déclarée"<<endl;
		exit(-1);
	}
	variable=lexer->YYText();
	//TYPE varType = UNSIGNED_INT;
	TYPE varType = VariableTypes[variable];

	current=(TOKEN) lexer->yylex();
	if(current!=ASSIGN)
		Error("caractères ':=' attendus");
	current=(TOKEN) lexer->yylex();
	TYPE exprType = Expression();

	// Vérification la compatibilité des types
	if(varType != exprType){
		Error("Type incompatible entre la variable et l'expression");
	}

	//Expression();
	cout << "\tpop "<<variable<<endl;
}
void ForStatement();
void WhileStatement();
void BlockStatement();
void IfStatement();

	// Statement := AssignementStatement
	void Statement(void){
		if(current==ID){
			AssignementStatement();
		}
		else if(current == KEYWORD){
			cout << "Keyword detected: " << lexer->YYText() << endl;
			if(strcmp(lexer->YYText(),"FOR")==0){
				ForStatement();
			}
			else if(strcmp(lexer->YYText(),"WHILE")==0){
				WhileStatement();
			}
			else if(strcmp(lexer->YYText(),"IF")==0){
				IfStatement();
			}
			else if(strcmp(lexer->YYText(),"BEGIN")==0){
				BlockStatement();
			}
			else {
            Error("Mot-clé non reconnu");
        }
		}
		else {
        Error("Instruction attendue: identifiant ou mot-clé");
		}
	}

// ForStatement := Identifier ":=" <Expression>, "TO" <Expression>, "DO" <instruction> ["STEP"<const>] 
void ForStatement(void){
	unsigned long tag = TagNumber++;
	current =(TOKEN) lexer->yylex();
	string variable;

	if(current != ID){
		Error("Identifiant attendu");
	} 

	if(IsDeclared(lexer->YYText())){
		variable = lexer->YYText();
	}
	else {
        Error("Variable non déclarée");
    }

	//variable= lexer->YYText();
	current = (TOKEN)lexer->yylex();

	if(current != ASSIGN){Error("Operateur ':=' attendu");}
	
	current =(TOKEN) lexer->yylex();
	TYPE expr1 = Expression();
	if(expr1 != UNSIGNED_INT){
		Error("Type entier attendu pour l'initialisation du FOR");
	}
	//Expression();

	cout << "\tpop %rax" << endl;
    cout << "\tmovq %rax, " << variable << endl;

	if(strcmp(lexer->YYText(), "TO")==0){
		current =(TOKEN) lexer->yylex();
		cout << "For" << tag << ":\t# debut de la boucle for" << endl;
		TYPE expr2 = Expression();
		if(expr2 != UNSIGNED_INT){
			Error("Type entier attendu pour la limite du FOR");
		}
		cout << "\tpop %rbx" << endl;
		cout << "\tcmpq %rbx, " << variable << endl;
		cout << "\tjg FinFor" << tag << endl;
	}
	else{
		Error("'TO' attendu");
	}

	if(strcmp(lexer->YYText(), "DO")==0){
		current = (TOKEN) lexer->yylex();
		string before = lexer->YYText();

		Statement();
		if (!(before == variable)) {
			cout << "\tpush " << variable << endl;
			cout << "\tpush $1" << endl;
			cout << "\tpop %rbx" << endl;
			cout << "\tpop %rax" << endl;
			cout << "\taddq %rbx, %rax" << endl;
			cout << "\tpush %rax" << endl;
			cout << "\tpop " << variable << endl;
		}
		cout << "\tjmp For" << tag << endl;
		cout << "FinFor" << tag << ":\t# Fin de la boucle" << endl;

	}
	else {
        Error("DO attendu après FOR TO "); 
	}
}

//WhileStatement := "WHILE" Expression "DO" Statement

void WhileStatement(void){
	unsigned long tag = TagNumber++;
	//string variable;
	current = (TOKEN) lexer->yylex();

	cout << "While " << tag << ":\t#Debut de la boucle While " << endl;
	//cout << "WHILE" << tag << ":" << endl;
	/*if(IsDeclared(lexer->YYText())){
		variable = lexer->YYText();
	}*/

	/*if(Expression() != BOOLEAN){
		Error("Dans votre while ce n'est pas un booléen");
	}*/
	TYPE condType = Expression();
	if(condType != BOOLEAN){
		Error("La condition du WHILE doit être de type BOOLEAN");
	}
	//Expression();
	cout << "\tpop %rax" << endl;
	cout << "\tcmpq $0, %rax" << /*variable <<*/ endl;
	cout << "\tje FinWhile" << tag << "\t# Sorti avec condition fausse" << endl;
	//cout << "\tjge FinWhile" << tag << "\t# Sorti avec condition fausse" << endl; // saut si c'est diff de 0 mais faut rentrer dans la boucle icii donc on enlve le g 
	if(current == KEYWORD || strcmp(lexer->YYText(), "DO")==0){
		current =(TOKEN) lexer->yylex();
		Statement();

		cout << "\tjmp While" << tag << endl;
		cout << "FinWhile" << tag << ":\t# Fin de la boucle While" << endl;
	}
	else{
		Error("'Do' attendu après un While");
	}
}

//IfStatement := "IF" Expression "THEN" Statement [ "ELSE" Statement ]
void IfStatement(void){
	unsigned long tag = TagNumber++;

	current = (TOKEN) lexer->yylex();
	TYPE condType = Expression();
/*
	cout << "\tpop %rax" << endl;
	cout << "\tcmpq $0, %rax" << endl;
	cout << "\tje ELSE" << tag <<"\t# Sauter à ELSE si la condition est fausse" << endl;*/
	if(condType != BOOLEAN && condType != UNSIGNED_INT){
		Error("La condition du IF doit être de type BOOLEAN ou UNSIGNED_INT");
	}
	//current = (TOKEN) lexer->yylex();  // Passer "IF" -> "THEN"
	if(current != KEYWORD || strcmp(lexer->YYText(), "THEN") != 0) {
        Error("'THEN' attendu");
    }
	
	current = (TOKEN) lexer->yylex();
	cout << "\tpop %rax" << endl;
	cout << "\tcmpq $0, %rax" << endl;
	cout << "\tje ELSE" << tag << endl;

	Statement();
	current = (TOKEN) lexer->yylex();

	//if(strcmp(lexer->YYText(), "THEN")!=0){ Error("'THEN' attendu après un IF");}
	cout << "\tjmp FinIf" << tag << endl;
	cout << "ELSE" << tag << ":" << endl;
	
	if(current == KEYWORD && strcmp(lexer->YYText(), "ELSE")==0){
		current =(TOKEN) lexer->yylex();
		Statement();
	}
	cout << "FinIf " << tag << ":" << endl;
}

//BlockStatement := "BEGIN" Statement { ";" Statement } "END"
void BlockStatement(void){
	//unsigned long tag = TagNumber++;

	cout << "#Debut du Block " << endl;
	current = (TOKEN) lexer->yylex();
	Statement();

	while(current == SEMICOLON){
 		current = (TOKEN)lexer->yylex();
 		Statement();
 	}

	if(current == KEYWORD && strcmp(lexer->YYText(), "END") == 0){
		cout << "# Fin de Block" << endl;
		current = (TOKEN) lexer->yylex();
	}
	else{
		Error("END attendu");
	}
	
}
// StatementPart := Statement {";" Statement} "."
void StatementPart(void){
	cout << "\t.text\t\t# The following lines contain the program"<<endl;
	cout << "\t.globl main\t# The main function must be visible from outside"<<endl;
	cout << "main:\t\t\t# The main function body :"<<endl;
	cout << "\tmovq %rsp, %rbp\t# Save the position of the stack's top"<<endl;
	Statement();
	while(current==SEMICOLON){
		current=(TOKEN) lexer->yylex();
		Statement();
	}
	if(current!=DOT)
		Error("caractère '.' attendu");
	current=(TOKEN) lexer->yylex();
}

// Program := [DeclarationPart] StatementPart
void Program(void){
	if(current==RBRACKET)
		DeclarationPart();
	StatementPart();	
}

int main(void){	// First version : Source code on standard input and assembly code on standard output
	// Header for gcc assembler / linker
	cout << "\t\t\t# This code was produced by the CERI Compiler"<<endl;
	// Let's proceed to the analysis and code production
	current=(TOKEN) lexer->yylex();
	Program();
	// Trailer for the gcc assembler / linker
	cout << "\tmovq %rbp, %rsp\t\t# Restore the position of the stack's top"<<endl;
	cout << "\tret\t\t\t# Return from main function"<<endl;
	if(current!=FEOF){
		cerr <<"Caractères en trop à la fin du programme : ["<<current<<"]";
		Error("."); // unexpected characters at the end of program
	}
}