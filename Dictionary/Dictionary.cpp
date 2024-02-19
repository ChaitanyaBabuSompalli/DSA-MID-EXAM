#include <iostream>
#include <string>

struct TreeNode {
    std::string word;
    std::string definition;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& w, const std::string& def) : word(w), definition(def), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    TreeNode* root;
    int size; // Size of the BST
    //Changes

    // Helper function to insert a word and its definition into the BST
    TreeNode* insertHelper(TreeNode* node, const std::string& word, const std::string& definition) {
        if (node == nullptr) {
            size++;
            return new TreeNode(word, definition);
        }

        if (word < node->word) {
            node->left = insertHelper(node->left, word, definition);
        }
        else if (word > node->word) {
            node->right = insertHelper(node->right, word, definition);
        }
        else {
            // Word already exists, update definition
            node->definition = definition;
        }

        return node;
    }

    // Helper function to search for a word in the BST
    TreeNode* searchHelper(TreeNode* node, const std::string& word) {
        if (node == nullptr || node->word == word) {
            return node;
        }

        if (word < node->word) {
            return searchHelper(node->left, word);
        }
        else {
            return searchHelper(node->right, word);
        }
    }

    // Helper function to print the BST in inorder traversal
    void printInOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        std::cout << node->word << ": " << node->definition << std::endl;
        printInOrder(node->right);
    }

public:
    Dictionary() : root(nullptr), size(0) {}

    // Method to insert a word and its definition into the dictionary
    void insert(const std::string& word, const std::string& definition) {
        root = insertHelper(root, word, definition);
    }

    // Method to search for a word in the dictionary
    std::string search(const std::string& word) {
        TreeNode* node = searchHelper(root, word);
        if (node != nullptr) {
            return node->definition;
        }
        else {
            return "Word not found in the dictionary.";
        }
    }

    // Method to get the size of the dictionary
    int getSize() {
        return size;
    }

    // Method to print the dictionary
    void printDictionary() {
        if (root == nullptr) {
            std::cout << "Dictionary is empty." << std::endl;
            return;
        }
        std::cout << "Dictionary:" << std::endl;
        printInOrder(root);
    }
};

int main() {
    Dictionary dictionary;

    int numWords;
    std::cout << "Enter the number of words to insert: ";
    std::cin >> numWords;

    for (int i = 0; i < numWords; ++i) {
        std::string word, definition;
        std::cout << "Enter word " << i + 1 << ": ";
        std::cin >> word;
        std::cout << "Enter definition for " << word << ": ";
        std::cin.ignore();
        std::getline(std::cin, definition);
        dictionary.insert(word, definition);
    }

    // Print the dictionary
    dictionary.printDictionary();
    std::cout << "Size of the dictionary: " << dictionary.getSize() << std::endl;

    // Search for a word
    std::string searchWord;
    std::cout << "Enter a word to search: ";
    std::cin >> searchWord;
    std::cout << "Definition: " << dictionary.search(searchWord) << std::endl;

    return 0;
}
