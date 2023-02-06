#include <vector>
#include <iostream>
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

        void delete_children(){
            for(int i=0; i<children.size(); i++){
                delete children[i];
            }
            children = {};
        }

        void print(int level=0){
            for(int i=0; i<level; i++){
                std::cout<<"|";
                std::cout<<"\t";
            }
            std::cout<<"Node "<<TokenTools::token_type_to_string(type);
            if(data != ""){
                std::cout<<" with data " << data;
            }
            std::cout<<"\n";
            for(int i=0; i<children.size(); i++){
                children[i]->print(level+1);
            }
        }

    private:
        
        std::vector<ParseTreeNode*> children;

};

#endif