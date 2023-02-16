#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "types/grammar_option.h"
#include "types/grammar.h"
#include "scanner.h"

ParseTreeNode* parse_program_header_nt(ScannerParams* scannerParams, Token* currentToken, Grammar* grammar, ErrorReporter* reporter){
    ParseTreeNode* program_header_nt_node = new ParseTreeNode(PROGRAM_HEADER_NT);
    if(currentToken->type == PROGRAM_T){
        ParseTreeNode* program_t_node = new ParseTreeNode(PROGRAM_T);
        program_header_nt_node->add_child(program_t_node);
        Token* nextToken = scan(scannerParams);
        if(nextToken->type == IDENTIFIER_T){
            ParseTreeNode* program_name_t_node = new ParseTreeNode(IDENTIFIER_T, nextToken->tokenString);
            program_header_nt_node->add_child(program_name_t_node);
            nextToken = scan(scannerParams);
            if(nextToken->type == IS_T){
                ParseTreeNode* is_t_node = new ParseTreeNode(IS_T);
                program_header_nt_node->add_child(is_t_node);
            }   
            else{
                reporter->reportError("Program name should be followed by IS");
            }
        }
        else{
            reporter->reportError("Program header should include the name of the program");
        }
    }
    else{
        reporter->reportError("First token of a program should be a PROGRAM_T");
    }

    return program_header_nt_node;
}

ParseTreeNode* parse_program_body_nt(ScannerParams* scannerParams, Token* currentToken, Grammar* grammar, ErrorReporter* reporter){
    ParseTreeNode* program_body_nt_node = new ParseTreeNode(PROGRAM_BODY_NT);
    ParseTreeNode* 
}

ParseTreeNode* parse_program_nt(ScannerParams* scannerParams, Token* currentToken, Grammar* grammar, ErrorReporter* reporter){
    ParseTreeNode* program_nt_node = new ParseTreeNode(PROGRAM_NT);
    ParseTreeNode* program_header_nt_node = parse_program_header_nt(scannerParams, currentToken, grammar, reporter);
    program_nt_node->add_child(program_header_nt_node);
    Token* nextToken = scan(scannerParams);
    ParseTreeNode* program_body_nt_node = parse_program_body_nt(scannerParams, currentToken, grammar, reporter);
    program_nt_node->add_child(program_body_nt_node);
    return program_nt_node;
}

ParseTree* parse_file(struct ScannerParams* scannerParams){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        std::vector<Token*> encounteredTokens;
        Grammar* grammar = new Grammar();
        grammar->build_grammar();
        encounteredTokens.push_back(scan(scannerParams));
        encounteredTokens.push_back(scan(scannerParams));
        parse_node(parsedTree->rootNode, scannerParams, &encounteredTokens, 0, grammar);
        return parsedTree;
};
