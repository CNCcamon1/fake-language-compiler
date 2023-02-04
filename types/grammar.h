#include <vector>

class Grammar{
    public:
        std::vector<std::vector<GrammarOption*>>* get_possible_children_for_type(TokenType type){
            return &grammarOptionsTable[type-43];
        }

        //Returns whether or not the current token is a valid first token for the given type
        bool child_choice_valid(TokenType type, Token* currentToken){
            if(is_terminal_or_literal(type)){
                return type == currentToken->type;
            }
            else{
                if(type == PROCEDURE_CALL_NT && currentToken->tokenMark != PROCEDURE_M){
                    return false;
                }
                bool firstValid = false;
                std::vector<TokenType>* firstPossibilities = &firstTokenTable[type-43];
                for(int i=0; i<firstPossibilities->size(); i++){
                    if(firstPossibilities->at(i) == currentToken->type){
                        firstValid = true;
                    }
                }

                return firstValid;
            }

        }

        bool derivation_choice_valid(std::vector<GrammarOption*>* derivation, Token* currentToken){
            bool checkedAll = false;
            int i=0;
            while(checkedAll == false){
                bool valid = child_choice_valid(derivation->at(i)->tokenType, currentToken);
                if(valid == true){
                    return true;
                }
                else if(derivation->at(i)->optionType == OPTIONAL_C){
                    i++;
                }
                else{
                    return false;
                }
            }
        }

        bool is_terminal(TokenType currentType){
            return currentType < 43;
        }

        bool is_terminal_or_literal(TokenType currentType){
            return currentType < 43 || currentType == IDENTIFIER_NT || currentType == STRING_LITERAL_NT || currentType == NUMBER_NT;
        }

        void build_grammar(){
            build_first_token_table();
        }
    
