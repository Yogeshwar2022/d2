#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

Node* buildHuffmanTree(const string& str) {
    map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    for (auto& it : freq) {
        minHeap.push(new Node(it.first, it.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

void printHuffmanCodes(Node* root, string code = "") {
    if (!root) return;

    if (root->data != '$') {
        cout << root->data << ": " << code << endl;
    }

    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    Node* root = buildHuffmanTree(input);

    cout << "Huffman Codes:\n";
    printHuffmanCodes(root);

    return 0;
}
