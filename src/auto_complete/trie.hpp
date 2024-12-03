#include <iostream>
#include <unordered_map>
#include <string>
#include <memory> // For smart pointers

class TrieNode {
public:
    // Map to store children (character -> TrieNode*)
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;

public:
    Trie() {
        root = std::make_unique<TrieNode>();
    }

    // Insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* node = root.get();
        for (char ch : word) {
            if (!node->children.count(ch)) {
                node->children[ch] = std::make_unique<TrieNode>();
            }
            node = node->children[ch].get();
        }
        node->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(const std::string& word) const {
        TrieNode* node = root.get();
        for (char ch : word) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch].get();
        }
        return node->isEndOfWord;
    }

    // Check if any word in the Trie starts with a given prefix
    bool startsWith(const std::string& prefix) const {
        TrieNode* node = root.get();
        for (char ch : prefix) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch].get();
        }
        return true;
    }
};