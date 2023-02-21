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
            lineCount = 1;
        }

        char get_next_char(){
            char next;
            file.get(next);
            if(next == '\n'){
                lineCount++;
                std::cout<<"Advancing to line "<<lineCount<<"\n";
            }
            if(next == '\t'){
                return get_next_char();
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