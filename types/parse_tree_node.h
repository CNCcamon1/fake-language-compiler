#include <vector>
#include "token.h"


#ifndef PARSE_TREE_NODE_TYPE
#define PARSE_TREE_NODE_TYPE

class ParseTreeNode{
    public:
        ParseTreeNode(TokenType typeInput){
            type = typeInput;
        }
        TokenType type;
        std::string data;

        void add_child(ParseTreeNode* node){
            children.push_back(node);
        }

        int get_children_count(){
            return children.size();
        }

        ParseTreeNode* get_child(int i){
            return children[i];
        }

    private:
        
        std::vector<ParseTreeNode*> children;

};

#endif