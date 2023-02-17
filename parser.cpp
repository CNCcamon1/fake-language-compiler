#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "types/grammar_option.h"
#include "types/grammar.h"
#include "scanner.h"

bool parse_number_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter)

bool parse_bound_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing BOUND_NT \n";
    parse_number_nt(scannerParams, currentToken, reporter);
    std::cout<<"Successfully parsed BOUNT_NT \n";
    return true;
}

bool parse_type_mark_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing TYPE_MARK_NT \n";
    if((*currentToken)->type == INTEGER_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed TYPE_MARK_NT \n";
        return true;
    }
    else if((*currentToken)->type == FLOAT_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed TYPE_MARK_NT \n";
        return true;
    }
    else if((*currentToken)->type == STRING_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed TYPE_MARK_NT \n";
        return true;
    }
    else if((*currentToken)->type == BOOL_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed TYPE_MARK_NT \n";
        return true;
    }
    else{
        reporter->reportError("TYpe mark must be 'integer', 'float', 'string', or 'bool'");
        return false;
    }
}

bool parse_variable_declaration_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing VARIABLE_DECLARATION_NT \n";
    if((*currentToken)->type == VARIABLE_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == IDENTIFIER_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == COLON_T){
                *currentToken = scan(scannerParams);
                parse_type_mark_nt(scannerParams, currentToken, reporter);
                if((*currentToken)->type == OPEN_BRACKET_T){
                    *currentToken = scan(scannerParams);
                    parse_bound_nt(scannerParams, currentToken, reporter);
                    if((*currentToken)->type == CLOSE_BRACKET_T){
                        *currentToken = scan(scannerParams);
                        std::cout<<"Successfully parsed VARIABLE_DECLARATION_NT \n";
                        return true;
                    }
                    else{
                        reporter->reportError("Bound must be followed by a closing bracket");
                        return false;
                    }
                }
                else{
                    std::cout<<"Successfully parsed VARIABLE_DECLARATION_NT \n";
                    return true;
                }
            }
            else{
                reporter->reportError("Variable declaration must include a colon");
                return false;
            }
        }
        else{
            reporter->reportError("Variable declaration must include an identifier");
            return false;
        }
    }
    else{
        reporter->reportError("Variable declaration must start with 'variable'");
        return false;
    }
}

bool parse_parameter_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PARAMETER_NT \n";
    parse_variable_declaration_nt(scannerParams, currentToken, reporter);
    std::cout<<"Successfully parsed PARAMETER_NT \n";
    return true;
}

bool parse_parameter_list_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PARAMTER_LIST_NT \n";
    bool endFound = false;
    while(!endFound){
        parse_parameter_nt(scannerParams, currentToken, reporter);
        if((*currentToken)->type == COMMA_T){
            *currentToken = scan(scannerParams);
            std::cout<<"Advancing to next parameter \n";
        }
        else if((*currentToken)->type == CLOSE_PARENTHESIS_T){
            endFound = true;
        }
        else{
            reporter->reportError("Parameter must be followed by either a close parenthesis or another parameter");
            return false
        }
    }
    std::cout<<"Successfully parsed PARAMETER_LIST_NT \n";
    return true;
}

bool parse_procedure_header_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROCEDURE_HEADER_NT \n";
    if((*currentToken)->type == PROCEDURE_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == IDENTIFIER_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == COLON_T){
                parse_type_mark_nt(scannerParams, currentToken, reporter);
                if((*currentToken)->type == OPEN_PARENTHESIS_T){
                    parse_parameter_list_nt(scannerParams, currentToken, reporter);
                    if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                        *currentToken = scan(scannerParams);
                        std::cout<<"Successfully parsed PROCEDURE_HEADER_NT \n";
                        return true;
                    }
                    else{
                        reporter->reportError("Procedure header must include parenthesis");
                        return false;
                    }
                }
                else{
                    reporter->reportError("Procedure header must include parenthesis");
                    return false;
                }
            }
            else{
                reporter->reportError("Procedure header must include a colon");
                return false;
            }
        }
        else{
            reporter->reportError("Procedure header must include an identifier");
            return false;
        }
    }
    else{
        reporter->reportError("Procedure header must start with 'procedure'");
        return false;
    }
}

bool parse_procedure_declaration_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROCEDURE_DECLARATION_NT \n";
    parse_procedure_header_nt(scannerParams, currentToken, reporter);
    parse_procedure_body_nt(scannerParams, currentToken, reporter);
    std::cout<<"Successfully parsed PROCEDURE_DECLARATION_NT \n";
}

bool parse_procedure_or_variable_declaration_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
    if((*currentToken)->type == PROCEDURE_T){
        parse_procedure_declaration_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == VARIABLE_T){
        parse_variable_declaration_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
        return true;
    }
    else{
        reporter->reportError("Declaration must start with either 'procedure' or 'variable'");
        return false;
    }
}

bool parse_declaration_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing DECLARATION_NT \n";
    if((*currentToken)->type == GLOBAL_T){
        *currentToken = scan(scannerParams);
        parse_procedure_or_variable_declaration_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed declaration \n";
        return true;
    }
    else{
        *currentToken = scan(scannerParams);
        parse_procedure_or_variable_declaration_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed declaration \n";
        return true;
    }
}

bool parse_declaration_nt_set(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing DECLARATION_NT_SET \n";
    bool endFound = false;
    while(!endFound){
        parse_declaration_nt(scannerParams,currentToken, reporter);
        if((*currentToken)->type == SEMICOLON_T){
            std::cout<<"Advancing to next declaration \n";
            *currentToken = scan(scannerParams);
        }
        else if((*currentToken)->type == BEGIN_T){
            endFound = true;
        }
        else{
            reporter->reportError("Declaration can only be followed by another declaration or BEGIN");
            return false;
        }
    }

    std::cout<<"Successfully parsed declaration set. \n";
    return true;
}

bool parse_program_header_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROGRAM_HEADER_NT \n";
    if((*currentToken)->type == PROGRAM_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == IDENTIFIER_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == IS_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROGRAM_NT \n";
                return true;
            }
            else{
                reporter->reportError("Program identifier must be followed by 'is'");
                return false;
            }
        }
        else{
            reporter->reportError("Program header must include an identifier");
            return false;
        }
    }
    else{
        reporter->reportError("Program header must begin with PROGRAM_T");
        return false;
    }
}

bool parse_program_body_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROGRAM_BODY_NT \n";
    parse_declaration_nt_set(scannerParams, currentToken, reporter);
    if((*currentToken)->type == BEGIN_T){
        *currentToken = scan(scannerParams);
        parse_statement_nt_set(scannerParams, currentToken, reporter);
        if((*currentToken)->type == END_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == PROGRAM_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROGRAM_HEADER_NT \n";
                return true;
            }
            else{
                reporter->reportError("Program must end with 'end program'");
                return false; 
            }
        }
        else{
            reporter->reportError("Program must end with 'end program'");
            return false;
        }
    }
    else{
        reporter->reportError("Declaration array must be followed by 'begin'");
        return false;
    }
}

bool parse_program_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROGRAM_NT \n";
    parse_program_header_nt(scannerParams, currentToken, reporter);
    parse_program_body_nt(scannerParams, currentToken, reporter);
    std::cout<<"Successfully parsed PROGRAM_NT \n";
    return true;
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
