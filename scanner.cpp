/*
Input: A line of a file
Output: A stream of tokens to parse
*/
#include <iostream>
#include <map>
#include "scanner.h"

bool check_if_number(std::string tokenString){
    std::string::const_iterator it = tokenString.begin();
    bool decimalEncountered = false;
    while (it != tokenString.end()){
        if(*it == '.'){
            if(decimalEncountered == true){
                return false;
            }
            else{
                decimalEncountered = true;
            }
        }
        else if(isdigit(*it)){
            it++;
        }
        else{
            return false;
        }
    }
    return true;
}

bool check_if_string(std::string tokenString){
    if(tokenString[0] == *"\"" && tokenString.back() == *"\""){
        return true;
    }
    else{
        return false;
    }
}

Token* match_token(std::string* buffer, SymbolTable* symbolTable){
    Token* matched_token;
    if(check_if_number(*buffer)){
        matched_token = new Token(NUMBER_T, *buffer);
        return matched_token;
    }
    else if(check_if_string(*buffer)){
        matched_token = new Token(STRING_LITERAL_T, *buffer);
    }
    else{
        matched_token = symbolTable->mapGet(buffer);
        if(matched_token != nullptr){
            return matched_token;
        }
        else{
            symbolTable->mapSet(buffer);
            return symbolTable->mapGet(buffer);
        }
    }


};

Token* scan(struct ScannerParams* scannerParams){
    Token* nextToken = nullptr;
    std::string* buffer = new std::string("");
    if(scannerParams->nextToken != NONE){
        std::cout<<"Returning stored next token of type "<<TokenTools::token_type_to_string(scannerParams->nextToken) << "\n";
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
                            scannerParams->errorReporter->reportError("No space detected between token and comment.", scannerParams->file->get_line_count());
                        }
                        else{
                            *buffer = "";
                        }
                        
                    }
                    else{
                        *buffer += nextChar;
                        if(*buffer == ";"){
                            return new Token(SEMICOLON_T);
                        }
                        std::string lastCharacter = buffer->substr(buffer->size() - 1);
                        if(lastCharacter == " " || lastCharacter == "\n" || lastCharacter == ";" 
                        || lastCharacter == "(" || lastCharacter == "[" || lastCharacter == ")"
                        || lastCharacter == "]" || lastCharacter == "."){
                            if(lastCharacter == ";"){
                                std::cout<<"Next token should be a semicolon \n";
                                scannerParams->nextToken = SEMICOLON_T;
                            }
                            else if(lastCharacter == "("){
                                scannerParams->nextToken = OPEN_PARENTHESIS_T;
                            }
                            else if(lastCharacter == "["){
                                scannerParams->nextToken = OPEN_BRACKET_T;
                            }
                            else if(lastCharacter == ")"){
                                std::cout<<"Next token should be a closed parenthesis \n";
                                scannerParams->nextToken = CLOSE_PARENTHESIS_T;
                            }
                            else if(lastCharacter == "]"){
                                scannerParams->nextToken = CLOSE_BRACKET_T;
                            }
                            else if(lastCharacter == "."){
                                scannerParams->nextToken = PERIOD_T;
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