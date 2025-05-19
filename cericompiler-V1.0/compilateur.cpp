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
#include <vector>
#include <set>
#include <map>
#include <FlexLexer.h>
#include "tokeniser.h"
#include <cstring>


using namespace std;

enum OPREL {EQU, DIFF, INF, SUP, INFE, SUPE, WTFR};
enum OPADD {ADD, SUB, OR, WTFA};
enum OPMUL {MUL, DIV, MOD, AND ,WTFM};
enum TYPE {UNSIGNED_INT, BOOLEAN, DOUBLE, CHAR, ERROR_TYPE};

// Function prototypes
TYPE Expression(void);
TYPE SimpleExpression(void);
OPREL RelationalOperator(void);
TYPE Factor(void);
TYPE Term(void);
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
    
	cout << "\tmovq " << lexer->YYText() << "(%rip), %rax" << endl;
    cout << "\tpushq %rax" << endl;
    
    current = (TOKEN) lexer->yylex();
    return t;
}

TYPE Number(void){
	if (strchr(lexer->YYText(), '.')) { // Si c'est un flottant
        double f = atof(lexer->YYText());
        unsigned long long *i = (unsigned long long*)&f;
        cout << "\tpushq $" << *i << "\t# empile le flottant " << f << endl;
        current = (TOKEN)lexer->yylex();
        return DOUBLE;
    } else if (lexer->YYText()[0] == '\'') { // Si c'est un caractère
        char c = lexer->YYText()[1];
        cout << "\tpushq $" << (int)c << "\t# empile le caractère '" << c << "'" << endl;
        current = (TOKEN)lexer->yylex();
        return CHAR;
    } else { // Si c'est un entier
        cout << "\tpushq $" << atoi(lexer->YYText()) << endl;
        current = (TOKEN)lexer->yylex();
        return UNSIGNED_INT;
    }
}

// Expression := SimpleExpression [RelationalOperator SimpleExpression]
TYPE Expression(void){
	OPREL oprel;
	TYPE t1=SimpleExpression();
	if(current==RELOP){
		oprel=RelationalOperator();
		TYPE t2=SimpleExpression();
		if(t1!=t2)
			Error("Type incompatibles pour expression relationnelle");
		 switch(t1) {
            case DOUBLE:
                cout << "\tfldl 8(%rsp)" << endl;    // Second opérande
                cout << "\tfldl (%rsp)" << endl;     // Premier opérande
                cout << "\taddq $16, %rsp" << endl;  // Nettoie la pile
                cout << "\tfcomip %st(1), %st(0)" << endl;  // Compare et pop
                cout << "\tfstp %st(0)" << endl;     // Pop le dernier nombre
                break;
                
            case CHAR:
                cout << "\tpopq %rax" << endl;
                cout << "\tpopq %rbx" << endl;
                cout << "\tcmpb %al, %bl" << endl;  // Compare les octets
                break;
                
            default:  // UNSIGNED_INT et BOOLEAN
                cout << "\tpopq %rax" << endl;
                cout << "\tpopq %rbx" << endl;
                cout << "\tcmpq %rax, %rbx" << endl;
        }
        switch(oprel) {
			case EQU:
				cout << "\tje Vrai" << ++TagNumber << "\t# If equal" << endl;
				break;
			case DIFF:
				cout << "\tjne Vrai" << ++TagNumber << "\t# If different" << endl;
				break;
			case SUPE:
				cout << "\tjae Vrai" << ++TagNumber << "\t# If above or equal" << endl;
				break;
			case INFE:
				cout << "\tjbe Vrai" << ++TagNumber << "\t# If below or equal" << endl;
				break;
			case INF:
				cout << "\tjb Vrai" << ++TagNumber << "\t# If below" << endl;
				break;
			case SUP:
				cout << "\tja Vrai" << ++TagNumber << "\t# If above" << endl;
				break;
			default:
				Error("Opérateur de comparaison inconnu");
		}
		cout << "\tpushq $0\t\t# False"<<endl;
		cout << "\tjmp Suite"<<TagNumber<<endl;
		cout << "Vrai"<<TagNumber<<":\tpushq $0xFFFFFFFFFFFFFFFF\t\t# True"<<endl;	
		cout << "Suite"<<TagNumber<<":"<<endl;
		return BOOLEAN;
	}
	return t1;
}			// Called by Term() and calls Term()
// Expression := SimpleExpression [RelationalOperator SimpleExpression]
/*TYPE Expression(void){
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
}*/

