#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "types/grammar_option.h"
#include "types/grammar.h"
#include "scanner.h"

bool parse_expression_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter);

bool parse_statement_nt_set(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter);

bool parse_assignment_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter);

bool parse_return_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing RETURN_STATEMENT_NT \n";
    if((*currentToken)->type == RETURN_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RETURN_STATEMENT_NT \n";
        return true;
    }
    else{
        reporter->reportError("Return statement must begin with 'return'");
        return false;
    }
}

bool parse_for_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing FOR_STATEMENT_NT \n";
    if((*currentToken)->type == FOR_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_assignment_statement_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == SEMICOLON_T){
                *currentToken = scan(scannerParams);
                parse_expression_nt(scannerParams, currentToken, reporter);
                if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                    *currentToken = scan(scannerParams);
                    parse_statement_nt_set(scannerParams, currentToken, reporter);
                    if((*currentToken)->type == END_T){
                        *currentToken = scan(scannerParams);
                        if((*currentToken)->type == FOR_T){
                            *currentToken = scan(scannerParams);
                            std::cout<<"Successfully parsed FOR_STATEMENT_NT \n";
                            return true;
                        }
                        else{
                            reporter->reportError("For statement must have an 'end for'");
                            return false;
                        }
                    }
                    else{
                        reporter->reportError("For loop must have an 'end'");
                        return false;
                    }
                }
                else{
                    reporter->reportError("For expression must have a closing parentehsis");
                    return false;
                }
            }
            else{
                reporter->reportError("Assignment statement in for loop must be followed by a semicolon");
                return false;
            }
        }
        else{
            reporter->reportError("For statement must have an opening parenthesis");
            return false;
        }
    }
    else{
        reporter->reportError("For statement must begin with 'for'");
        return false;
    }
}

bool parse_if_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing IF_STATEMENT_NT \n";
    if((*currentToken)->type == IF_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                *currentToken = scan(scannerParams);
                if((*currentToken)->type == THEN_T){
                    *currentToken = scan(scannerParams);
                    parse_statement_nt_set(scannerParams, currentToken, reporter);
                    if((*currentToken)->type == ELSE_T){
                        *currentToken = scan(scannerParams);
                        parse_statement_nt_set(scannerParams, currentToken, reporter);
                    }

                    if((*currentToken)->type == END_T){
                        *currentToken = scan(scannerParams);
                        if((*currentToken)->type == IF_T){
                            std::cout<<"Successfully parsed IF_STATEMENT_NT \n";
                            *currentToken = scan(scannerParams);
                            return true;
                        }
                        else{
                            reporter->reportError("If statement must end with 'end if'");
                            return false;
                        }
                    }
                    else{
                        reporter->reportError("If statement must have an 'end if");
                        return false;
                    }
                }
                else{
                    reporter->reportError("If condition must include 'then'");
                    return false;
                }
            }
            else{
                reporter->reportError("If condition must be followed by a closing parenthesis");
                return false;
            }
        }
        else{
            reporter->reportError("If statement must have a set of parenthesis");
            return false;
        }
    }
    else{
        reporter->reportError("If statement must begin with 'if'");
        return false;
    }
}

bool parse_name_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing NAME_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed NAME_NT \n";
                return true;
            }
            else{
                reporter->reportError("Expression must be followed by a closing bracket \n");
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed NAME_NT \n";
            return true;
        }
    }
    else{
        reporter->reportError("Name must start with an identifier");
        return false;
    }
}

bool parse_argument_list_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing ARGUMENT_LIST_NT \n";
    parse_expression_nt(scannerParams, currentToken, reporter);
    if((*currentToken)->type == COMMA_T){
        *currentToken = scan(scannerParams);
        parse_argument_list_nt(scannerParams, currentToken, reporter);
    }
    std::cout<<"Successfully parsed ARGUMENT_LIST_NT \n";
    return true;
}

