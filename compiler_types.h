#ifndef COMPILER_TYPES
#define COMPILER_TYPES

enum TokenType{

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

#endif



