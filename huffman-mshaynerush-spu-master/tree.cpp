/*
 Filename: huffmantree.h
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Shayne Rushton
 Date: 0/14/2021
 Course: Data Structures II
*/


#include "tree.h"

Tree::Tree(){}

Tree::~Tree(){}
using namespace std;

void Tree::Read(string &inFile, string outFile) { //read contents to a file saving the original and making default names for output files where needed. For decoding, create a copy with my own file type to decode.

    //creating file name stubs removing the extension so that it can be used for various purposes
    infileName = inFile.substr(0,inFile.find('.'));
    outFileName = outFile.substr(0, outFile.find('.'));
    defaultFileName = infileName;

    ifstream inFS(inFile);
    stringstream ss;
    char fileRead;

    while (inFS.get(fileRead)) {
        ss << fileRead;
    }
    //creates a copy of the original file for decoding

    if(outFile == "default") {
        outFile = inFile.substr(0, inFile.find('.'));
        outFile += ".decode";
        ofstream oFS(outFile);
        oFS << ss.str();
    } else {

    }
    Tree::MakeFrequencyMap(inFile);
}

void Tree::MakeFrequencyMap(string &inFile) { // read the file, count each character and store in a unordered map
    ifstream iFS(inFile);
    char ch;
    string str;
    while (iFS.get(ch)) {
        if(ch == '\n'){
            str = "CR";
        } else if(ch == '\r'){
            str = "LF";
        } else {
            str = ch;
        }
        freqTable[str]++;
    }
        Tree::MakeNodes(freqTable);
}
void Tree::MakeNodes(const unordered_map<string, int> &freqTable){
    //the frequency map consists of key and frequency, then is combined into nodes and inserted into a vector

    for(auto ch: freqTable){
        Node* neo = new Node();
        neo->_key = ch.first;
        neo->_freq = ch.second;
        neo->left = nullptr;
        neo->right = nullptr;
        treeNodes.push_back(neo);
    }
    Tree::SortTreeNodes(treeNodes);
}

void Tree::SortTreeNodes(vector<Node*> &treeNodes) {
    //soring nodes using selection sort and stacking them in reverse order frequency first, then alphabetically
    int minIndex;
    Node *tmp;
    for(size_t i = 0; i < 10; i++){
        for (size_t i = 0; i < treeNodes.size() - 1; i++) {
            minIndex = i;
            for (size_t j = i + 1; j < treeNodes.size(); j++) {
                if (Tree::Compare(treeNodes.at(j), treeNodes.at(minIndex))) {
                    minIndex = j;
                    tmp = treeNodes.at(i);
                    treeNodes.at(i) = treeNodes.at(minIndex);
                    treeNodes.at(minIndex) = tmp;
                }
            }
        }
    }

    // creating the frequency table file - the is the last time the treeNodes vector will be intact, so it made sense to create this now.
    string outFile = infileName + ".frequency";
    ofstream oFS(outFile);
    string key;
    stringstream ss;
    for (auto fr: treeNodes) {
        keyList.push_back(fr->_key);
        stringstream ss;
        string key;
        if(fr->_key != "CR" && fr->_key != "LF"){ // creating one extra space in the characters for formatting
            key = " ";
            key += fr->_key;
        } else
        {
            key = fr->_key;
        }
        ss << "{element: " << key<< ", frequency: " << fr->_freq << "}" << endl;

        oFS << ss.str();
    }

    oFS.close();

    Tree::BuildTree(treeNodes);

}
bool Tree::Compare(Node* &node1, Node* &node2){
    if(node1->_freq == node2->_freq){
        // if the frequncies are equal return true if key 1 > key 2 and false if not
        return (node1->_key > node2->_key);
    } else {
        // if the frequency is different, the this will return true if freq 1 > freq 2 and false if not
        return (node1->_freq > node2->_freq);
    }
}

bool Tree::CompareCodes(Node* &node1, Node* &node2){
    if(node1->_code.size() == node2->_code.size()){
        // if the frequencies are equal return true if key 1 > key 2 and false if not
        return (node1->_key > node2->_key);
    } else {
        // if the frequency is different, the this will return true if freq 1 > freq 2 and false if not
        return (node1->_code > node2->_code);
    }
}

