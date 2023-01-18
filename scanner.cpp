/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include "scanner.h"

TokenStream* scanLine(std::string line){
    std::cout<< line << std::endl;
    TokenStream* stream;
    TokenStream* lastTokenStream = new TokenStream(nullptr);
    Token* foundToken;
    stream = lastTokenStream;
    std::string* buffer;
    for(char& c : line){
        *buffer += c;
        foundToken = match_token(buffer);
        if(foundToken != nullptr){
            TokenStream* newTokenStream = new TokenStream(foundToken);
            lastTokenStream->link_tail(newTokenStream);
            lastTokenStream = newTokenStream;
            *buffer = "";
        }
    }
    return stream;
};

Token* match_token(std::string* buffer){
    return nullptr;
}