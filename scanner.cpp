/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include <map>
#include "scanner.h"

std::string* to_lower_case(std::string* input){
    std::string* output = new std::string("");
    for(char& c : *input){
        output += std::tolower(c);
    }
    return output;
}

void match_buffer_to_string(std::string* buffer, std::string matchString,
    enum TokenType typeIfMatch, Token* match){
    if(*to_lower_case(buffer) == matchString){
        match = new Token(typeIfMatch);
    }
}
void match_nonterminals(std::string* buffer, Token* match){
    std::map<std::string, enum TokenType> stringToTypeDict;
    stringToTypeDict["program"] = PROGRAM_T;
    stringToTypeDict["is"] = IS_T;
    stringToTypeDict["begin"] = BEGIN_T;
    stringToTypeDict["end"] = END_T;
    stringToTypeDict["global"] = GLOBAL_T;
    stringToTypeDict["procedure"] = PROCEDURE_T;
    stringToTypeDict["("] = OPEN_PARENTHESIS_T;
    stringToTypeDict[")"] = CLOSE_PARENTHESIS_T;
    stringToTypeDict[","] = COMMA_T;
    stringToTypeDict[";"] = SEMICOLON_T;
    stringToTypeDict["variable"] = VARIABLE_T;
    stringToTypeDict[":"] = COLON_T;
    stringToTypeDict["["] = OPEN_BRACKET_T;
    stringToTypeDict["]"] = CLOSE_BRACKET_T;
    stringToTypeDict["integer"] = INTEGER_T;
    stringToTypeDict["float"] = FLOAT_T;
    stringToTypeDict["string"] = STRING_T;
    stringToTypeDict["bool"] = BOOL_T;
    stringToTypeDict[":="] = ASSIGNMENT_OP_T;
    stringToTypeDict["if"] = IF_T;
    stringToTypeDict["then"] = THEN_T;
    stringToTypeDict["else"] = ELSE_T;
    stringToTypeDict["for"] = FOR_T;
    stringToTypeDict["return"] = RETURN_T;
    stringToTypeDict["&"] = AND_OP_T;
    stringToTypeDict["|"] = OR_OP_T;
    stringToTypeDict["not"] = NOT_OP_T;
    stringToTypeDict["+"] = PLUS_OP_T;
    stringToTypeDict["-"] = MINUS_OP_T;
    stringToTypeDict["<"] = LESSTHAN_OP_T;
    stringToTypeDict[">="] = GREATER_EQUAL_OP_T;
    stringToTypeDict["<="] = LESS_EQUAL_OP_T;
    stringToTypeDict[">"] = GREATERTHAN_OP_T;
    stringToTypeDict["=="] = EQUALITY_OP_T;
    stringToTypeDict["!="] = INEQUALITY_OP_T;
    stringToTypeDict["*"] = MULTIPLY_OP_T;
    stringToTypeDict["/"] = DIVIDE_OP_T;
    stringToTypeDict["true"] = TRUE_T;
    stringToTypeDict["false"] = FALSE_T;

    for (auto const& x : stringToTypeDict){
        if(match == nullptr){
            match_buffer_to_string(buffer, x.first, x.second, match);
        }
        else{
            break;
        }
    }
}

Token* match_token(std::string* buffer){
    Token* match;
    match_nonterminals(buffer, match);
    return match;
};

TokenStream* scanLine(std::string line, CommentStatus* commentStatus){
    TokenStream* stream;
    TokenStream* lastTokenStream = new TokenStream(nullptr);
    Token* foundToken;
    std::string* buffer = new std::string("");

    stream = lastTokenStream;

    for(char& c : line){
        commentStatus->update_comment_status(c);
        if(commentStatus->in_comment() == false){
            *buffer += c;
            foundToken = match_token(buffer);
            if(foundToken != nullptr){
                TokenStream* newTokenStream = new TokenStream(foundToken);
                lastTokenStream->link_tail(newTokenStream);
                lastTokenStream = newTokenStream;
                *buffer = "";
            }
        }
        else{
            *buffer = "";
        }

    }
    commentStatus->end_line();
    return stream;
};
