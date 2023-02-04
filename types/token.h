#include <string>

#ifndef TOKEN_TYPE
#define TOKEN_TYPE

enum TokenType{
    PROGRAM_T = 0,
    IS_T = 1,
    SEMICOLON_T = 2,
    BEGIN_T = 3,
    END_T = 4,
    GLOBAL_T = 5,
    PROCEDURE_T = 6,
    COLON_T = 7,
    OPEN_PARENTHESIS_T = 8,
    CLOSE_PARENTHESIS_T = 9,
    COMMA_T = 10,
    VARIABLE_T = 11,
    OPEN_BRACKET_T = 12,
    CLOSE_BRACKET_T = 13,
    INTEGER_T = 14,
    FLOAT_T = 15,
    STRING_T = 16,
    BOOL_T = 17,
    ASSIGNMENT_OP_T = 18,
    IF_T = 19,
    THEN_T = 20,
    ELSE_T = 21,
    FOR_T = 22,
    RETURN_T = 23,
    AND_OP_T = 24,
    OR_OP_T = 25,
    NOT_OP_T = 26,
    PLUS_OP_T = 27,
    MINUS_OP_T = 28,
    LESSTHAN_OP_T = 29,
    GREATER_EQUAL_OP_T = 30,
    LESS_EQUAL_OP_T = 31,
    GREATERTHAN_OP_T = 32,
    EQUALITY_OP_T = 33,
    INEQUALITY_OP_T= 34,
    MULTIPLY_OP_T = 35,
    DIVIDE_OP_T = 36,
    TRUE_T = 37,
    FALSE_T = 38,
    ALPHA_T = 39,
    NUM_T = 40,
    QUOTE_T = 41,
    PERIOD_T = 42,
    PROGRAM_NT = 43,
    PROGRAM_HEADER_NT = 44,
    PROGRAM_BODY_NT = 45,
    IDENTIFIER_NT = 46,
    DECLARATION_NT = 47,
    STATEMENT_NT = 48,
    PROCEDURE_DECLARATION_NT = 49,
    VARIABLE_DECLARATION_NT = 50,
    PROCEDURE_HEADER_NT = 51,
    PROCEDURE_BODY_NT = 52,
    TYPE_MARK_NT = 53,
    PARAMETER_LIST_NT = 54,
    PARAMETER_NT = 55,
    BOUND_NT = 56,
    NUMBER_NT = 57,
    ASSIGNMENT_STATEMENT_NT = 58,
    IF_STATEMENT_NT = 59,
    LOOP_STATEMENT_NT = 60,
    RETURN_STATEMENT_NT = 61,
    PROCEDURE_CALL_NT = 62,
    ARGUMENT_LIST_NT = 63,
    DESTINATION_NT = 64,
    EXPRESSION_NT = 65,
    ARITH_OP_NT = 66,
    RELATION_NT = 67,
    TERM_NT = 68,
    FACTOR_NT = 69,
    NAME_NT = 70,
    STRING_NT = 71,
    DECLARATION_OBJ_NT = 72,
    STATEMENT_OBJ_NT = 73,
    EXPRESSION_RECURSE_NT = 74,
    STRING_LITERAL_NT = 75,
    ARITH_OP_RECURSE_NT = 76,
    RELATION_RECURSE_NT = 77,
    TERM_RECURSE_NT = 78,
    BOUND_OBJ_NT = 79,
    PARAMETER_LIST_OBJ_NT = 80,
    ARGUMENT_LIST_OBJ_NT = 81,
    ELSE_BLOCK_NT = 82,
    EXPRESSION_BLOCK_OBJ_NT = 83,
    END_OF_FILE = 84,
    NONE = 85
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