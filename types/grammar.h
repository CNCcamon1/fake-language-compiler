#include <vector>

class Grammar{
    public:
        std::vector<GrammarOption*>* get_possible_children_for_type(TokenType type){
            return &grammarOptionsTable[type-43];
        }

        bool child_choice_valid(TokenType type, Token* currentToken, Token* lookaheadToken){
            bool firstValid = false;
            //bool followsValid = false;

            std::vector<TokenType>* firstPossibilities = &firstTokenTable[type];
            //std::vector<TokenType>* followsPossibilities = &followTokenTable[type];

            for(int i=0; i<firstPossibilities->size(); i++){
                if(firstPossibilities->at(i) == currentToken->type){
                    firstValid = true;
                }
            }

            return firstValid;
        }

        bool is_terminal(TokenType currentType);

        void build_grammar();
    
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
            {{new GrammarOption(PROCEDURE_T), new GrammarOption()}}, //PROCEDURE_HEADER_NT
        };

        std::vector<std::vector<TokenType>> firstTokenTable{

        };

        /*std::vector<std::vector<TokenType>> followTokenTable{

        }; */
};