// Factor := "(" Expression ")" | Number | Letter
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
	if(current == NUMBER) {
        if(strchr(lexer->YYText(), '.')) {  // Flottant
            double f = atof(lexer->YYText());
            unsigned long long *i = (unsigned long long*)&f;
            cout << "\tmovabs $" << *i << ", %rax\t# charge le flottant " << f << " (" << *i << ")" << endl;
            cout << "\tpushq %rax" << endl;
            current = (TOKEN)lexer->yylex();
            return DOUBLE;
        } else {  // Entier
            cout << "\tpushq $" << atoi(lexer->YYText()) << endl;
            current = (TOKEN)lexer->yylex();
            return UNSIGNED_INT;
        }
    } else if(current == CHARCONST) {  // Nouveau type pour les caractères
        char c = lexer->YYText()[1];  // Skip le premier guillemet
        cout << "\tpushq $" << (int)c << "\t# empile le caractère '" << c << "'" << endl;
        current = (TOKEN)lexer->yylex();
        return CHAR;
    } else if(current == ID) {
        return Identifier();
    } else {
        Error("'(' ou chiffre ou lettre ou caractère attendu");
        return ERROR_TYPE;
    }
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
TYPE Term(void) {
    OPMUL mulop;
    TYPE t1 = Factor();
    while(current == MULOP) {
        mulop = MultiplicativeOperator();
        TYPE t2 = Factor();
        
        if(mulop == AND) {
            // Gestion des opérations logiques
            if(t1 != BOOLEAN && t1 != UNSIGNED_INT) {
                Error("Opérateur && requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
            }
            if(t2 != BOOLEAN && t2 != UNSIGNED_INT) {
                Error("Opérateur && requiert des opérandes de type BOOLEAN ou UNSIGNED_INT");
            }
            cout << "\tpopq %rbx" << endl;
            cout << "\tpopq %rax" << endl;
            cout << "\tandq %rbx, %rax" << endl;
            cout << "\tpushq %rax" << endl;
            t1 = BOOLEAN;
        } else {
            // Pour les autres opérations
            if(t1 != t2) {
                Error("Types incompatibles pour une opération multiplicative");
            }

            switch(t1) {
                case DOUBLE:
                    cout << "\tfldl 8(%rsp)" << endl;
                    cout << "\tfldl (%rsp)" << endl;
                    cout << "\taddq $16, %rsp" << endl;
                    
                    if(mulop == MUL) {
                        cout << "\tfmulp" << endl;
                    } else if(mulop == DIV) {
                        cout << "\tfdivp" << endl;
                    } else {
                        Error("Seules les opérations * et / sont supportées pour les flottants");
                    }
                    cout << "\tsubq $8, %rsp" << endl;
                    cout << "\tfstpl (%rsp)" << endl;
                    break;

                case CHAR:
                    cout << "\tpopq %rbx" << endl;
                    cout << "\tpopq %rax" << endl;
                    if(mulop == MUL) {
                        cout << "\tmulb %bl" << endl;
                        cout << "\tpushq %rax" << endl;
                    } else {
                        Error("Seule la multiplication est supportée pour les caractères");
                    }
                    break;

                case UNSIGNED_INT:
                    cout << "\tpopq %rbx" << endl;
                    cout << "\tpopq %rax" << endl;
                    switch(mulop) {
                        case MUL:
                            cout << "\timulq %rbx, %rax" << endl;
                            break;
                        case DIV:
                            cout << "\tcqto" << endl;
                            cout << "\tidivq %rbx" << endl;
                            break;
                        case MOD:
                            cout << "\tcqto" << endl;
                            cout << "\tidivq %rbx" << endl;
                            cout << "\tmovq %rdx, %rax" << endl;
                            break;
                        default:
                            Error("Opérateur multiplicatif inconnu");
                    }
                    cout << "\tpushq %rax" << endl;
                    break;

                default:
                    Error("Type non supporté pour les opérations multiplicatives");
            }
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
			
			switch(t1) {
                case DOUBLE:
                    cout << "\tfldl 8(%rsp)" << endl;
                    cout << "\tfldl (%rsp)" << endl;
                    cout << "\taddq $16, %rsp" << endl;
                    
                    switch(adop) {
                        case ADD:
                            cout << "\tfaddp" << endl;
                            break;
                        case SUB:
                            cout << "\tfsubp" << endl;
                            break;
                        default:
                            Error("Opération non supportée pour les flottants");
                    }
                    cout << "\tsubq $8, %rsp" << endl;
                    cout << "\tfstpl (%rsp)" << endl;
                    break;

                case CHAR:cout << "\tpopq %rbx" << endl;
                    cout << "\tpopq %rax" << endl;
                    cout << "\tmovb %bl, %bl" << endl;
                    cout << "\tmovb %al, %al" << endl;
                    
                    switch(adop) {
                        case ADD:
                            cout << "\taddb %bl, %al" << endl;
                            cout << "\tpushq %rax\t# ADD char" << endl;
                            break;
                        case SUB:
                            cout << "\tsubb %bl, %al" << endl;
                            cout << "\tpushq %rax\t# SUB char" << endl;
                            break;
                        default:
                            Error("Opération non supportée pour les caractères");
                    }
                    break;

                case UNSIGNED_INT:
                    cout << "\tpopq %rbx" << endl;
                    cout << "\tpopq %rax" << endl;
                    switch(adop) {
						case OR:
                            cout << "\taddq %rbx, %rax\t# OR" << endl;
                            break;
                        case ADD:
                            cout << "\taddq %rbx, %rax\t# ADD" << endl;
                            break;
                        case SUB:
                            cout << "\tsubq %rbx, %rax\t# SUB" << endl;
                            break;
                        default:
                            Error("Opérateur additif inconnu");
                    }
                    cout << "\tpushq %rax" << endl;
                    break;

                default:
                    Error("Type non supporté pour les opérations additives");
            }
        }
    }
    return t1;
}

// DeclarationPart := "[" Ident {"," Ident} "]"
void DeclarationPart(void){
	if(current!=RBRACKET)
		Error("caractère '[' attendu");
	cout << "\t.data"<<endl;
	cout << "FormatString1:\t.string \"%llu\\n\"\n";  // affichage d'un entier 64 bits
	cout << "FormatString2:\t.string \"%f\\n\"\n";  // tp7
    cout << "FormatString3:\t.string \"%c\\n\"\n";  // tp7

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
// VarDeclarationPart := "VAR" VarDeclaration {";" VarDeclaration} "."
// VarDeclaration := Ident {"," Ident} ":" Type
void VarDeclarationPart() {
	if(current == KEYWORD && strcmp(lexer->YYText(), "VAR") == 0) {
		cout << "\t.data" << endl;
		cout << "FormatString1:\t.string \"%llu\\n\"\n";
		cout << "FormatString2:\t.string \"%f\\n\"\n";  // tp7
    	cout << "FormatString3:\t.string \"%c\\n\"\n";  // tp7
		cout << "\t.align 8" << endl;

		current = (TOKEN) lexer->yylex();  // on avance après VAR

		while(current == ID) {
			vector<string> identifiants;
			identifiants.push_back(lexer->YYText());

			current = (TOKEN) lexer->yylex();
			while(current == COMMA) {
				current = (TOKEN) lexer->yylex();
				if(current != ID) Error("Identifiant attendu après virgule");
				identifiants.push_back(lexer->YYText());
				current = (TOKEN) lexer->yylex();
			}

			if(current != COLON) Error("':' attendu");
			current = (TOKEN) lexer->yylex();

			TYPE type;
			if(current != KEYWORD) Error("Type attendu");
			if(strcmp(lexer->YYText(), "INTEGER") == 0) {
				type = UNSIGNED_INT;
			} else if(strcmp(lexer->YYText(), "DOUBLE") == 0) {
                type = DOUBLE;
            } else if(strcmp(lexer->YYText(), "CHAR") == 0) {
                type = CHAR;
            } else if(strcmp(lexer->YYText(), "BOOLEAN") == 0) {
                type = BOOLEAN;
            } else {
				Error("Type inconnu");
			}

			for(const string& id : identifiants) {
				if(IsDeclared(id.c_str())) {
					Error("Variable déjà déclarée : " + id);
				}
				DeclaredVariables.insert(id);
				VariableTypes[id] = type;

				switch(type) {
                    case DOUBLE:
                        cout << id << ":\t.double 0.0" << endl;
                        break;
                    case CHAR:
                        cout << id << ":\t.byte 0" << endl;
                        break;
                    default: // UNSIGNED_INT et BOOLEAN
                        cout << id << ":\t.quad 0" << endl;
                }
			}

			current = (TOKEN) lexer->yylex();
			if(current == SEMICOLON) {
				current = (TOKEN) lexer->yylex();
			}
		}

		if(current != DOT) Error("'.' attendu en fin de déclaration");
		current = (TOKEN) lexer->yylex();  // passer le '.'
	}
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



// AssignementStatement := Identifier ":=" Expression
void AssignementStatement(void) {
    string variable;
    if(current != ID)
        Error("Identificateur attendu");

    if(!IsDeclared(lexer->YYText())) {
        Error("Variable non déclarée : " + string(lexer->YYText()));
    }

    variable = lexer->YYText();
    TYPE varType = VariableTypes[variable];

    current = (TOKEN) lexer->yylex();
    if(current != ASSIGN)
        Error("caractères ':=' attendus");

    current = (TOKEN) lexer->yylex();
    TYPE exprType = Expression();

    if(varType != exprType && !(varType == BOOLEAN && exprType == UNSIGNED_INT)) {
        Error("Type incompatible entre la variable et l'expression");
    }

    switch(varType) {
        case DOUBLE:
            cout << "\tmovsd (%rsp), %xmm0" << endl;      // Utilise xmm0 pour les flottants
            cout << "\taddq $8, %rsp" << endl;
            cout << "\tmovsd %xmm0, " << variable << "(%rip)" << endl;
            break;
            
        case CHAR:
            cout << "\tmovq (%rsp), %rax" << endl;
            cout << "\taddq $8, %rsp" << endl;
            cout << "\tmovb %al, " << variable << "(%rip)" << endl;
            break;
            
        default: // UNSIGNED_INT et BOOLEAN
            cout << "\tmovq (%rsp), %rax" << endl;
            cout << "\taddq $8, %rsp" << endl;
            cout << "\tmovq %rax, " << variable << "(%rip)" << endl;
    }
}

/*void AssignementStatement(void){
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
	// AJOUT TP6 : accepte BOOLEAN := UNSIGNED_INT (comme a := 1)
	if(varType != exprType){
		if (!(varType == BOOLEAN && exprType == UNSIGNED_INT)) {
        	Error("Type incompatible entre la variable et l'expression");
    	}
	}
	//Expression();
	switch(varType) {
        case DOUBLE:
            cout << "\tfldl (%rsp)" << endl;
            cout << "\taddq $8, %rsp" << endl;
            cout << "\tfstpl " << variable << "(%rip)" << endl;
            break;
            
        case CHAR:
            cout << "\tpopq %rax" << endl;
            cout << "\tmovb %al, " << variable << "(%rip)" << endl;
            break;
            
        default: // UNSIGNED_INT et BOOLEAN
            cout << "\tpopq %rax" << endl;
            cout << "\tmovq %rax, " << variable << "(%rip)" << endl;
    }
}*/
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
		//cout << "Keyword detected: " << lexer->YYText() << endl;
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
		else if(strcmp(lexer->YYText(), "DISPLAY") == 0){
			current = (TOKEN) lexer->yylex();
			TYPE exprType = Expression();
			switch(exprType) {
        case DOUBLE:
            cout << "\tfldl (%rsp)" << endl;      // Charge le flottant dans %st(0)
            cout << "\taddq $8, %rsp" << endl;    // Nettoie la pile
            cout << "\tsubq $8, %rsp" << endl;    // Réserve de l'espace
            cout << "\tfstpl (%rsp)" << endl;     // Stocke le flottant
            cout << "\tmovq $FormatString2, %rdi" << endl;
            cout << "\tmovl $1, %eax" << endl;    // 1 argument flottant
            cout << "\tcall printf@PLT" << endl;
            cout << "\taddq $8, %rsp" << endl;    // Nettoie la pile
            break;
            
        case CHAR:
            cout << "\tpopq %rsi" << endl;         // Récupère le caractère
            cout << "\tmovq $FormatString3, %rdi" << endl;
            cout << "\tmovl $0, %eax" << endl;    // Pas d'argument flottant
            cout << "\tcall printf@PLT" << endl;
            break;
            
        default: // UNSIGNED_INT et BOOLEAN
            cout << "\tpopq %rsi" << endl;
            cout << "\tmovq $FormatString1, %rdi" << endl;
            cout << "\tmovl $0, %eax" << endl;
            cout << "\tcall printf@PLT" << endl;
    }
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

	cout << "\tmovq (%rsp), %rax" << endl;
    cout << "\taddq $8, %rsp" << endl;
    cout << "\tmovq %rax, " << variable << "(%rip)" << endl;

	if(strcmp(lexer->YYText(), "TO")==0){
		current =(TOKEN) lexer->yylex();
		cout << "For" << tag << ":\n";
		TYPE expr2 = Expression();
		if(expr2 != UNSIGNED_INT){
			Error("Type entier attendu pour la limite du FOR");
		}
		cout << "\tpopq %rbx" << endl;
		cout << "\tcmpq %rbx, " << variable << endl;
		cout << "\tjg FinFor" << tag << endl;
	}
	else{
		Error("'TO' attendu");
	}

	if(strcmp(lexer->YYText(), "DO")==0){
		current = (TOKEN) lexer->yylex();
		//string before = lexer->YYText();

		Statement();
		cout << "\tmovq " << variable << "(%rip), %rax" << endl;
        cout << "\taddq $1, %rax" << endl;
        cout << "\tmovq %rax, " << variable << "(%rip)" << endl;
        
		cout << "\tjmp For" << tag << endl;
		cout << "FinFor" << tag << ":\n";

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

	cout << "While" << tag << ":\n";
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
	cout << "\tpopq %rax" << endl;
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
	cout << "\tpopq %rax" << endl;
	cout << "\tcmpq $0, %rax" << endl;
	cout << "\tje ELSE" << tag << endl;

	Statement();
	current = (TOKEN) lexer->yylex();

	//if(strcmp(lexer->YYText(), "THEN")!=0){ Error("'THEN' attendu après un IF");}
	cout << "\tjmp FinIf" << tag << endl;
	cout << "ELSE" << tag << ":\n";
	
	if(current == KEYWORD && strcmp(lexer->YYText(), "ELSE")==0){
		current =(TOKEN) lexer->yylex();
		Statement();
	}
	cout << "FinIf" << tag << ":\n";

}

//BlockStatement := "BEGIN" Statement { ";" Statement } "END"
void BlockStatement(void){
	//unsigned long tag = TagNumber++;

	cout << "\t# Debut du Block" << endl;
	current = (TOKEN) lexer->yylex();
	Statement();

	while(current == SEMICOLON){
 		current = (TOKEN)lexer->yylex();
 		Statement();
 	}

	if(current == KEYWORD && strcmp(lexer->YYText(), "END") == 0){
		cout << "\t# Fin de Block" << endl;
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
	if(current==KEYWORD && strcmp(lexer->YYText(), "VAR") == 0)
		VarDeclarationPart();
	else if(current==RBRACKET)
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