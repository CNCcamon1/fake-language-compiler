#ifndef COMMENT_STATUS_TYPE
#define COMMENT_STATUS_TYPE

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
            else if(c == '\n'){
                beginningComment = false;
                endingComment = false;
                end_line();
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



