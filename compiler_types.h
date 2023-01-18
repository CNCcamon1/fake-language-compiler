#ifndef COMPILER_TYPES
#define COMPILER_TYPES

enum TokenType{
    PROGRAM_NT,
    PROGRAM_HEADER_NT,
    PROGRAM_BODY_NT,
    IDENTIFIER_NT,
    PROGRAM_T,
    IS_T,
    DECLARATION_NT,
    STATEMENT_NT,
    SEMICOLON_T,
    BEGIN_T,
    END_T,
    GLOBAL_T,
    PROCEDURE_DECLARATION_NT,
    VARIABLE_DECLARATION_NT,
    PROCEDURE_HEADER_NT,
    PROCEDURE_BODY_NT,
    PROCEDURE_T,
    COLON_T,
    TYPE_MARK_NT,
    OPEN_PARENTHESIS_T,
    CLOSE_PARENTHESIS_T,
    PARAMETER_LIST_NT,
    PARAMETER_NT,
    COMMA_T,
    VARIABLE_DECLARATION_NT,
    VARIABLE_T,
    OPEN_BRACKET_T,
    CLOSE_BRACKET_T,
    BOUND_NT,
    INTEGER_T,
    FLOAT_T,
    STRING_T,
    BOOL_T,
    NUMBER_NT,
    ASSIGNMENT_STATEMENT_NT,
    IF_STATEMENT_NT,
    LOOP_STATEMENT_NT,
    RETURN_STATEMENT_NT,
    PROCEDURE_CALL_NT,
    ARGUMENT_LIST_NT,
    DESTINATION_NT,
    EXPRESSION_NT,
    ASSIGNMENT_OP_T,
    IF_T,
    THEN_T,
    ELSE_T,
    FOR_T,
    RETURN_T,
    AND_OP_T,
    OR_OP_T,
    NOT_OP_T,
    ARITH_OP_NT,
    RELATION_NT,
    PLUS_OP_T,
    MINUS_OP_T,
    LESSTHAN_OP_T,
    GREATER_EQUAL_OP_T,
    LESS_EQUAL_OP_T,
    GREATERTHAN_OP_T,
    EQUALITY_OP_T,
    INEQUALITY_OP_T,
    TERM_NT,
    MULTIPLY_OP_T,
    FACTOR_NT,
    DIVIDE_OP_T,
    NAME_NT,
    STRING_NT,
    TRUE_T,
    FALSE_T,
};

class Token{
    public:
        enum TokenType type;
        bool is_terminal;
        Token(TokenType type, bool is_terminal){
            type = type;
            is_terminal = is_terminal;
        }
};

class TokenStream{
    public:
        Token* head;
        TokenStream* tail;
        TokenStream(Token* head){
            head = head;
            tail = nullptr;
        }

        void link_tail(TokenStream* tail){
            tail = tail;
        }
};

class TokenTree{
    public:
        Token* rootNode;
        TokenTree* leftBranch;
        TokenTree* rightBranch;
};

class CommentStatus{
    public: 
        CommentStatus(){
            commentCount = 0;
            beginningComment = false;
            endingComment = false;
            multiLineComment = false;
        }
        bool in_comment(){
            if(commentCount > 0){
                return true;
            }
            else{
                return false;
            }
        }
        void update_comment_status(char c){
            if(c == '/'){
                if(beginningComment){
                    if(multiLineComment == false){
                        commentCount += 1;
                    }
                }
                else if(endingComment){
                    commentCount -= 1;
                }
                else{
                    beginningComment = true;
                }
            }
            else if(c == '*'){
                if(beginningComment){
                    commentCount += 1;
                    multiLineComment = true;
                }
                else{
                    endingComment = true;
                }
            }
            else{
                beginningComment = false;
                endingComment = false;
            }

            if(commentCount == 0){
                multiLineComment = false;
            }
        }
        void end_line(){
            if(multiLineComment == false){
                commentCount = 0;
            }
        }
    private:
        int commentCount;
        bool beginningComment;
        bool endingComment;
        bool multiLineComment;
};

#endif



