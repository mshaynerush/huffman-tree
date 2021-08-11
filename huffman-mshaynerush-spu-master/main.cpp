/*
 Filename: huffmantree.h
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Shayne Rushton
 Date: 0/14/2021
 Course: Data Structures II
*/


#include "tree.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    Tree tr;
    Tree::Node* root = tr.GetRoot();
    if(argc == 3) { // this means only an input file was included along with the desired process
        string userOption = argv[1];
        string inFile = argv[2];
        string outFile = "default";
        tr.Read(inFile, outFile);
        tr.Write(inFile, 3);
        if (userOption == "-encode") {
            ifstream inputFile(inFile, ios::binary);
            inputFile.seekg(0, ios::end);
            cout << inputFile.tellg() << " bytes encoded" << endl;
        }
        if (userOption == "-frequency") {
            tr.PrintFrequencyTable();
        }
        if( userOption == "-encoding-table"){
            tr.PrintCodeTable(3);
        }
    } else if(argc == 4){ // methods here are triggered when an output file is entered
        string userOption = argv[1];
        string inFile = argv[2];
        string outFile = argv[3];
        tr.Read(inFile, outFile);
        tr.Write(inFile, 4);
        if (userOption == "-encode") {
            ifstream inputFile(inFile, ios::binary);
            inputFile.seekg(0, ios::end);
            cout << inputFile.tellg() << " bytes encoded" << endl;
        }
        if (userOption == "-frequency") {
            tr.PrintFrequencyTable();
        }
        if (userOption == "-single"){
            tr.PrintCharacterEncoding(outFile);
        }
        if( userOption == "-encoding-table"){
            cin.ignore();
            tr.PrintCodeTable(4);
        }
        if( userOption == "-decode"){
          tr.decodeFlag = "Yes";

        }
    } else {
        cout << "usage: executable [-single, -encode, -decode, -encoding-table, -frequency] input filename optional output file name" << endl;
    }
    if(tr.decodeFlag == "Yes"){
        char character = 0;
        tr.Decode(root, character);
    }
    return 0;
}