    private:
        std::vector<std::vector<std::vector<GrammarOption*>>> grammarOptionsTable {
            {{new GrammarOption(PROGRAM_HEADER_NT), new GrammarOption(PROGRAM_BODY_NT), new GrammarOption(PERIOD_T)}}, //PROGRAM_NT
            {{new GrammarOption(PROGRAM_T), new GrammarOption(IDENTIFIER_NT), new GrammarOption(IS_T)}}, //PROGRAM_HEADER_NT
            {{new GrammarOption(DECLARATION_OBJ_NT, ARRAY_C), new GrammarOption(BEGIN_T), new GrammarOption(STATEMENT_OBJ_NT, ARRAY_C), new GrammarOption(END_T), new GrammarOption(PROGRAM_T)}}, //PROGRAM_BODY_NT
            {{}}, //IDENTIFIER_NT
            {{new GrammarOption(GLOBAL_T, OPTIONAL_C), new GrammarOption(PROCEDURE_DECLARATION_NT)}, {new GrammarOption(GLOBAL_T, OPTIONAL_C), new GrammarOption(VARIABLE_DECLARATION_NT)}}, //DECLARATION_NT
            {{new GrammarOption(ASSIGNMENT_STATEMENT_NT)}, {new GrammarOption(IF_STATEMENT_NT)}, {new GrammarOption(LOOP_STATEMENT_NT)}, {new GrammarOption(RETURN_STATEMENT_NT)}}, //STATEMENT_NT
            {{new GrammarOption(PROCEDURE_HEADER_NT), new GrammarOption(PROCEDURE_BODY_NT)}}, //PROCEDURE_DECLARATION_NT
            {{new GrammarOption(VARIABLE_T), new GrammarOption(IDENTIFIER_NT), new GrammarOption(COLON_T), new GrammarOption(TYPE_MARK_NT), new GrammarOption(BOUND_OBJ_NT, OPTIONAL_C)}}, //VARIABLE_DECLARATION_NT
            {{new GrammarOption(PROCEDURE_T), new GrammarOption(IDENTIFIER_NT), new GrammarOption(COLON_T), new GrammarOption(TYPE_MARK_NT), new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(PARAMETER_LIST_NT, OPTIONAL_C), new GrammarOption(CLOSE_PARENTHESIS_T)}}, //PROCEDURE_HEADER_NT
            {{new GrammarOption(DECLARATION_OBJ_NT, ARRAY_C), new GrammarOption(BEGIN_T), new GrammarOption(STATEMENT_OBJ_NT, ARRAY_C), new GrammarOption(END_T), new GrammarOption(PROCEDURE_T)}}, //PROCEDURE_BODY_NT
            {{new GrammarOption(INTEGER_T)}, {new GrammarOption(FLOAT_T)}, {new GrammarOption(STRING_T)}, {new GrammarOption(BOOL_T)}}, //TYPE_MARK_NT
            {{new GrammarOption(PARAMETER_NT), new GrammarOption(PARAMETER_LIST_OBJ_NT, OPTIONAL_C)}}, //PARAMETER_LIST_NT
            {{new GrammarOption(VARIABLE_DECLARATION_NT)}}, //PARAMETER_NT
            {{new GrammarOption(NUMBER_NT)}}, //BOUND_NT
            {{}}, //NUMBER_NT
            {{new GrammarOption(DESTINATION_NT), new GrammarOption(ASSIGNMENT_OP_T), new GrammarOption(EXPRESSION_NT)}}, //ASSIGNMENT_STATEMENT_NT
            {{new GrammarOption(IF_T), new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(EXPRESSION_NT), new GrammarOption(CLOSE_PARENTHESIS_T), new GrammarOption(THEN_T), new GrammarOption(STATEMENT_OBJ_NT, ARRAY_C), new GrammarOption(ELSE_BLOCK_NT, OPTIONAL_C), new GrammarOption(END_T), new GrammarOption(IF_T)}}, //IF_STATEMENT_NT
            {{new GrammarOption(FOR_T), new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(ASSIGNMENT_STATEMENT_NT), new GrammarOption(SEMICOLON_T), new GrammarOption(EXPRESSION_NT), new GrammarOption(CLOSE_PARENTHESIS_T), new GrammarOption(STATEMENT_OBJ_NT, ARRAY_C), new GrammarOption(END_T), new GrammarOption(FOR_T)}}, //LOOP_STATEMENT_NT
            {{new GrammarOption(RETURN_T), new GrammarOption(EXPRESSION_NT)}}, //RETURN_STATEMENT_NT
            {{new GrammarOption(IDENTIFIER_NT), new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(ARGUMENT_LIST_NT, OPTIONAL_C), new GrammarOption(CLOSE_PARENTHESIS_T)}}, //PROCEDURE_CALL_NT
            {{new GrammarOption(EXPRESSION_NT), new GrammarOption(ARGUMENT_LIST_OBJ_NT, OPTIONAL_C)}}, //ARGUMENT_LIST_NT
            {{new GrammarOption(IDENTIFIER_NT), new GrammarOption(EXPRESSION_BLOCK_OBJ_NT, OPTIONAL_C)}}, //DESTINATION_NT
            {{new GrammarOption(NOT_OP_T, OPTIONAL_C), new GrammarOption(ARITH_OP_NT), new GrammarOption(EXPRESSION_RECURSE_NT, OPTIONAL_C)}}, //EXPRESSION_NT
            {{new GrammarOption(RELATION_NT), new GrammarOption(ARITH_OP_RECURSE_NT, OPTIONAL_C)}}, //ARITH_OP_NT
            {{new GrammarOption(TERM_NT), new GrammarOption(RELATION_RECURSE_NT, OPTIONAL_C)}}, //RELATION_NT
            {{new GrammarOption(FACTOR_NT), new GrammarOption(TERM_RECURSE_NT, OPTIONAL_C)}}, //TERM_NT
            {{new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(EXPRESSION_NT), new GrammarOption(CLOSE_PARENTHESIS_T)}, {new GrammarOption(PROCEDURE_CALL_NT)}, {new GrammarOption(MINUS_OP_T, OPTIONAL_C), new GrammarOption(NAME_NT)}, {new GrammarOption(MINUS_OP_T, OPTIONAL_C), new GrammarOption(NUMBER_NT)}, {new GrammarOption(STRING_LITERAL_NT)}, {new GrammarOption(TRUE_T)}, {new GrammarOption(FALSE_T)}}, //FACTOR_NT
            {{new GrammarOption(IDENTIFIER_NT), new GrammarOption(EXPRESSION_BLOCK_OBJ_NT, OPTIONAL_C)}}, //NAME_NT
            {{}}, //STRING_NT
            {{new GrammarOption(DECLARATION_NT), new GrammarOption(SEMICOLON_T)}}, //DECLARATION_OBJ_NT
            {{new GrammarOption(STATEMENT_NT), new GrammarOption(SEMICOLON_T)}}, //STATEMENT_OBJ_NT
            {{new GrammarOption(AND_OP_T), new GrammarOption(ARITH_OP_NT)}, {new GrammarOption(OR_OP_T), new GrammarOption(ARITH_OP_NT)}}, //EXPRESSION_RECURSE_NT
            {{}}, //STRING_LITERAL_NT
            {{new GrammarOption(PLUS_OP_T), new GrammarOption(RELATION_NT)}, {new GrammarOption(MINUS_OP_T), new GrammarOption(RELATION_NT)}}, //ARITH_OP_RECURSE_NT
            {{new GrammarOption(LESSTHAN_OP_T), new GrammarOption(TERM_NT)}, {new GrammarOption(GREATER_EQUAL_OP_T), new GrammarOption(TERM_NT)}, {new GrammarOption(LESS_EQUAL_OP_T), new GrammarOption(TERM_NT)}, {new GrammarOption(GREATERTHAN_OP_T), new GrammarOption(TERM_NT)}, {new GrammarOption(EQUALITY_OP_T), new GrammarOption(TERM_NT)}, {new GrammarOption(INEQUALITY_OP_T), new GrammarOption(TERM_NT)}}, //RELATION_RECURSE_NT
            {{new GrammarOption(MULTIPLY_OP_T), new GrammarOption(FACTOR_NT)},{new GrammarOption(DIVIDE_OP_T), new GrammarOption(FACTOR_NT)}}, //TERM_RECURSE_NT
            {{new GrammarOption(OPEN_BRACKET_T), new GrammarOption(BOUND_NT), new GrammarOption(CLOSE_BRACKET_T)}}, //BOUND_OBJ_NT
            {{new GrammarOption(COMMA_T), new GrammarOption(PARAMETER_LIST_NT)}}, //PARAMETER_LIST_OBJ_NT
            {{new GrammarOption(COMMA_T), new GrammarOption(ARGUMENT_LIST_NT)}}, //ARGUMENT_LIST_OBJ_NT
            {{new GrammarOption(ELSE_T), new GrammarOption(STATEMENT_OBJ_NT, ARRAY_C)}}, //ELSE_BLOCK_NT
            {{new GrammarOption(OPEN_BRACKET_T), new GrammarOption(EXPRESSION_NT), new GrammarOption(CLOSE_BRACKET_T)}}, //EXPRESSION_BLOCK_OBJ_NT
        };

