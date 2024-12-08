#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
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

    // Levenshtein distance computation function
    int levenshteinDistance(const std::string& a, const std::string& b) const {
        std::vector<std::vector<int>> dp(a.size() + 1, std::vector<int>(b.size() + 1));

        for (size_t i = 0; i <= a.size(); ++i) {
            for (size_t j = 0; j <= b.size(); ++j) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        return dp[a.size()][b.size()];
    }

    // Search for words within a given Levenshtein distance tolerance
    void searchWithTolerance(const std::string& word, int maxDistance, std::vector<std::string>& result) const {
        std::string currentWord;
        searchWithToleranceHelper(root.get(), word, maxDistance, 0, currentWord, result);
    }

private:
    // Helper function to recursively search the Trie
    void searchWithToleranceHelper(TrieNode* node, const std::string& target, int maxDistance, int depth,
                                   std::string& currentWord, std::vector<std::string>& result) const {
        if (node == nullptr) return;

        // If this is an end of a word, calculate Levenshtein distance
        if (node->isEndOfWord) {
            int distance = levenshteinDistance(currentWord, target);
            if (distance <= maxDistance) {
                result.push_back(currentWord);
            }
        }

        // Recursively check all children
        for (const auto& [ch, childNode] : node->children) {
            currentWord.push_back(ch);
            searchWithToleranceHelper(childNode.get(), target, maxDistance, depth + 1, currentWord, result);
            currentWord.pop_back(); // Backtrack
        }
    }
};