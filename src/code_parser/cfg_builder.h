#include "bb.h"

class CFGBuilder {
private:
    int blockCounter = 0;
    std::vector<BasicBlock> blocks;

    int createNewBlock() {
        blocks.push_back({blockCounter, {}, {}});
        return blockCounter++;
    }

    void processNode(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        switch (node->type) {
            case ASTNode::ASSIGNMENT:
                handleAssignment(node, currentBlock);
                break;
            case ASTNode::READ:
                blocks[currentBlock].instructions.push_back("READ " + node->value);
                break;
            case ASTNode::WRITE:
                blocks[currentBlock].instructions.push_back("WRITE " + evaluateExpression(node->children[0]));
                break;
            case ASTNode::EXPRESSION:
                blocks[currentBlock].instructions.push_back(evaluateExpression(node));
                break;
            case ASTNode::CONDITION:
                handleCondition(node, currentBlock);
                break;
            case ASTNode::IF:
                handleIf(node, currentBlock);
                break;
            case ASTNode::WHILE:
                handleWhile(node, currentBlock);
                break;
            case ASTNode::REPEAT:
                handleRepeat(node, currentBlock);
                break;
            default:
                break;
        }
    }

    void handleAssignment(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        // Dziecko [0] to zmienna, dziecko [1] to wartość do przypisania
        std::string target = node->children[0]->value;
        std::string value = evaluateExpression(node->children[1]);
        blocks[currentBlock].instructions.push_back(target + " = " + value);
    }

    std::string evaluateExpression(const std::shared_ptr<ASTNode>& node) {
        if (node->type == ASTNode::EXPRESSION) {
            std::string left = evaluateExpression(node->children[0]);
            std::string right = evaluateExpression(node->children[1]);
            return "(" + left + " " + node->value + " " + right + ")";
        } else if (node->type == ASTNode::CONDITION) {
            std::string left = evaluateExpression(node->children[0]);
            std::string right = evaluateExpression(node->children[1]);
            return "(" + left + " " + node->value + " " + right + ")";
        } else if (node->type == ASTNode::VARIABLE || node->type == ASTNode::CONSTANT) {
            return node->value;
        } else if (node->type == ASTNode::ARRAY_ACCESS) {
            std::string arrayName = node->children[0]->value;
            std::string index = evaluateExpression(node->children[1]);
            return arrayName + "[" + index + "]";
        }
        return "";
    }

    void handleCondition(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        std::string condition = evaluateExpression(node);
        blocks[currentBlock].instructions.push_back("CONDITION " + condition);
    }

    void handleIf(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        int trueBlock = createNewBlock();
        int falseBlock = createNewBlock();
        int exitBlock = createNewBlock();

        blocks[currentBlock].instructions.push_back("IF " + evaluateExpression(node->children[0]) + " GOTO " + std::to_string(trueBlock));
        blocks[currentBlock].successors.push_back(trueBlock);
        blocks[currentBlock].successors.push_back(falseBlock);

        // Process the true branch
        processNode(node->children[1], trueBlock);
        blocks[trueBlock].successors.push_back(exitBlock);

        // Process the false branch (if exists)
        if (node->children.size() > 2) {
            processNode(node->children[2], falseBlock);
        }
        blocks[falseBlock].successors.push_back(exitBlock);
    }

    void handleWhile(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        int conditionBlock = createNewBlock();
        int bodyBlock = createNewBlock();
        int exitBlock = createNewBlock();

        blocks[currentBlock].successors.push_back(conditionBlock);
        processNode(node->children[0], conditionBlock); // Warunek
        blocks[conditionBlock].instructions.push_back("IF " + evaluateExpression(node->children[0]) + " GOTO " + std::to_string(bodyBlock));
        blocks[conditionBlock].successors.push_back(bodyBlock);
        blocks[conditionBlock].successors.push_back(exitBlock);

        processNode(node->children[1], bodyBlock); // Ciało pętli
        blocks[bodyBlock].successors.push_back(conditionBlock);
    }

    void handleRepeat(const std::shared_ptr<ASTNode>& node, int currentBlock) {
        int bodyBlock = createNewBlock();
        int exitBlock = createNewBlock();

        blocks[currentBlock].successors.push_back(bodyBlock);
        processNode(node->children[0], bodyBlock); // Ciało pętli
        blocks[bodyBlock].instructions.push_back("UNTIL " + evaluateExpression(node->children[1]) + " GOTO " + std::to_string(exitBlock));
        blocks[bodyBlock].successors.push_back(bodyBlock); // Powrót do początku
        blocks[bodyBlock].successors.push_back(exitBlock);
    }

public:
    std::vector<BasicBlock> buildCFG(const std::shared_ptr<ASTNode>& root) {
        int entryBlock = createNewBlock();
        processNode(root, entryBlock);
        return blocks;
    }
};