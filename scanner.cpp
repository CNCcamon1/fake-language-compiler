/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include <map>
#include "scanner.h"

Token* match_token(std::string* buffer, SymbolTable* symbolTable){
    Token* matched_token = symbolTable->mapGet(buffer);
    if(matched_token != nullptr){
        return matched_token;
    }
    else{
        symbolTable->mapSet(buffer);
        return symbolTable->mapGet(buffer);
    }
};

Token* scan(struct ScannerParams* scannerParams){
    Token* nextToken = nullptr;
    std::string* buffer = new std::string("");
    if(scannerParams->nextToken != NONE){
        nextToken = new Token(scannerParams->nextToken);
        scannerParams->nextToken = NONE;
    }
    else{
           while(nextToken == nullptr){
                try{
                    char nextChar = scannerParams->file->get_next_char();
                    scannerParams->commentStatus->update_comment_status(nextChar);
                    if(scannerParams->commentStatus->in_comment()){
                        //If in a comment, clear the buffer and don't process it
                        if(!(*buffer == "" || *buffer == "/" || *buffer == "*")){
                            /*If the buffer contains anything but the first character of a comment, 
                            and a comment has been entered, that's an error condition */
                            std::string* errorMessage = new std::string("No space detected between token and comment.");
                            scannerParams->errorReporter->reportError(errorMessage);
                        }
                        else{
                            *buffer = "";
                        }
                        
                    }
                    else{
                        *buffer += nextChar;
                        std::string lastCharacter = buffer->substr(buffer->size() - 1);
                        if(lastCharacter == " " || lastCharacter == "\n" || lastCharacter == ";" 
                        || lastCharacter == "(" || lastCharacter == "[" || lastCharacter == ")"
                        || lastCharacter == "]"){
                            if(lastCharacter == ";"){
                                scannerParams->nextToken = SEMICOLON_T;
                            }
                            else if(lastCharacter == "("){
                                scannerParams->nextToken = OPEN_PARENTHESIS_T;
                            }
                            else if(lastCharacter == "["){
                                scannerParams->nextToken = OPEN_BRACKET_T;
                            }
                            else if(lastCharacter == ")"){
                                scannerParams->nextToken = CLOSE_PARENTHESIS_T;
                            }
                            else if(lastCharacter == "]"){
                                scannerParams->nextToken = CLOSE_BRACKET_T;
                            }
                            //It is the end of a token
                            std::string token_string = buffer->substr(0, (buffer->size() - 1));
                            if(token_string != ""){
                                nextToken = match_token(&token_string, scannerParams->symbolTable);
                            }
                            else{
                                *buffer = "";
                            }
                        }
                    }


                }
                catch(EndOfFileException& e){
                    nextToken = new Token(END_OF_FILE);
                }

            }
        }


    return nextToken;
}