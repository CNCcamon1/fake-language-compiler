#include <iostream>
#include <fstream>
#include "tokenStream.h"
#include "scanner.h"
#include "parser.h"

void compile_file(std::ifstream* file){
    std::string line;
    TokenStream* tokenStream;
    while (std::getline(*file, line)){
        scanLine(line, tokenStream);
        parseLine(tokenStream);
    }
}

int main(int argc, char** argv){
    if ( argc > 1 )
    {
        // The input file has been passed in the command line.
        // Read the data from it.
        std::ifstream ifile(argv[1]);
        if (ifile)
        {
            compile_file(&ifile);
        }
        else
        {
            // Deal with error condition
        }
    }
    else{
        //Deal with error condition
    }
    return 0;
}

