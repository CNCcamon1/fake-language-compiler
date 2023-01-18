/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include <map>
#include "scanner.h"



std::map<std::string, enum TokenType> make_terminal_dict(){
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
    stringToTypeDict["\""] = QUOTE_T;
    return stringToTypeDict;
}

std::map<std::string, enum TokenType> make_literal_dict(){
    std::map<std::string, enum TokenType> stringToTypeDict;
    stringToTypeDict["a"] = ALPHA_T;
    stringToTypeDict["b"] = ALPHA_T;
    stringToTypeDict["c"] = ALPHA_T;
    stringToTypeDict["d"] = ALPHA_T;
    stringToTypeDict["e"] = ALPHA_T;
    stringToTypeDict["f"] = ALPHA_T;
    stringToTypeDict["g"] = ALPHA_T;
    stringToTypeDict["h"] = ALPHA_T;
    stringToTypeDict["i"] = ALPHA_T;
    stringToTypeDict["j"] = ALPHA_T;
    stringToTypeDict["k"] = ALPHA_T;
    stringToTypeDict["l"] = ALPHA_T;
    stringToTypeDict["m"] = ALPHA_T;
    stringToTypeDict["n"] = ALPHA_T;
    stringToTypeDict["o"] = ALPHA_T;
    stringToTypeDict["p"] = ALPHA_T;
    stringToTypeDict["q"] = ALPHA_T;
    stringToTypeDict["r"] = ALPHA_T;
    stringToTypeDict["s"] = ALPHA_T;
    stringToTypeDict["t"] = ALPHA_T;
    stringToTypeDict["u"] = ALPHA_T;
    stringToTypeDict["v"] = ALPHA_T;
    stringToTypeDict["w"] = ALPHA_T;
    stringToTypeDict["x"] = ALPHA_T;
    stringToTypeDict["y"] = ALPHA_T;
    stringToTypeDict["z"] = ALPHA_T;
    stringToTypeDict["A"] = ALPHA_T;
    stringToTypeDict["B"] = ALPHA_T;
    stringToTypeDict["C"] = ALPHA_T;
    stringToTypeDict["D"] = ALPHA_T;
    stringToTypeDict["E"] = ALPHA_T;
    stringToTypeDict["F"] = ALPHA_T;
    stringToTypeDict["G"] = ALPHA_T;
    stringToTypeDict["H"] = ALPHA_T;
    stringToTypeDict["I"] = ALPHA_T;
    stringToTypeDict["J"] = ALPHA_T;
    stringToTypeDict["K"] = ALPHA_T;
    stringToTypeDict["L"] = ALPHA_T;
    stringToTypeDict["M"] = ALPHA_T;
    stringToTypeDict["N"] = ALPHA_T;
    stringToTypeDict["O"] = ALPHA_T;
    stringToTypeDict["P"] = ALPHA_T;
    stringToTypeDict["Q"] = ALPHA_T;
    stringToTypeDict["R"] = ALPHA_T;
    stringToTypeDict["S"] = ALPHA_T;
    stringToTypeDict["T"] = ALPHA_T;
    stringToTypeDict["U"] = ALPHA_T;
    stringToTypeDict["V"] = ALPHA_T;
    stringToTypeDict["W"] = ALPHA_T;
    stringToTypeDict["X"] = ALPHA_T;
    stringToTypeDict["Y"] = ALPHA_T;
    stringToTypeDict["Z"] = ALPHA_T;  
    stringToTypeDict["0"] = NUM_T;  
    stringToTypeDict["1"] = NUM_T;  
    stringToTypeDict["2"] = NUM_T;  
    stringToTypeDict["3"] = NUM_T;  
    stringToTypeDict["4"] = NUM_T;  
    stringToTypeDict["5"] = NUM_T;  
    stringToTypeDict["6"] = NUM_T;  
    stringToTypeDict["7"] = NUM_T;  
    stringToTypeDict["8"] = NUM_T;  
    stringToTypeDict["9"] = NUM_T;  
    return stringToTypeDict;
}

std::string* to_lower_case(std::string* input){
    std::string* output = new std::string("");
    for(char& c : *input){
        *output += std::tolower(c);
    }
    return output;
}

Token* match_buffer_to_string(std::string* buffer, std::string matchString,
    enum TokenType typeIfMatch){
    if(*to_lower_case(buffer) == matchString){
        return new Token(typeIfMatch);
    }

}
void match_terminals(std::string* buffer, Token** match, std::map<std::string, enum TokenType>* stringToTypeDict){
    for (auto const& x : *stringToTypeDict){
        if(*match == nullptr){
            *match = match_buffer_to_string(buffer, x.first, x.second);
        }
        else{
            break;
        }
    }
}

TokenStream* match_literals(std::string* buffer, TokenStream* streamEnd, std::map<std::string, enum TokenType>* stringToTypeDict){
    Token* newToken = nullptr;
    TokenStream* stream = nullptr;
    TokenStream* lastStream = nullptr;
    for(char& c : *buffer){
        for (auto const& x : *stringToTypeDict){
            if(newToken == nullptr){
                newToken = match_buffer_to_string(new std::string(1,c), x.first, x.second);
            }
            else{
                TokenStream* newStream = new TokenStream(newToken);
                if(stream == nullptr){
                    stream = newStream;
                    lastStream = newStream;
                    newToken = nullptr;
                }
                else{
                    lastStream->link_tail(newStream);
                    lastStream = newStream;
                    newToken = nullptr;
                }
            }
        }
    }
    lastStream->link_tail(streamEnd);
    return stream;

}

TokenStream* match_token(std::string* buffer, 
    std::map<std::string, enum TokenType>* terminalDict,
    std::map<std::string, enum TokenType>* literalDict){
    
    Token* match = nullptr;
    match_terminals(buffer, &match, terminalDict);
    if(match != nullptr){
        //If the buffer IS a terminal, then just return it
        return new TokenStream(match);
    }
    else{
        //If not, it may be a string of literals followed by a terminal. 
        for(int i=1; i<(buffer->size()); i++){
            std::string endString = buffer->substr(buffer->size() - i);
            match_terminals(&endString, &match, terminalDict);
            if(match != nullptr){
                TokenStream* streamEnd = new TokenStream(match);
                std::string startString = buffer->substr(0, (buffer->size() - i));
                TokenStream* stream = match_literals(&startString, streamEnd, literalDict);
                return stream;
            }
        }
        return nullptr;
    }
};

TokenStream* scan_line(std::string line, CommentStatus* commentStatus, 
    std::map<std::string, enum TokenType>* terminalDict,
    std::map<std::string, enum TokenType>* literalDict){
    TokenStream* stream;
    TokenStream* lastTokenStream = new TokenStream(nullptr);
    TokenStream* foundTokenStream;
    std::string* buffer = new std::string("");

    stream = lastTokenStream;

    for(char& c : line){
        if(c != ' '){
            commentStatus->update_comment_status(c);
            if(commentStatus->in_comment() == false){
                *buffer += c;
                //Get the token stream which matches the buffer, if it exists
                foundTokenStream = match_token(buffer,terminalDict, literalDict);
                //If a valid token stream is found,
                if(foundTokenStream != nullptr){
                    lastTokenStream->link_end(foundTokenStream);
                    lastTokenStream = foundTokenStream;
                    *buffer = "";
                }
            }
            else{
                *buffer = "";
            }
        }
    }
    commentStatus->end_line();
    return stream;
};
