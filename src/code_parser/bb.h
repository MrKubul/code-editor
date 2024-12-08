#include "ast.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

struct ASTNode {
    enum NodeType { PROCEDURE, IF, WHILE, REPEAT, ASSIGNMENT, READ, WRITE, CONDITION, EXPRESSION } type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children; // Dzieci dla zagnieżdżeń
};

struct BasicBlock {
    int id;
    std::vector<AstNode> instructions; // Instrukcje w bloku
    std::vector<int> successors;           // ID bloków docelowych
};