#include <fstream>
#include <iostream>
#include <map>
#include <exception>
#include "compiler_exceptions.h"

#ifndef COMPILER_TYPES
#define COMPILER_TYPES

enum TokenType{
    PROGRAM_T,
    IS_T,
    SEMICOLON_T,
    BEGIN_T,
    END_T,
    GLOBAL_T,
    PROCEDURE_T,
    COLON_T,
    OPEN_PARENTHESIS_T,
    CLOSE_PARENTHESIS_T,
    COMMA_T,
    VARIABLE_T,
    OPEN_BRACKET_T,
    CLOSE_BRACKET_T,
    INTEGER_T,
    FLOAT_T,
    STRING_T,
    BOOL_T,
    ASSIGNMENT_OP_T,
    IF_T,
    THEN_T,
    ELSE_T,
    FOR_T,
    RETURN_T,
    AND_OP_T,
    OR_OP_T,
    NOT_OP_T,
    PLUS_OP_T,
    MINUS_OP_T,
    LESSTHAN_OP_T,
    GREATER_EQUAL_OP_T,
    LESS_EQUAL_OP_T,
    GREATERTHAN_OP_T,
    EQUALITY_OP_T,
    INEQUALITY_OP_T,
    MULTIPLY_OP_T,
    DIVIDE_OP_T,
    TRUE_T,
    FALSE_T,
    ALPHA_T,
    NUM_T,
    QUOTE_T,
    PROGRAM_NT,
    PROGRAM_HEADER_NT,
    PROGRAM_BODY_NT,
    IDENTIFIER_NT,
    DECLARATION_NT,
    STATEMENT_NT,
    PROCEDURE_DECLARATION_NT,
    VARIABLE_DECLARATION_NT,
    PROCEDURE_HEADER_NT,
    PROCEDURE_BODY_NT,
    TYPE_MARK_NT,
    PARAMETER_LIST_NT,
    PARAMETER_NT,
    BOUND_NT,
    NUMBER_NT,
    ASSIGNMENT_STATEMENT_NT,
    IF_STATEMENT_NT,
    LOOP_STATEMENT_NT,
    RETURN_STATEMENT_NT,
    PROCEDURE_CALL_NT,
    ARGUMENT_LIST_NT,
    DESTINATION_NT,
    EXPRESSION_NT,
    ARITH_OP_NT,
    RELATION_NT,
    TERM_NT,
    FACTOR_NT,
    NAME_NT,
    STRING_NT,
    END_OF_FILE,
    NONE
};

class Token{
    public:
        enum TokenType type;
        std::string tokenString;
        Token(TokenType typeInput){
            type = typeInput;
        };
        Token(TokenType typeInput, std::string tokenStringInput){
            type = typeInput;
            tokenString = tokenStringInput;
        }
};

class InFile{
    private: 
        std::ifstream file;
        int lineCount;
    public:
        InFile(std::string path) : file(path){
            lineCount = 0;
        }

        char get_next_char(){
            char next;
            file.get(next);
            if(next == '\n'){
                lineCount++;
            }
            if(file.eof()){
                throw EndOfFileException();
            }
            else{
                return next;
            }
        }
};

class ErrorReporting{
    public:
        ErrorReporting(){
            errorStatus = false;
        }
        bool errorStatus;
        void reportError(std::string* message){

        };
        void reportWarning(std::string* message){
            
        };
};

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

class CommentStatus{
    public: 
        CommentStatus(){
            commentCount = 0;
            beginningComment = false;
            endingComment = false;
            multiLineComment = false;
        }
        bool in_comment(){
            if(commentCount > 0){
                return true;
            }
            else{
                return false;
            }
        }
        void update_comment_status(char c){
            if(c == '/'){
                if(beginningComment){
                    if(multiLineComment == false){
                        commentCount += 1;
                    }
                }
                else if(endingComment){
                    commentCount -= 1;
                }
                else{
                    beginningComment = true;
                }
            }
            else if(c == '*'){
                if(beginningComment){
                    commentCount += 1;
                    multiLineComment = true;
                }
                else{
                    endingComment = true;
                }
            }
            else if(c == '\n'){
                beginningComment = false;
                endingComment = false;
                end_line();
            }
            else{
                beginningComment = false;
                endingComment = false;
            }

            if(commentCount == 0){
                multiLineComment = false;
            }
        }
        void end_line(){
            if(multiLineComment == false){
                commentCount = 0;
            }
        }
    private:
        int commentCount;
        bool beginningComment;
        bool endingComment;
        bool multiLineComment;
};

#endif



