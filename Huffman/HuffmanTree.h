#pragma once
#include<queue>
#include<vector>
#include<utility>
#include<iostream>
#include<unordered_map>
#include<fstream>
#include"InternalNode.h"

class HuffmanTree
{
private:

	enum FLAGS{PRINT, CREATE_BINARY_CODE};

	class Compare
	{
	public:
		bool operator()(const std::shared_ptr<LeafNode> & lhs, const std::shared_ptr<LeafNode> & rhs) const
		{
			return lhs->GetWeight() > rhs->GetWeight();
		}
	};

	std::deque<std::shared_ptr<LeafNode>> mNodes;
	std::shared_ptr<InternalNode> mRoot;
	std::unordered_map<char, std::string> mSymbolsMap;
	std::vector<std::pair<char, unsigned int>> mCharsnFreq;

	std::string mBinaryCode;
	std::string mText;
	std::string mPath;
	unsigned int ASCII_SIZE;

	void readFromFile();
	void writeToFile(const std::string & _fileName);
	void buildBinaryCode();
	void manageBinaryCode(const int & _arg);
	void computeFrequency();
	void buildTree();
	void traverseTree(const std::shared_ptr<LeafNode> & _node, const int & _arg);
	void init();
	void reset();
	void printCompression();
public:
	HuffmanTree();
	HuffmanTree(unsigned int _ascii_size);
	~HuffmanTree();

	bool MainFromString(const std::string & _text);
	bool MainFromTextFile(const std::string & _path);
	bool WriteBinaryCodeToFile(const std::string & _fileName);
	bool PrintTree();
	bool ResetTree();
	std::string GetBinaryCode() const;

};