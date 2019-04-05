#pragma once
#include<queue>
#include<vector>
#include<utility>
#include<iostream>
#include<unordered_map>
#include<fstream>

#include"InternalNode.h"
#include"BitWriter.h"
#include"FileReader.h"
#include"FrequencyReader.h"

class HuffmanTree
{
private:

	enum FLAGS{PRINT_TREE, CREATE_BINARY_CODE, SAVE_TREE};

	class Compare
	{
	public:
		bool operator()(const std::shared_ptr<LeafNode> & lhs, const std::shared_ptr<LeafNode> & rhs) const
		{
			return lhs->GetWeight() > rhs->GetWeight();
		}
	};

	BitWriter mBitWriter;
	FileReader mFileReader;
	FrequencyReader mFrequencyReader;

	std::deque<std::shared_ptr<LeafNode>> mNodes;
	std::shared_ptr<InternalNode> mRoot;
	unsigned int ASCII_SIZE;
	unsigned int encodedSize;
	unsigned int treeSize;
	unsigned int encodedTotalBitSize;
	unsigned int unEncodedSize;

	void readFromFile(const std::string & _path);
	void computeFrequency();
	void buildTree();
	void traverseTree(const std::shared_ptr<LeafNode> & _node, const int & _arg);
	void init();
	void reset();
	void computeSize();
	void debugPrint(const std::string & _string);
public:
	HuffmanTree();
	HuffmanTree(unsigned int _ascii_size);
	~HuffmanTree();

	//MISC
	bool MainFromString(const std::string & _text);
	bool MainFromTextFile(const std::string & _path);
	bool PrintTree();
	bool Reset();
	void Init();
	void ClearAll();

};