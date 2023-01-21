#include <iostream>
#include <string>
#include <fstream>
#include "error_reporter.h"

#ifndef INFILE_TYPE
#define INFILE_TYPE

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

        int get_line_count(){
            return lineCount;
        }
};

#endif