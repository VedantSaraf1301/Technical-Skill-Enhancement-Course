/*
Question 1: Global Autocomplete System (Trie)

Build a Trie-based system that stores up to 1 million strings.
Implement a function that returns the top 5 most frequent suggestions
for a given prefix.

Complexity Requirement:
Prefix search must be O(L), where L is the length of the prefix.
*/
#include <bits/stdc++.h>
using namespace std;

class AutocompleteSystem {

    class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        vector<string> topFiveWords;
    };

    TrieNode* rootNode;
    unordered_map<string, int> wordFrequency;

public:

    AutocompleteSystem() {
        rootNode = new TrieNode();
    }

    void insertWord(string word) {

        wordFrequency[word]++;

        TrieNode* currentNode = rootNode;

        for(char character : word) {

            if(currentNode->children.find(character) == currentNode->children.end()) {
                currentNode->children[character] = new TrieNode();
            }

            currentNode = currentNode->children[character];

            updateTopFive(currentNode, word);
        }
    }

private:

    void updateTopFive(TrieNode* node, string word) {

        // check if word exists
        if(find(node->topFiveWords.begin(), node->topFiveWords.end(), word)
            == node->topFiveWords.end()) {

            node->topFiveWords.push_back(word);
        }

        // sort
        sort(node->topFiveWords.begin(), node->topFiveWords.end(),
        [&](string &firstWord, string &secondWord) {

            int frequencyDifference =
                wordFrequency[secondWord] - wordFrequency[firstWord];

            if(frequencyDifference == 0)
                return firstWord < secondWord;

            return frequencyDifference > 0;
        });

        // keep only top 5
        if(node->topFiveWords.size() > 5) {
            node->topFiveWords.pop_back();
        }
    }

public:

    vector<string> searchPrefix(string prefix) {

        TrieNode* currentNode = rootNode;

        for(char character : prefix) {

            if(currentNode->children.find(character) ==
               currentNode->children.end()) {

                return {};
            }

            currentNode = currentNode->children[character];
        }

        return currentNode->topFiveWords;
    }
};

//Example Of Usage
int main() {

    AutocompleteSystem system;

    system.insertWord("apple");
    system.insertWord("app");
    system.insertWord("application");
    system.insertWord("apply");
    system.insertWord("apex");
    system.insertWord("app");

    vector<string> result = system.searchPrefix("app");

    for(string s : result)
        cout << s << endl;
}