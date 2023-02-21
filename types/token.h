#include <string>

#ifndef TOKEN_TYPE
#define TOKEN_TYPE

enum TokenType{
    PROGRAM_T,
    IDENTIFIER_T,
    IS_T,
    BEGIN_T,
    END_T,
    SEMICOLON_T,
    GLOBAL_T,
    PROCEDURE_T,
    VARIABLE_T,
    COLON_T,
    OPEN_PARENTHESIS_T,
    CLOSE_PARENTHESIS_T,
    INTEGER_T,
    FLOAT_T,
    STRING_T,
    BOOL_T,
    COMMA_T,
    OPEN_BRACKET_T,
    CLOSE_BRACKET_T,
    NUMBER_T,
    IF_T,
    FOR_T,
    RETURN_T,
    ASSIGNMENT_OP_T,
    NOT_T,
    AND_OP_T,
    OR_OP_T,
    PLUS_OP_T,
    MINUS_OP_T,
    LESS_OP_T,
    GREATER_EQUAL_OP_T,
    LESS_EQUAL_OP_T,
    GREATER_OP_T,
    EQUALITY_OP_T,
    INEQUALITY_OP_T,
    MULTIPLY_OP_T,
    DIVIDE_OP_T,
    STRING_LITERAL_T,
    TRUE_T,
    FALSE_T,
    THEN_T,
    ELSE_T,
    PERIOD_T,
    END_OF_FILE,
    QUOTE_T,
    NONE
};

enum TokenMark{
    NONE_M = 0,
    PROCEDURE_M = 1
};

class TokenTools{
    public:
        static std::string token_type_to_string(TokenType type){
            static const char * enumStrings[] = {"PROGRAM_T","IS_T","SEMICOLON_T","BEGIN_T","END_T","GLOBAL_T","PROCEDURE_T","COLON_T",
            "OPEN_PARENTHESIS_T","CLOSE_PARENTHESIS_T","COMMA_T","VARIABLE_T","OPEN_BRACKET_T","CLOSE_BRACKET_T","INTEGER_T","FLOAT_T","STRING_T"
            ,"BOOL_T","ASSIGNMENT_OP_T","IF_T","THEN_T","ELSE_T","FOR_T","RETURN_T","AND_OP_T","OR_OP_T","NOT_OP_T","PLUS_OP_T","MINUS_OP_T",
            "LESSTHAN_OP_T","GREATER_EQUAL_OP_T","LESS_EQUAL_OP_T","GREATERTHAN_OP_T","EQUALITY_OP_T","INEQUALITY_OP_T","MULTIPLY_OP_T","DIVIDE_OP_T"
            ,"TRUE_T","FALSE_T","ALPHA_T","NUM_T","QUOTE_T","PERIOD_T","PROGRAM_NT","PROGRAM_HEADER_NT","PROGRAM_BODY_NT","IDENTIFIER_NT","DECLARATION_NT","STATEMENT_NT",
            "PROCEDURE_DECLARATION_NT","VARIABLE_DECLARATION_NT","PROCEDURE_HEADER_NT","PROCEDURE_BODY_NT","TYPE_MARK_NT","PARAMETER_LIST_NT","PARAMETER_NT"
            ,"BOUND_NT","NUMBER_NT","ASSIGNMENT_STATEMENT_NT","IF_STATEMENT_NT","LOOP_STATEMENT_NT","RETURN_STATEMENT_NT","PROCEDURE_CALL_NT","ARGUMENT_LIST_NT",
            "DESTINATION_NT","EXPRESSION_NT","ARITH_OP_NT","RELATION_NT","TERM_NT","FACTOR_NT","NAME_NT","STRING_NT","DECLARATION_ARRAY_NT","STATEMENT_ARRAY_NT",
            "EXPRESSION_RECURSE_NT","STRING_LITERAL_NT", "ARITH_OP_RECURSE_NT", "RELATION_RECURSE_NT", "TERM_RECURSE_NT","BOUND_OBJ_NT",
            "PARAMETER_LIST_OBJ_NT", "ARGUMENT_LIST_OBJ_NT","ELSE_BLOCK_NT","EXPRESSION_BLOCK_OBJ_NT","END_OF_FILE","NONE" };
            return enumStrings[type];
        }
};

class Token{
    public:
        enum TokenType type;
        std::string tokenString;
        enum TokenMark tokenMark;
        Token(TokenType typeInput){
            type = typeInput;
        };
        Token(TokenType typeInput, std::string tokenStringInput){
            type = typeInput;
            tokenString = tokenStringInput;
        }
        Token(TokenType typeInput, std::string tokenStringInput, TokenMark tokenMarkInput){
            type = typeInput;
            tokenString = tokenStringInput;
            tokenMark = tokenMarkInput;
        }
};

#endif