#pragma once
#include<string>

class BitWriter
{
public:
	enum CODE_TYPE { TOTAL_TYPE, TREE_TYPE };

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
	}
public:
	BitWriter()
	{

	}

	~BitWriter()
	{
		reset();
	}

	void WriteBit(const int & _bit)
	{
		if (_bit != -1)
			mTempCode.push_back(_bit);
		else if(!mTempCode.empty())
			mTempCode.pop_back();

	}

	void WriteSymbol(const char & _char)
	{
		mSymbolsMap.insert(std::make_pair(_char, mTempCode));
	}

	std::string & GetTotalBinaryCodeString(const std::string & _text)
	{
		mTotalBinaryCode.clear();

		for (auto text = _text.begin(); text != _text.end(); ++text)
			mTotalBinaryCode += mSymbolsMap.find(*text)->second;

		return mTotalBinaryCode;
	}

	std::string & GetBinaryCode()
	{
		return mTempCode;
	}

	std::string & GetTreeCode()
	{
		for (auto t = mSymbolsMap.begin(); t != mSymbolsMap.end(); ++t)
		{
			mTreeCode += t->second;
			mTreeCode += t->first;
		}

		return mTreeCode;
	}

	void Reset()
	{
		reset();
	}
};