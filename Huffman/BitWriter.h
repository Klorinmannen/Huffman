#pragma once
#include<string>

class BitWriter
{
private:

	std::string mTempCode;
	std::string mTotalBinaryCode;
	std::string mTreeCode;

	std::unordered_map<char, std::string> mSymbolsMap;

	void reset()
	{
		mTempCode.clear();
		mTotalBinaryCode.clear();
		mTreeCode.clear();
		mSymbolsMap.clear();
		return;
	}
public:
	BitWriter(){}
	~BitWriter()
	{
		reset();
	}

	void WriteBit(const int & _bit)
	{
		if (_bit != -1)
			mTempCode += std::to_string(_bit);
		else if(!mTempCode.empty())
			mTempCode.pop_back();

		return;
	}

	void WriteSymbol(const char & _char)
	{
		mSymbolsMap.insert(std::make_pair(_char, mTempCode));
		return;
	}

	std::string & GetTotalBinaryCodeString(const std::string & _text)
	{
		mTotalBinaryCode.clear();

		for (auto text = _text.begin(); text != _text.end(); ++text)
			mTotalBinaryCode += (mSymbolsMap.find(*text)->second);

		return mTotalBinaryCode;
	}

	std::string & GetBinaryCode() { return mTempCode; }

	std::string & GetTreeCode()
	{
		for (auto t = mSymbolsMap.begin(); t != mSymbolsMap.end(); ++t)
		{
			mTreeCode += t->second;
			mTreeCode += t->first;
		}

		return mTreeCode;
	}

	std::unordered_map<char, std::string> & GetSymbolsMap() { return mSymbolsMap; }

	void Clear(){ reset(); return; }
	
	void Init(const unsigned int & _size) 
	{ 
		mTempCode = "";
		mTotalBinaryCode = "";
		mTreeCode = "";
		mSymbolsMap.reserve(_size);

		return; 
	}

	void DebugPrint(const std::string & _text)
	{
		std::cout << mTempCode << std::endl;
		std::cout << GetTotalBinaryCodeString(_text) << std::endl;
		std::cout << GetTreeCode() << std::endl;
	}
};