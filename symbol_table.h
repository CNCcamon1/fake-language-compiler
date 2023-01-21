#include <string>
#include <map>
#include "token.h"

#ifndef SYMBOL_TABLE_TYPE
#define SYMBOL_TABLE_TYPE

class SymbolTable{
    public:
        SymbolTable(){
            initialize_reserved_symbols();
        }
        void mapSet(std::string* string){
            map[to_lower_case(string)] = new Token(IDENTIFIER_NT, *string);
        }
        Token* mapGet(std::string* key){
            if(map[to_lower_case(key)]){
                return map[to_lower_case(key)];
            }
            else{
                return nullptr;
            }
        }
    private:
        std::map<std::string, Token*> map;
        std::string to_lower_case(std::string* input){
            std::string* output = new std::string("");
            for(char& c : *input){
                *output += std::tolower(c);
            }
            return *output;
        }
        void initialize_reserved_symbols(){
            map["program"] = new Token(PROGRAM_T);
            map["is"] = new Token(IS_T);
            map["begin"] = new Token(BEGIN_T);
            map["end"] = new Token(END_T);
            map["global"] = new Token(GLOBAL_T);
            map["procedure"] = new Token(PROCEDURE_T);
            map["("] = new Token(OPEN_PARENTHESIS_T);
            map[")"] = new Token(CLOSE_PARENTHESIS_T);
            map[","] = new Token(COMMA_T);
            map[");"] = new Token(SEMICOLON_T);
            map["variable"] = new Token(VARIABLE_T);
            map[":"] = new Token(COLON_T);
            map["["] = new Token(OPEN_BRACKET_T);
            map["]"] = new Token(CLOSE_BRACKET_T);
            map["integer"] = new Token(INTEGER_T);
            map["float"] = new Token(FLOAT_T);
            map["string"] = new Token(STRING_T);
            map["bool"] = new Token(BOOL_T);
            map[":="] = new Token(ASSIGNMENT_OP_T);
            map["if"] = new Token(IF_T);
            map["then"] = new Token(THEN_T);
            map["else"] = new Token(ELSE_T);
            map["for"] = new Token(FOR_T);
            map["return"] = new Token(RETURN_T);
            map["&"] = new Token(AND_OP_T);
            map["|"] = new Token(OR_OP_T);
            map["not"] = new Token(NOT_OP_T);
            map["+"] = new Token(PLUS_OP_T);
            map["-"] = new Token(MINUS_OP_T);
            map["<"] = new Token(LESSTHAN_OP_T);
            map[">="] = new Token(GREATER_EQUAL_OP_T);
            map["<="] = new Token(LESS_EQUAL_OP_T);
            map[">"] = new Token(GREATERTHAN_OP_T);
            map["=="] = new Token(EQUALITY_OP_T);
            map["!="] = new Token(INEQUALITY_OP_T);
            map["*"] = new Token(MULTIPLY_OP_T);
            map["/"] = new Token(DIVIDE_OP_T);
            map["true"] = new Token(TRUE_T);
            map["false"] = new Token(FALSE_T);
            map["\""] = new Token(QUOTE_T);
        }
};


#endif