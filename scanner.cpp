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

Token* match_static_token(std::string* buffer){
    Token* nextToken;
    if(*buffer == ";"){
        nextToken = new Token(SEMICOLON_T);
    }
    else if(*buffer == "("){
        nextToken = new Token(OPEN_PARENTHESIS_T);
    }
    else if(*buffer == ")"){
        nextToken = new Token(CLOSE_PARENTHESIS_T);
    }
    else if(*buffer == "["){
        nextToken = new Token(OPEN_BRACKET_T);
    }
    else if(*buffer == "]"){
        nextToken = new Token(CLOSE_BRACKET_T);
    }
    else if(*buffer == "."){
        nextToken = new Token(PERIOD_T);
    }
    return nextToken;
}

bool character_is_static_token(char nextChar){
    return (nextChar == ';' || nextChar == '(' || nextChar == ')'
        || nextChar == '[' || nextChar == ']' || nextChar == '.');
}

bool string_is_static_token(std::string nextChar){
    return (nextChar == ";" || nextChar == "(" || nextChar == ")"
        || nextChar == "[" || nextChar == "]" || nextChar == ".");
}

Token* match_non_static_token(std::string* buffer, SymbolTable* symbolTable){
    Token* matched_token;
    if(check_if_number(*buffer)){
        matched_token = new Token(NUMBER_T, *buffer);
        return matched_token;
    }
    else if(check_if_string(*buffer)){
        matched_token = new Token(STRING_LITERAL_T, *buffer);
        return matched_token;
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
    std::string* buffer;
    //Check if there is a prebuffered value
    if(*scannerParams->preBuffered != ""){
        //If there is, set the buffer equal to it
        buffer = new std::string();
        *buffer = *scannerParams->preBuffered;
        *scannerParams->preBuffered = "";
        //If the preBuffered value is a static token, just return it
        if(string_is_static_token(*buffer)){
           return match_static_token(buffer);
        }
        //Otherwise continue on with the prebuffered value already in the buffer
    }
    else{
        //If there is no prebuffered value, just start from nothing
        buffer = new std::string();
    }
    //Loop until a valid token has been scanned
    while(nextToken == nullptr){
            try{
                //Get the next character from the file
                char nextChar = scannerParams->file->get_next_char();
                scannerParams->commentStatus->update_comment_status(&nextChar, scannerParams->file);
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
                    //Check the special case for the colon
                    if(*buffer == ":"){
                        //If the buffer is a colon and the next character is an equals sign, then we can safely return an assignment operator
                        if(nextChar == '='){
                            nextToken = new Token(ASSIGNMENT_OP_T);
                        }
                        else{
                            //Otherwise check if the colon is followed by whitespace or some other character
                            if(nextChar != ' ' && nextChar != '\n'){
                                //If the colon is followed by something other than whitespace, make that the prebuffered value
                                *scannerParams->preBuffered = nextChar;
                            }
                            //Return a colon
                            nextToken = new Token(COLON_T);
                        }
                    }
                    else{
                        //Check if the next character is a static token
                        if(character_is_static_token(nextChar)){
                            //If it is, check if the buffer is empty
                            if(*buffer == ""){
                                //If the buffer is empty and the next character is a static token then we can just return that
                                *buffer += nextChar;
                                nextToken = match_static_token(buffer);
                            }
                            else{
                                //We've found the end of a non-static token. Return that and set the prebuffered value to be that static token
                                nextToken = match_non_static_token(buffer, scannerParams->symbolTable);
                                *scannerParams->preBuffered = nextChar;
                            }
                        }
                        //Check the special case that the next character is a colon
                        else if(nextChar == ':'){
                            if(*buffer == ""){
                                *buffer += ":";
                            }
                            else{
                                nextToken = match_non_static_token(buffer, scannerParams->symbolTable);
                                *scannerParams->preBuffered = ":";
                            }

                        }
                        //If the string doesn't end with a static token but does end with a whitespace, then we've found the end of a nonstatic token but shouldn't buffer anything
                        else if(nextChar == ' ' || nextChar == '\n'){
                            if(*buffer != ""){
                                nextToken = match_non_static_token(buffer, scannerParams->symbolTable);
                            }

                        }
                        else{
                            *buffer += nextChar;
                        }
                    }

                }


            }
            catch(EndOfFileException& e){
                nextToken = new Token(END_OF_FILE);
            }
        }


    return nextToken;
}