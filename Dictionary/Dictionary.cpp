#include <iostream>
#include <string>

// TreeNode structure to represent each node in the binary search tree (BST)
struct TreeNode {
    std::string word;
    std::string definition;
    TreeNode* left;   // Pointer to the left child node
    TreeNode* right;  // Pointer to the right child node

    // Constructor to initialize TreeNode with word and definition
    TreeNode(const std::string& w, const std::string& def) : word(w), definition(def), left(nullptr), right(nullptr) {}
};

// Dictionary class representing the dictionary application
class Dictionary {
private:
    TreeNode* root; // Pointer to the root node of the BST
    int size;       // Size of the BST

    // Helper function to recursively insert a word and its definition into the BST
    TreeNode* insertHelper(TreeNode* node, const std::string& word, const std::string& definition) {
        // If the current node is null, create a new node with the word and definition
        if (node == nullptr) {
            size++;
            return new TreeNode(word, definition);
        }

        // If the word is less than the current node's word, insert it into the left subtree
        if (word < node->word) {
            node->left = insertHelper(node->left, word, definition);
        }
        // If the word is greater than the current node's word, insert it into the right subtree
        else if (word > node->word) {
            node->right = insertHelper(node->right, word, definition);
        }
        // If the word already exists, update its definition
        else {
            node->definition = definition;
        }

        return node;
    }

    // Helper function to recursively search for a word in the BST
    TreeNode* searchHelper(TreeNode* node, const std::string& word) {
        // If the current node is null or the word is found, return the node
        if (node == nullptr || node->word == word) {
            return node;
        }

        // If the word is less than the current node's word, search in the left subtree
        if (word < node->word) {
            return searchHelper(node->left, word);
        }
        // If the word is greater than the current node's word, search in the right subtree
        else {
            return searchHelper(node->right, word);
        }
    }

    // Helper function to recursively print the BST in inorder traversal
    void printInOrder(TreeNode* node) {
        // If the current node is null, return
        if (node == nullptr) {
            return;
        }
        // Print the left subtree
        printInOrder(node->left);
        // Print the current node's word and definition
        std::cout << node->word << ": " << node->definition << std::endl;
        // Print the right subtree
        printInOrder(node->right);
    }

public:
    // Constructor to initialize the dictionary with an empty BST
    Dictionary() : root(nullptr), size(0) {}

    // Method to insert a word and its definition into the dictionary
    void insert(const std::string& word, const std::string& definition) {
        root = insertHelper(root, word, definition);
    }

    // Method to search for a word in the dictionary
    std::string search(const std::string& word) {
        TreeNode* node = searchHelper(root, word);
        // If the word is found, return its definition; otherwise, return a message indicating it was not found
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

    // Method to print the dictionary in alphabetical order
    void printDictionary() {
        // If the root is null, the dictionary is empty
        if (root == nullptr) {
            std::cout << "Dictionary is empty." << std::endl;
            return;
        }
        // Otherwise, print the dictionary in inorder traversal
        std::cout << "Dictionary:" << std::endl;
        printInOrder(root);
    }
};

// Main function to execute the dictionary application
int main() {
    // Create an instance of the Dictionary class
    Dictionary dictionary;

    // Prompt the user to enter the number of words to insert
    int numWords;
    std::cout << "Enter the number of words to insert: ";
    std::cin >> numWords;

    // Loop to insert words and definitions into the dictionary
    for (int i = 0; i < numWords; ++i) {
        std::string word, definition;
        std::cout << "Enter word " << i + 1 << ": ";
        std::cin >> word;
        std::cout << "Enter definition for " << word << ": ";
        // Clear the input buffer and get the definition (including spaces)
        std::cin.ignore();
        std::getline(std::cin, definition);
        // Insert the word and definition into the dictionary
        dictionary.insert(word, definition);
    }

    // Print the dictionary
    dictionary.printDictionary();
    // Print the size of the dictionary
    std::cout << "Size of the dictionary: " << dictionary.getSize() << std::endl;

    // Prompt the user to enter a word to search
    std::string searchWord;
    std::cout << "Enter a word to search: ";
    std::cin >> searchWord;
    // Search for the word in the dictionary and print its definition
    std::cout << "Definition: " << dictionary.search(searchWord) << std::endl;

    return 0;
}
