#include "parse_tree_node.h"

#ifndef PARSE_TREE_TYPE
#define PARSE_TREE_TYPE

class ParseTree{
    public:
        ParseTree(ParseTreeNode* rootNodeInput){
            rootNode = rootNodeInput;
        };
        ParseTreeNode* rootNode;
};

#endif