        std::vector<std::vector<TokenType>> firstTokenTable{

        };

        std::vector<TokenType> get_valid_first_tokens(TokenType nonterminalType){
            std::vector<TokenType> validFirstTokens;
            std::vector<std::vector<GrammarOption*>>* derivationOptionsForNonterminal = &grammarOptionsTable[nonterminalType-43];
            for(int i=0; i<derivationOptionsForNonterminal->size(); i++){
                //For each derivation option for this nonterminal
                std::vector<GrammarOption*>* derivationOption = &derivationOptionsForNonterminal->at(i);
                bool foundAll = false;
                int j = 0;
                while(foundAll == false){
                    GrammarOption* option = derivationOptionsForNonterminal->at(i).at(j);
                    if(is_terminal_or_literal(option->tokenType)){
                        validFirstTokens.push_back(option->tokenType);
                    }
                    else{
                        std::vector<TokenType> typeOptionsForNonterminal = get_valid_first_tokens(option->tokenType);
                        validFirstTokens.insert(validFirstTokens.end(), typeOptionsForNonterminal.begin(), typeOptionsForNonterminal.end());
                    }

                    if(option->optionType != OPTIONAL_C){
                        foundAll = true;
                    }
                    else{
                        j++;
                    }
                }

            }

            return validFirstTokens;
        }

        void build_first_token_table(){
            for(int i=0; i<grammarOptionsTable.size(); i++){
                //For each nonterminal type in the grammar
                TokenType type = static_cast<TokenType>(i+43);
                std::vector<TokenType> firstTokens;
                if(type == IDENTIFIER_NT || type == STRING_LITERAL_NT || type == NUMBER_NT || type == STRING_NT){
                    firstTokens = {};
                }
                else{
                    firstTokens = get_valid_first_tokens(static_cast<TokenType>(i+43));
                }
                std::cout<<"Valid first tokens for type " << TokenTools::token_type_to_string(type) <<": \n";
                for(int i=0; i<firstTokens.size(); i++){
                    std::cout<< TokenTools::token_type_to_string(firstTokens[i]) << ",";
                }
                std::cout<<"\n";
                firstTokenTable.push_back(firstTokens);
            }
        }
};
