#include "HuffmanTree.h"

void HuffmanTree::readFromFile(const std::string & _path)
{
	mFileReader.ReadFile(_path);
}

void HuffmanTree::computeFrequency()
{
	//For each time a character in the text appears, +1 frequency.
	//For each character check if theres a frequency and if there is, store char with its frequency
	
	std::string temp = mFileReader.GetText();
	for (auto text = temp.begin(); text != temp.end(); ++text)
	{
		if (mCharsFreq[static_cast<int>(*text)].first == '\0')
			mCharsFreq[static_cast<int>(*text)].first = *text;

		mCharsFreq[static_cast<int>(*text)].second += 1;
	}

	//Clean up empty spaces
	for (auto obj = mCharsFreq.begin(); obj != mCharsFreq.end();)
	{
		if (obj->first == '\0')
			obj = mCharsFreq.erase(obj);
		else
			obj++;
	}

	return;
}

void HuffmanTree::buildTree()
{
	std::shared_ptr<LeafNode> pLeafOne = nullptr;
	std::shared_ptr<LeafNode> pLeafTwo = nullptr;
	std::shared_ptr<InternalNode> pInternalPtr = nullptr;

	for (unsigned int i = 0; i < mCharsFreq.size(); i++)
	{
		pLeafOne = std::make_shared<LeafNode>();
		pLeafOne->SetWeigth(mCharsFreq[i].second);
		pLeafOne->SetSymbol(mCharsFreq[i].first);
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
	mCharsFreq.resize(ASCII_SIZE);
	for (auto obj = mCharsFreq.begin(); obj != mCharsFreq.end(); ++obj)
		*obj = std::make_pair('\0', 0);

}

void HuffmanTree::reset()
{

	mRoot.reset();
	mCharsFreq.clear();
	mNodes.clear();
	mBitWriter.Reset();
	mFileReader.Reset();

	return;
}

void HuffmanTree::computeBitSize()
{
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

	computeFrequency();
	buildTree();
	traverseTree(mRoot, FLAGS::CREATE_BINARY_CODE);

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

	std::string test;
	test = mBitWriter.GetTotalBinaryCodeString(mFileReader.GetText());
	test = mBitWriter.GetTreeCode();

	if (1)
	{

	}

#ifdef _DEBUG

#endif

	return true;
}

bool HuffmanTree::PrintTree()
{
	if (!mRoot)
		return false;
	
	traverseTree(mRoot, FLAGS::PRINT_TREE);
	return true;
}

bool HuffmanTree::ResetTree()
{
	reset();
	return true;
}
