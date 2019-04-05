#include "HuffmanTree.h"

void HuffmanTree::readFromFile(const std::string & _path)
{
	mFileReader.ReadFile(_path);
}

void HuffmanTree::computeFrequency()
{
	
	mFrequencyReader.ComputeFrequency(mFileReader.GetText());

	return;
}

void HuffmanTree::buildTree()
{
	std::shared_ptr<LeafNode> pLeafOne = nullptr;
	std::shared_ptr<LeafNode> pLeafTwo = nullptr;
	std::shared_ptr<InternalNode> pInternalPtr = nullptr;
	auto tempVec = mFrequencyReader.GetFreqsNSymbols();
	for (auto t = tempVec.begin(); t != tempVec.end(); ++t)
	{
		pLeafOne = std::make_shared<LeafNode>();
		pLeafOne->SetWeigth(t->second);
		pLeafOne->SetSymbol(t->first);
		mNodes.push_back(pLeafOne);
	}

	std::sort(mNodes.begin(), mNodes.end(), Compare());

	while (mNodes.size() > 1)
	{
		pLeafOne = mNodes.back();
		mNodes.pop_back();
		if (mNodes.size() > 0)
		{
			pLeafTwo = mNodes.back();
			mNodes.pop_back();

			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetWeigth(pLeafOne->GetWeight() + pLeafTwo->GetWeight());
			pInternalPtr->SetLeftChild(pLeafOne);
			pInternalPtr->SetRightChild(pLeafTwo);

			mNodes.push_back(pInternalPtr);
		}
		else
		{
			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetWeigth(pLeafOne->GetWeight());
			pInternalPtr->SetLeftChild(pLeafOne);
		}

		std::sort(mNodes.begin(), mNodes.end(), Compare());
	}

	mRoot = std::dynamic_pointer_cast<InternalNode>(mNodes.front());
	mNodes.pop_front();
 
	pLeafOne.reset();
	pLeafTwo.reset();
	pInternalPtr.reset();

	return;
}

void HuffmanTree::traverseTree(const std::shared_ptr<LeafNode>& _node, const int & _arg)
{
	std::shared_ptr<InternalNode> temp = nullptr;
	temp = std::dynamic_pointer_cast<InternalNode>(_node);

	switch (_arg)
	{

	case FLAGS::CREATE_BINARY_CODE:
	{
		if (temp)
		{
			mBitWriter.WriteBit(0);
			traverseTree(temp->GetLeftChild(), FLAGS::CREATE_BINARY_CODE);
			mBitWriter.WriteBit(1);
			traverseTree(temp->GetRightChild(), FLAGS::CREATE_BINARY_CODE);

		}
		else
		{
			//leaf node
			_node->SetBinaryCode(mBitWriter.GetBinaryCode());
			mBitWriter.WriteSymbol(_node->GetSymbol());
		}

		mBitWriter.WriteBit(-1);
	}
		break;
	case FLAGS::PRINT_TREE:
		if (temp)
		{
			traverseTree(temp->GetLeftChild(), FLAGS::PRINT_TREE);
			traverseTree(temp->GetRightChild(), FLAGS::PRINT_TREE);
		}
		else
		{
			//leaf node
			std::cout <<
				"Binary code: " <<
				_node->GetSymbol() <<
				" " <<
				_node->GetWeight() <<
				". " <<
				_node->GetBindaryCode() <<
				std::endl;
		}

		break;
	}


	return;
}

void HuffmanTree::init()
{
	mFrequencyReader.Init(ASCII_SIZE);
	mBitWriter.Init(ASCII_SIZE);
	mFileReader.Init();
}


void HuffmanTree::Init()
{
	init();
}

void HuffmanTree::ClearAll()
{
	mRoot.reset();
	mNodes.clear();
	mFrequencyReader.Clear();
	mBitWriter.Clear();
	mFileReader.Clear();

	return;
}


void HuffmanTree::reset()
{
	mRoot.reset();
	mNodes.clear();
	mFrequencyReader.Init(ASCII_SIZE);
	mBitWriter.Clear();
	mFileReader.Clear();

	return;
}

void HuffmanTree::computeSize()
{

	auto map = mBitWriter.GetSymbolsMap();
	auto freqs = mFrequencyReader.GetFreqsNSymbols();
	encodedSize = 0;
	treeSize = 0;

	for (auto t = freqs.begin(); t != freqs.end(); ++t)
	{
		auto p = map.find(t->first);
		encodedSize += p->second.length() * t->second;
	}

	auto code = mBitWriter.GetTreeCode();
	for (auto t = code.begin(); t != code.end(); ++t)
	{
		if (*t != '1' && *t != '0')
		{
			treeSize += 8;
		}

		treeSize += 1;
	}

	//treeSize = mBitWriter.GetTreeCode().length();
	encodedTotalBitSize = treeSize + encodedSize;
	unEncodedSize = mFileReader.GetText().length() * 8;

	debugPrint("Coded: " + std::to_string(encodedTotalBitSize) + " Bits or " + std::to_string(encodedTotalBitSize / 8) + " Bytes");
	debugPrint("Uncoded: " + std::to_string(unEncodedSize) + " Bits or " + std::to_string(unEncodedSize / 8) + " Bytes");
}

void HuffmanTree::debugPrint(const std::string & _string)
{
	std::cout << _string << std::endl;
}

HuffmanTree::HuffmanTree()
{
	ASCII_SIZE = 256;
	init();
}

HuffmanTree::HuffmanTree(unsigned int _ascii_size)
{
	ASCII_SIZE = _ascii_size;
	init();
}

HuffmanTree::~HuffmanTree()
{
}

bool HuffmanTree::MainFromString(const std::string & _text)
{
	if (_text.empty())
		return false;
	if (mRoot)
		reset();

	mFileReader.InsertString(_text);
	computeFrequency();
	buildTree();
	traverseTree(mRoot, FLAGS::CREATE_BINARY_CODE);

#ifdef _DEBUG
	debugPrint(mBitWriter.GetTotalBinaryCodeString(mFileReader.GetText()) + " " + std::to_string(mBitWriter.GetTotalBinaryCodeString(mFileReader.GetText()).length()));
	debugPrint(mBitWriter.GetTreeCode());
#endif

	computeSize();


	return true;
}

bool HuffmanTree::MainFromTextFile(const std::string & _path)
{
	if (_path.empty())
		return false;
	if (mRoot)
		reset();

	readFromFile(_path);
	computeFrequency();
	buildTree();
	traverseTree(mRoot, FLAGS::CREATE_BINARY_CODE);

#ifdef _DEBUG
	debugPrint(mBitWriter.GetTotalBinaryCodeString(mFileReader.GetText()) + " " + std::to_string(mBitWriter.GetTotalBinaryCodeString(mFileReader.GetText()).length()));
	debugPrint(mBitWriter.GetTreeCode());
#endif



	computeSize();

	return true;
}

bool HuffmanTree::PrintTree()
{
	if (!mRoot)
		return false;
	
	traverseTree(mRoot, FLAGS::PRINT_TREE);
	return true;
}

bool HuffmanTree::Reset()
{
	reset();
	return true;
}
