#include <vector>

class Grammar{
    public:
        std::vector<std::vector<GrammarOption*>>* get_possible_children_for_type(TokenType type){
            return &grammarOptionsTable[type-43];
        }

        //Returns whether or not the current token is a valid first token for the given type
        bool child_choice_valid(TokenType type, Token* currentToken){
            if(is_terminal(type)){
                return type == currentToken->type;
            }
            else{
                bool firstValid = false;
                std::vector<TokenType>* firstPossibilities = &firstTokenTable[type];
                for(int i=0; i<firstPossibilities->size(); i++){
                    if(firstPossibilities->at(i) == currentToken->type){
                        firstValid = true;
                    }
                }

                return firstValid;
            }

        }

        bool is_terminal(TokenType currentType){
            return currentType < 43;
        }

        void build_grammar(){
            build_first_token_table();
        }
    
    private:
        std::vector<std::vector<std::vector<GrammarOption*>>> grammarOptionsTable {
            {{new GrammarOption(PROGRAM_HEADER_NT), new GrammarOption(PROGRAM_BODY_NT)}}, //PROGRAM_NT
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
            {{new GrammarOption(IDENTIFIER_NT), new GrammarOption(OPEN_PARENTHESIS_T), new GrammarOption(ARGUMENT_LIST_NT, OPTIONAL_C)}}, //PROCEDURE_CALL_NT
            {{new GrammarOption(EXPRESSION_NT), new GrammarOption(ARGUMENT_LIST_OBJ_NT)}}, //ARGUMENT_LIST_NT
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
                GrammarOption* first = derivationOptionsForNonterminal->at(i).at(0);
                if(is_terminal(first->tokenType) || first->tokenType == IDENTIFIER_NT || first->tokenType == NUMBER_NT || first->tokenType == STRING_LITERAL_NT){
                    validFirstTokens.push_back(first->tokenType);
                }
                else{
                    std::vector<TokenType> typeOptionsForNonterminal = get_valid_first_tokens(first->tokenType);
                    validFirstTokens.insert(validFirstTokens.end(), typeOptionsForNonterminal.begin(), typeOptionsForNonterminal.end());
                }
            }

            return validFirstTokens;
        }

        void build_first_token_table(){
            for(int i=0; i<grammarOptionsTable.size(); i++){
                //For each nonterminal type in the grammar
                std::vector<TokenType> firstTokens = get_valid_first_tokens(static_cast<TokenType>(i));
                firstTokenTable.push_back(firstTokens);
            }
        }
};