bool parse_procedure_call_or_name_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROCEDURE_CALL_OR_NAME_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            parse_argument_list_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == CLOSE_PARENTHESIS_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
                return true;
            }
            else{
                reporter->reportError("Argument list must be followed by a closing parenthesis");
                return false;
            }
        }
        else if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
                return true;
            }
            else{
                reporter->reportError("Expression must be followed by a closing bracket");
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed PROCEDURE_CALL_OR_NAME_NT";
            return true;
        }
    }
    else{
        reporter->reportError("Procedure call or name must include an identifier");
        return false;
    }
}

bool parse_factor_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing FACTOR_NT \n";
    if((*currentToken)->type == OPEN_PARENTHESIS_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken, reporter);
        if((*currentToken)->type == CLOSE_PARENTHESIS_T){
            *currentToken = scan(scannerParams);
            std::cout<<"Successfully parsed FACTOR_NT \n";
            return true;
        }
        else{
            reporter->reportError("Expression must be followed by a closing parenthesis");
            return false;
        }
    }
    else if((*currentToken)->type == IDENTIFIER_T){
        parse_procedure_call_or_name_nt(scannerParams, currentToken, reporter);
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
            parse_name_nt(scannerParams, currentToken, reporter);
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
        reporter->reportError("Couldn't match factor to any possible derivations \n");
        return false;
    }
}

bool parse_term_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing TERM_NT \n";
    parse_factor_nt(scannerParams, currentToken, reporter);
    if((*currentToken)->type == MULTIPLY_OP_T){
        *currentToken = scan(scannerParams);
        parse_factor_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
    else if((*currentToken)->type == DIVIDE_OP_T){
        *currentToken = scan(scannerParams);
        parse_factor_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
    else{
        std::cout<<"Successfully parsed TERM_NT";
        return true;
    }
}

bool parse_relation_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing RELATION_NT \n";
    parse_term_nt(scannerParams, currentToken, reporter);
    if((*currentToken)->type == LESS_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == GREATER_EQUAL_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == LESS_EQUAL_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == GREATER_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == EQUALITY_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else if((*currentToken)->type == INEQUALITY_OP_T){
        *currentToken = scan(scannerParams);
        parse_term_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;
    }
    else{
        std::cout<<"Successfully parsed RELATION_NT \n";
        return true;        
    }
}

bool parse_arith_op_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing ARITH_OP_NT \n";
    parse_relation_nt(scannerParams, currentToken, reporter);
    if((*currentToken)->type == PLUS_OP_T){
        *currentToken = scan(scannerParams);
        parse_relation_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true;
    }
    else if((*currentToken)->type == MINUS_OP_T){
        *currentToken = scan(scannerParams);
        parse_relation_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true;
    }
    else{
        std::cout<<"Successfully parsed ARITH_OP_NT";
        return true; 
    }
}

bool parse_expression_recurse_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing EXPRESSION_RECURSE_NT \n";
    if((*currentToken)->type == AND_OP_T){
        *currentToken = scan(scannerParams);
        parse_arith_op_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed EXPRESSION_RECURSE_NT \n";
        return true;
    }
    else if((*currentToken)->type == OR_OP_T){
        *currentToken = scan(scannerParams);
        parse_arith_op_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed EXPRESSION_RECURSE_NT \n";
        return true;
    }
    else{
        reporter->reportError("Expression should include & or |");
        return false;
    }
}

