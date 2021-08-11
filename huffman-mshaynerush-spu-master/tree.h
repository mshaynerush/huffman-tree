/*
 Filename: huffmantree.h
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Shayne Rushton
 Date: 0/14/2021
 Course: Data Structures II
*/



#ifndef REDO_HUFFMA_TREE_H
#define REDO_HUFFMA_TREE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
#include <ostream>

using namespace std;
class Tree {


public:

    struct Node{
        string _key;
        int _freq = 0;
        string _code;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* _root;
    unordered_map<string,int> freqTable;
    vector<string>keyList;
    vector<Node*> treeNodes;
    unordered_map<string, string> codeTable;
    string infileName;
    string outFileName;
    string defaultFileName;
    string decodeFlag;
    int sent;
    Tree();
    ~Tree();
    Node* GetRoot();
    void MakeFrequencyMap(string &inFile);
    void MakeNodes(const unordered_map<string, int> &freqTable);
    void SortTreeNodes(vector<Node*> &treeNodes);
    bool Compare(Node* &node1, Node* &node2);
    bool CompareCodes(Node* &node1, Node* &node2);
    void BuildTree(vector<Node*> &treeNodes);
    void SortTree(vector<Node*> &treeNodes);
    void Write(string &inFile, int const sent);
    void Read(string &inFile, string outFile);
    void TreeWalk(Node* &node, unordered_map<string,string> &codeTable, string code);
    void PrintCodeTable(const int &sent);
    void PrintFrequencyTable();
    void PrintCharacterEncoding(string ch);
    void Decode(Node* root, char character);

};


#endif //REDO_HUFFMA_TREE_H
