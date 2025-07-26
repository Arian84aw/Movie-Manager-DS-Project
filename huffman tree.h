#include "Headers.h"

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

    // Comparator for priority queue
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
};

class HuffmanTree {
public:
    unordered_map<char, int> calculateFrequencies(vector<string>& words) {
        unordered_map<char, int> frequency;
        for (auto& word : words) {
            //transform(word.begin(), word.end(), word.begin(), ::tolower);
            for (char ch : word) {
                frequency[ch]++;
            }
        }
        return frequency;
    }

    HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, greater<HuffmanNode*>> minHeap;

        for (const auto& pair : frequencies) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        while (minHeap.size() > 1) {
            HuffmanNode* left = minHeap.top();
            minHeap.pop();
            HuffmanNode* right = minHeap.top();
            minHeap.pop();

            HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
            merged->left = left;
            merged->right = right;
    
            minHeap.push(merged);
        }
    
        return minHeap.top();
    }

    void generateHuffmanCodes(HuffmanNode* node, const string& prefix, unordered_map<char, string>& huffmanCodes) {
        if (node == nullptr)
            return;
        if (node->character != '\0') {
            huffmanCodes[node->character] = prefix;
        }
    
        generateHuffmanCodes(node->left, prefix + "0", huffmanCodes);
        generateHuffmanCodes(node->right, prefix + "1", huffmanCodes);
    }
    string decodeHuffman(const bitset<256>& encodedBits, size_t length, HuffmanNode* huffmanTree) {
        string decodedOutput;
        HuffmanNode* currentNode = huffmanTree;
    
        for (size_t i = 0; i < length; ++i) {
            if (encodedBits[i]) {
                currentNode = currentNode->right;
            }
            else {
                currentNode = currentNode->left;
            }
            if (currentNode->character != '\0') {
                decodedOutput += currentNode->character;
                currentNode = huffmanTree;
            }
        }
    
        return decodedOutput;
    }
    
};