bool parse_expression_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing EXPRESSION_NT \n";
    if((*currentToken)->type == NOT_T){
        parse_arith_op_nt(scannerParams, currentToken, reporter);
        if((*currentToken)->type == AND_OP_T || (*currentToken)->type == OR_OP_T){
            parse_expression_recurse_nt(scannerParams, currentToken, reporter);
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
        else{
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
    }
    else{
        parse_arith_op_nt(scannerParams, currentToken, reporter);
        if((*currentToken)->type == AND_OP_T || (*currentToken)->type == OR_OP_T){
            parse_expression_recurse_nt(scannerParams, currentToken, reporter);
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
        else{
            std::cout<<"Successfully parsed EXPRESSION_NT \n";
            return true;
        }
    }
}

bool parse_destination_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing DESTINATION_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        *currentToken = scan(scannerParams);
        if((*currentToken)->type == OPEN_BRACKET_T){
            *currentToken = scan(scannerParams);
            parse_expression_nt(scannerParams, currentToken, reporter);
            if((*currentToken)->type == CLOSE_BRACKET_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed DESTINATION_NT \n";
                return true;
            }
            else{
                reporter->reportError("Expression must be followed by a closing bracket");
                return false;
            }
        }
        else{
            std::cout<<"Successfully parsed DESTINATION_NT \n";
            return true;
        }
    }
    else{
        reporter->reportError("Destination must start with an identifier");
        return false;
    }
}

bool parse_assignment_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing ASSIGNMENT_STATEMENT_NT \n";
    parse_destination_nt(scannerParams, currentToken, reporter);
    if((*currentToken)->type == ASSIGNMENT_OP_T){
        *currentToken = scan(scannerParams);
        parse_expression_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed ASSIGNMENT_STATEMENT_NT \n";
        return true;
    }
    else{
        reporter->reportError("Assignment statement must use an assignment operator");
        return false;
    }
}

bool parse_statement_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing STATEMENT_NT \n";
    if((*currentToken)->type == IDENTIFIER_T){
        parse_assignment_statement_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == IF_T){
        parse_if_statement_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == FOR_T){
        parse_for_statement_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else if((*currentToken)->type == RETURN_T){
        parse_return_statement_nt(scannerParams, currentToken, reporter);
        std::cout<<"Successfully parsed STATEMENT_NT \n";
        return true;
    }
    else{
        reporter->reportError("Statement must be an assignment statement, an if statement, a for statement, or a return statement");
        return false;
    }
}

bool parse_statement_nt_set(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
     std::cout<<"Parsing STATEMENT_NT_SET \n";
    bool endFound = false;
    while(!endFound){
        parse_statement_nt(scannerParams,currentToken, reporter);
        if((*currentToken)->type == SEMICOLON_T){
            std::cout<<"Advancing to next statement \n";
            *currentToken = scan(scannerParams);
        }
        else if((*currentToken)->type == END_T){
            endFound = true;
        }
        else{
            reporter->reportError("Statement can only be followed by another statement or END");
            return false;
        }
    }

    std::cout<<"Successfully parsed STATEMENT_NT_SET \n";
    return true;
}

bool parse_declaration_nt_set(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter);

bool parse_procedure_body_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing PROCEDURE_BODY_NT \n";
    parse_declaration_nt_set(scannerParams, currentToken, reporter);
    if((*currentToken)->type == BEGIN_T){
        *currentToken = scan(scannerParams);
        parse_statement_nt_set(scannerParams, currentToken, reporter);
        if((*currentToken)->type == END_T){
            *currentToken = scan(scannerParams);
            if((*currentToken)->type == PROCEDURE_T){
                *currentToken = scan(scannerParams);
                std::cout<<"Successfully parsed PROCEDURE_BODY_NT \n";
                return true;
            }
            else{
                reporter->reportError("Procedure ending must include 'procedure'");
                return false;
            }
        }
        else{
            reporter->reportError("Statement set must be followed by 'end'");
            return false;
        }
    }
    else{
        reporter->reportError("Declaration set must be followed by 'begin'");
        return false;
    }
}

bool parse_bound_nt(ScannerParams* scannerParams, Token** currentToken, ErrorReporter* reporter){
    std::cout<<"Parsing BOUND_NT \n";
    if((*currentToken)->type == NUMBER_T){
        *currentToken = scan(scannerParams);
        std::cout<<"Successfully parsed BOUNT_NT \n";
        return true;
    }
    else{
        reporter->reportError("Bound must be a number");
        return false;
    }

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
            return false;
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
