/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include "scanner.h"


Token* match_token(std::string* buffer){

    return nullptr;
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
