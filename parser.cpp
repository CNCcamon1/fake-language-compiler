#include <vector>
#include <iostream>
#include "scanner.h"

bool parse_expression_nt(ScannerParams* scannerParams, Token** currentToken);

bool parse_statement_nt_set(ScannerParams* scannerParams, Token** currentToken);

bool parse_assignment_statement_nt(ScannerParams* scannerParams, Token** currentToken);

bool parse_return_statement_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing RETURN_STATEMENT_NT \n";
    if((*currentToken)->type == RETURN_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RETURN_STATEMENT_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Return statement must begin with 'return'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_for_statement_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing FOR_STATEMENT_NT \n";
    if((*currentToken)->type == FOR_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_assignment_statement_nt(scannerParams, currentToken);
            if((*currentToken)->type == SEMICOLON_T){
                *currentToken = scan(scannerParams);
                parse_expression_nt(scannerParams, currentToken);
                if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                    *currentToken = scan(scannerParams);
                    parse_statement_nt_set(scannerParams, currentToken);
                    if((*currentToken)->type == END_T){
                        *currentToken = scan(scannerParams);
                        if((*currentToken)->type == FOR_T){
                            *currentToken = scan(scannerParams);
                            std::cout<<"Successfully parsed FOR_STATEMENT_NT \n";
                            return true;
                        }
                        else{
                            scannerParams->errorReporter->reportError("For statement must have an 'end for'", scannerParams->file->get_line_count());
                            return false;
                        }
                    }
                    else{
                        scannerParams->errorReporter->reportError("For loop must have an 'end'", scannerParams->file->get_line_count());
                        return false;
                    }
                }
                else{
                    scannerParams->errorReporter->reportError("For expression must have a closing parentehsis", scannerParams->file->get_line_count());
                    return false;
                }
            }
            else{
                scannerParams->errorReporter->reportError("Assignment statement in for loop must be followed by a semicolon", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("For statement must have an opening parenthesis", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("For statement must begin with 'for'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_if_statement_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing IF_STATEMENT_NT \n";
    if((*currentToken)->type == IF_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken);
            if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                *currentToken = scan(scannerParams);
                if((*currentToken)->type == THEN_T){
                    *currentToken = scan(scannerParams);
                    parse_statement_nt_set(scannerParams, currentToken);
                    if((*currentToken)->type == ELSE_T){
                        *currentToken = scan(scannerParams);
                        parse_statement_nt_set(scannerParams, currentToken);
                    }

                    if((*currentToken)->type == END_T){
                        *currentToken = scan(scannerParams);
                        if((*currentToken)->type == IF_T){
                            std::cout<<"Successfully parsed IF_STATEMENT_NT \n";
                            *currentToken = scan(scannerParams);
                            return true;
                        }
                        else{
                            scannerParams->errorReporter->reportError("If statement must end with 'end if'", scannerParams->file->get_line_count());
                            return false;
                        }
                    }
                    else{
                        scannerParams->errorReporter->reportError("If statement must have an 'end if", scannerParams->file->get_line_count());
                        return false;
                    }
                }
                else{
                    scannerParams->errorReporter->reportError("If condition must include 'then'", scannerParams->file->get_line_count());
                    return false;
                }
            }
            else{
                scannerParams->errorReporter->reportError("If condition must be followed by a closing parenthesis", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("If statement must have a set of parenthesis", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("If statement must begin with 'if'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_name_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing NAME_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed NAME_NT \n";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Expression must be followed by a closing bracket \n", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed NAME_NT \n";
            return true;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Name must start with an identifier", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_argument_list_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing ARGUMENT_LIST_NT \n";
    if((*currentToken)->type != CLOSE_PARENTHESIS_T){
        parse_expression_nt(scannerParams, currentToken);
        if((*currentToken)->type == COMMA_T){
            *currentToken = scan(scannerParams);
            parse_argument_list_nt(scannerParams, currentToken);
        }
    }

    std::cout<<"Successfully parsed ARGUMENT_LIST_NT \n";
    return true;
}

bool parse_procedure_call_or_name_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROCEDURE_CALL_OR_NAME_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_argument_list_nt(scannerParams, currentToken);
            if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Argument list must be followed by a closing parenthesis", scannerParams->file->get_line_count());
                return false;
            }
        }
        else if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Expression must be followed by a closing bracket", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
            return true;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Procedure call or name must include an identifier", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_factor_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing FACTOR_NT \n";
    if((*currentToken)->type == OPEN_PARENTHESIS_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken);
        if((*currentToken)->type == CLOSE_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            std::cout<<"Successfully parsed FACTOR_NT \n";
            return true;
        }
        else{
            scannerParams->errorReporter->reportError("Expression must be followed by a closing parenthesis", scannerParams->file->get_line_count());
            return false;
        }
    }
    else if((*currentToken)->type == IDENTIFIER_T){
        parse_procedure_call_or_name_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed FACTOR_NT \n";
        return true;
    }
    else if((*currentToken)->type == MINUS_OP_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == NUMBER_T){
            *currentToken = scan(scannerParams);
            std::cout<<"Successfully parsed FACTOR_NT \n";
            return true;
        }
        else if((*currentToken)->type == IDENTIFIER_T){
            parse_name_nt(scannerParams, currentToken);
            std::cout<<"Successfully parsed FACTOR_NT \n";
            return true;
        }

    }
    else if((*currentToken)->type == NUMBER_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed FACTOR_NT \n";
        return true;
    }
    else if((*currentToken)->type == STRING_LITERAL_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed FACTOR_NT \n";
        return true;
    }
    else if((*currentToken)->type == TRUE_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed FACTOR_NT \n";
        return true;
    }
    else if((*currentToken)->type == FALSE_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed FACTOR_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Couldn't match factor to any possible derivations \n", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_term_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing TERM_NT \n";
    parse_factor_nt(scannerParams, currentToken);
    if((*currentToken)->type == MULTIPLY_OP_T){
        *currentToken = scan(scannerParams);
        parse_factor_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
    else if((*currentToken)->type == DIVIDE_OP_T){
        *currentToken = scan(scannerParams);
        parse_factor_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
    else{
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
}

bool parse_relation_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing RELATION_NT \n";
    parse_term_nt(scannerParams, currentToken);
    if((*currentToken)->type == LESS_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == GREATER_EQUAL_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == LESS_EQUAL_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == GREATER_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == EQUALITY_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == INEQUALITY_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else{
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;        
    }
}

bool parse_arith_op_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing ARITH_OP_NT \n";
    parse_relation_nt(scannerParams, currentToken);
    if((*currentToken)->type == PLUS_OP_T){
        *currentToken = scan(scannerParams);
        parse_relation_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true;
    }
    else if((*currentToken)->type == MINUS_OP_T){
        *currentToken = scan(scannerParams);
        parse_relation_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true;
    }
    else{
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true; 
    }
}

bool parse_expression_recurse_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing EXPRESSION_RECURSE_NT \n";
    if((*currentToken)->type == AND_OP_T){
        *currentToken = scan(scannerParams);
        parse_arith_op_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed EXPRESSION_RECURSE_NT \n";
        return true;
    }
    else if((*currentToken)->type == OR_OP_T){
        *currentToken = scan(scannerParams);
        parse_arith_op_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed EXPRESSION_RECURSE_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Expression should include & or |", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_expression_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing EXPRESSION_NT \n";
    if((*currentToken)->type == NOT_T){
        parse_arith_op_nt(scannerParams, currentToken);
        if((*currentToken)->type == AND_OP_T || (*currentToken)->type == OR_OP_T){
            parse_expression_recurse_nt(scannerParams, currentToken);
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
        else{
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
    }
    else{
        parse_arith_op_nt(scannerParams, currentToken);
        if((*currentToken)->type == AND_OP_T || (*currentToken)->type == OR_OP_T){
            parse_expression_recurse_nt(scannerParams, currentToken);
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
        else{
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
    }
}

bool parse_destination_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing DESTINATION_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed DESTINATION_NT \n";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Expression must be followed by a closing bracket", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed DESTINATION_NT \n";
            return true;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Destination must start with an identifier", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_assignment_statement_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing ASSIGNMENT_STATEMENT_NT \n";
    parse_destination_nt(scannerParams, currentToken);
    if((*currentToken)->type == ASSIGNMENT_OP_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed ASSIGNMENT_STATEMENT_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Assignment statement must use an assignment operator", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_statement_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing STATEMENT_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        parse_assignment_statement_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == IF_T){
        parse_if_statement_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == FOR_T){
        parse_for_statement_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == RETURN_T){
        parse_return_statement_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Statement must be an assignment statement, an if statement, a for statement, or a return statement", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_statement_nt_set(ScannerParams* scannerParams, Token** currentToken){
     std::cout<<"Parsing STATEMENT_NT_SET \n";
    bool endFound = false;
    while(!endFound){
        if((*currentToken)->type == END_T || (*currentToken)->type == ELSE_T){
            endFound = true;
            break;
        }
        else{
            parse_statement_nt(scannerParams,currentToken);
            if((*currentToken)->type == SEMICOLON_T){
                std::cout<<"Advancing to next statement \n";
                *currentToken = scan(scannerParams);
            }

            else{
                scannerParams->errorReporter->reportError("Statement can only be followed by another statement or END", scannerParams->file->get_line_count());
                return false;
            }
        }

    }

    std::cout<<"Successfully parsed STATEMENT_NT_SET \n";
    return true;
}

bool parse_declaration_nt_set(ScannerParams* scannerParams, Token** currentToken);

bool parse_procedure_body_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROCEDURE_BODY_NT \n";
    parse_declaration_nt_set(scannerParams, currentToken);
    if((*currentToken)->type == BEGIN_T){
        *currentToken = scan(scannerParams);
        parse_statement_nt_set(scannerParams, currentToken);
        if((*currentToken)->type == END_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == PROCEDURE_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_BODY_NT \n";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Procedure ending must include 'procedure'", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("Statement set must be followed by 'end'", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Declaration set must be followed by 'begin'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_bound_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing BOUND_NT \n";
    if((*currentToken)->type == NUMBER_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed BOUNT_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Bound must be a number", scannerParams->file->get_line_count());
        return false;
    }

}

bool parse_type_mark_nt(ScannerParams* scannerParams, Token** currentToken){
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
        scannerParams->errorReporter->reportError("TYpe mark must be 'integer', 'float', 'string', or 'bool'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_variable_declaration_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing VARIABLE_DECLARATION_NT \n";
    if((*currentToken)->type == VARIABLE_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == IDENTIFIER_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == COLON_T){
                *currentToken = scan(scannerParams);
                parse_type_mark_nt(scannerParams, currentToken);
                if((*currentToken)->type == OPEN_BRACKET_T){
                    *currentToken = scan(scannerParams);
                    parse_bound_nt(scannerParams, currentToken);
                    if((*currentToken)->type == CLOSE_BRACKET_T){
                        *currentToken = scan(scannerParams);
                        std::cout<<"Successfully parsed VARIABLE_DECLARATION_NT \n";
                        return true;
                    }
                    else{
                        scannerParams->errorReporter->reportError("Bound must be followed by a closing bracket", scannerParams->file->get_line_count());
                        return false;
                    }
                }
                else{
                    std::cout<<"Successfully parsed VARIABLE_DECLARATION_NT \n";
                    return true;
                }
            }
            else{
                scannerParams->errorReporter->reportError("Variable declaration must include a colon", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("Variable declaration must include an identifier", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Variable declaration must start with 'variable'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_parameter_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PARAMETER_NT \n";
    parse_variable_declaration_nt(scannerParams, currentToken);
    std::cout<<"Successfully parsed PARAMETER_NT \n";
    return true;
}

bool parse_parameter_list_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PARAMTER_LIST_NT \n";
    bool endFound = false;
    while(!endFound){
        parse_parameter_nt(scannerParams, currentToken);
        if((*currentToken)->type == COMMA_T){
            *currentToken = scan(scannerParams);
            std::cout<<"Advancing to next parameter \n";
        }
        else if((*currentToken)->type == CLOSE_PARENTHESIS_T){
            endFound = true;
        }
        else{
            scannerParams->errorReporter->reportError("Parameter must be followed by either a close parenthesis or another parameter", scannerParams->file->get_line_count());
            return false;
        }
    }
    std::cout<<"Successfully parsed PARAMETER_LIST_NT \n";
    return true;
}

bool parse_procedure_header_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROCEDURE_HEADER_NT \n";
    if((*currentToken)->type == PROCEDURE_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == IDENTIFIER_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == COLON_T){
                *currentToken = scan(scannerParams);
                parse_type_mark_nt(scannerParams, currentToken);
                if((*currentToken)->type == OPEN_PARENTHESIS_T){
                    *currentToken = scan(scannerParams);
                    parse_parameter_list_nt(scannerParams, currentToken);
                    if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                        *currentToken = scan(scannerParams);
                        std::cout<<"Successfully parsed PROCEDURE_HEADER_NT \n";
                        return true;
                    }
                    else{
                        scannerParams->errorReporter->reportError("Procedure header must include parenthesis", scannerParams->file->get_line_count());
                        return false;
                    }
                }
                else{
                    scannerParams->errorReporter->reportError("Procedure header must include parenthesis", scannerParams->file->get_line_count());
                    return false;
                }
            }
            else{
                scannerParams->errorReporter->reportError("Procedure header must include a colon", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("Procedure header must include an identifier", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Procedure header must start with 'procedure'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_procedure_declaration_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROCEDURE_DECLARATION_NT \n";
    parse_procedure_header_nt(scannerParams, currentToken);
    parse_procedure_body_nt(scannerParams, currentToken);
    std::cout<<"Successfully parsed PROCEDURE_DECLARATION_NT \n";
}

bool parse_procedure_or_variable_declaration_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
    if((*currentToken)->type == PROCEDURE_T){
        parse_procedure_declaration_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == VARIABLE_T){
        parse_variable_declaration_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed PROCEDURE_OR_VARIABLE_DECLARATION_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Declaration must start with either 'procedure' or 'variable'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_declaration_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing DECLARATION_NT \n";
    if((*currentToken)->type == GLOBAL_T){
        *currentToken = scan(scannerParams);
        parse_procedure_or_variable_declaration_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed declaration \n";
        return true;
    }
    else{
        parse_procedure_or_variable_declaration_nt(scannerParams, currentToken);
        std::cout<<"Successfully parsed declaration \n";
        return true;
    }
}

bool parse_declaration_nt_set(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing DECLARATION_NT_SET \n";
    bool endFound = false;
    while(!endFound){
        if((*currentToken)->type == BEGIN_T){
            endFound = true;
            break;
        }
        else{
            parse_declaration_nt(scannerParams,currentToken);
            if((*currentToken)->type == SEMICOLON_T){
                std::cout<<"Advancing to next declaration \n";
                *currentToken = scan(scannerParams);
            }
            else{
                scannerParams->errorReporter->reportError("Declaration can only be followed by another declaration or BEGIN", scannerParams->file->get_line_count());
                return false;
            }
        }

    }

    std::cout<<"Successfully parsed declaration set. \n";
    return true;
}

bool parse_program_header_nt(ScannerParams* scannerParams, Token** currentToken){
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
                scannerParams->errorReporter->reportError("Program identifier must be followed by 'is'", scannerParams->file->get_line_count());
                return false;
            }
        }
        else{
            scannerParams->errorReporter->reportError("Program header must include an identifier", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Program header must begin with PROGRAM_T", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_program_body_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROGRAM_BODY_NT \n";
    parse_declaration_nt_set(scannerParams, currentToken);
    if((*currentToken)->type == BEGIN_T){
        *currentToken = scan(scannerParams);
        parse_statement_nt_set(scannerParams, currentToken);
        if((*currentToken)->type == END_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == PROGRAM_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROGRAM_HEADER_NT \n";
                return true;
            }
            else{
                scannerParams->errorReporter->reportError("Program must end with 'end program'", scannerParams->file->get_line_count());
                return false; 
            }
        }
        else{
            scannerParams->errorReporter->reportError("Program must end with 'end program'", scannerParams->file->get_line_count());
            return false;
        }
    }
    else{
        scannerParams->errorReporter->reportError("Declaration array must be followed by 'begin'", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_program_nt(ScannerParams* scannerParams, Token** currentToken){
    std::cout<<"Parsing PROGRAM_NT \n";
    parse_program_header_nt(scannerParams, currentToken);
    parse_program_body_nt(scannerParams, currentToken);
    if((*currentToken)->type == PERIOD_T){
        std::cout<<"Successfully parsed PROGRAM_NT \n";
        return true;
    }
    else{
        scannerParams->errorReporter->reportError("Program must end with period", scannerParams->file->get_line_count());
        return false;
    }
}

bool parse_file(ScannerParams* scannerParams){
    Token* token = scan(scannerParams);
    Token** currentToken = &token;
    parse_program_nt(scannerParams, currentToken);
    if(scannerParams->errorReporter->errorStatus == true){
        scannerParams->errorReporter->print_errors();
        return false;
    }
    return true;
};