void Tree::BuildTree(vector<Node*> &treeNodes){

/* this function is recursive between sorting and adding nodes
 * each time it cycles it combines two nodes from the vector and deletes those nodes
 * creating a parent that points to the two child nodes, the parent combines their frequency and characters into one node
 * after a parent is created it is pushed to the vector, then sorted
 * this process repeats until only one node remains in the vector which then becomes the root
 */

    if(treeNodes.size() == 0){
        return;
    }
    if(treeNodes.size() == 1){
        Node* neo = new Node();
        neo->_key = treeNodes.at(0)->_key;
        neo->_freq = treeNodes.at(0)->_freq;
        neo->left = treeNodes.at(0)->left;
        neo->right = treeNodes.at(0)->right;
        _root = neo;
        string code;
         Tree::TreeWalk(_root, codeTable, code);
         return;
    }

    Node* parent = new Node();
    Node *leftChild;
    Node *rightChild;

    // get the first item (starting at bottom to build the tree from the bottom up
    leftChild = treeNodes.back();
    treeNodes.pop_back();
    rightChild = treeNodes.back();
    treeNodes.pop_back();

    // combine child keys and sum frequencies, adding to parent node then add to list for sorting later
    parent->_key = leftChild->_key + rightChild->_key;
    parent->_freq = leftChild->_freq + rightChild->_freq;
    parent->left = leftChild;
    parent->right = rightChild;

    treeNodes.push_back(parent);
    if(treeNodes.size() > 1){
        Tree::SortTree(treeNodes);
    }
//
    BuildTree(treeNodes);
}

void Tree::SortTree(vector<Node*> &treeNodes){ // sorting method for building the tree
    int minIndex;
    Node *tmp;
    if(treeNodes.size() <= 1){
        return;
    }
        for (size_t i = 0; i < treeNodes.size() - 1; i++) {
            minIndex = i;
            for (size_t j = i + 1; j < treeNodes.size(); j++) {
                if (Tree::Compare(treeNodes.at(j), treeNodes.at(minIndex))) {
                    minIndex = j;
                    tmp = treeNodes.at(i);
                    treeNodes.at(i) = treeNodes.at(minIndex);
                    treeNodes.at(minIndex) = tmp;
                }
            }
        }
        Tree::BuildTree(treeNodes);
}

void Tree::TreeWalk(Node* &_root, unordered_map<string,string> &codeTable, string code) {
    //creates the code by finding the leaf in the tree and making a path

    if(_root->left == nullptr && _root->right == nullptr){
        codeTable[_root->_key] = code;
        return;
    }
    if(_root->left != nullptr){
        TreeWalk(_root->left, codeTable, code + "1");
    }
    if(_root->right != nullptr){

        TreeWalk(_root->right, codeTable, code + "0");
    }


}

void Tree::PrintCodeTable(const int &sent) { // prints code table to the browser and to a file
// write coding map to file

    string key;
    stringstream ss;

    if(sent == 3) {
        for(size_t i = 0; i < keyList.size(); i++) {
            key = keyList.at(i);
            ss << "{key: " << key << ", code: " << codeTable[key] << "}" << endl;
        }
        string outFile = infileName + ".table";
        ofstream oFS(outFile);
        cout << ss.str();
        oFS << ss.str();
        ss << ss.str();
        oFS.close();
    } else if (sent == 4){
        for(size_t i = 0; i < keyList.size(); i++) {
            key = keyList.at(i);
            ss << "{key: " << key << ", code: " << codeTable[key] << "}" << endl;
        }
        string outFile = outFileName + ".table";
        ofstream oFS(outFile);
        cout << ss.str();
        oFS << ss.str();

        oFS.close();
    }

}
void Tree::PrintFrequencyTable() { // prints the contents of the frequency file. frequency is not affected by an output file

    string freqLine;

    ifstream inFile(infileName + ".frequency" );

    while( getline(inFile, freqLine)){
        cout << freqLine << endl;
    }
    cin.clear();

}

void Tree::Write(string &inFile, const int sent){ // creates the encoded file



    if(sent == 3) {
        stringstream ss;
        ifstream inFS(inFile);
        ofstream oFS(infileName + ".encoded");
        char ch;
        string chStr;
        while(inFS.get(ch)){
            chStr = ch;
            ss << codeTable[chStr];
        }
        oFS << ss.str();

    } else if( sent == 4 ){
        ofstream oFS(outFileName + ".encoded");
        stringstream ss;
        ifstream inFS(inFile);
        char ch;
        string chStr;
        while(inFS.get(ch)){
            chStr = ch;
            ss << codeTable[chStr];

        }
        oFS << ss.str();
    }
}

void Tree::PrintCharacterEncoding(string ch) { //Prints the value of the character provided and a message if the character is not found
    string code;
        if(codeTable.find(ch) != codeTable.end()) {
            code = codeTable[ch];
            cout << code;
        } else {
            cout << "Character does not exist in the file" << endl;
        }
}

Tree::Node* Tree::GetRoot() {
    return this->_root;
//    cout << this->_root;
}


void Tree::Decode(Node* root, char character){

    cout << root->_key;
    if (_root->left == nullptr && _root->right == nullptr) {
        stringstream digit;
        ofstream oFS(outFileName + ".decoded");
        digit << character;
        cout << digit.str();
        oFS << digit.str();

    }

    char ch;
    fstream inFS(infileName + "decode");
    while (inFS.get(ch)) {
        cout << ch;
        if (ch == '1') {
            Decode(_root->left, character + '1');
        } else {
            Decode(_root->right, character + '0');
        }
    }
    //grab a character from the file
    //based on the char move that way until you reach leaf and take that char
    //place char in string stream
    //write to file
}