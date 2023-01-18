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



