#pragma once
#include<vector>
#include"Utility.h"
class FrequencyReader
{
private:

	std::vector<std::pair<char, unsigned int>> mCharsFreq;

	void cleanUp()
	{
		for (auto obj = mCharsFreq.begin(); obj != mCharsFreq.end();)
		{
			if (obj->first == '\0')
				obj = mCharsFreq.erase(obj);
			else
				obj++;
		}
	}

public:
	FrequencyReader() {}
	~FrequencyReader() {}

	void ComputeFrequency(const std::string & _text)
	{
		if (_text.empty())
			return;
		
		for (auto text = _text.begin(); text != _text.end(); ++text)
		{
			if (mCharsFreq[static_cast<int>(*text)].first == '\0')
				mCharsFreq[static_cast<int>(*text)].first = *text;

			mCharsFreq[static_cast<int>(*text)].second += 1;
		}

		cleanUp();
	}

	void Clear()
	{
		mCharsFreq.clear();
		return;
	}

	void Init(const unsigned int & _size)
	{

		if (!mCharsFreq.empty())
			mCharsFreq.clear();

		mCharsFreq.resize(_size);

		for (auto obj = mCharsFreq.begin(); obj != mCharsFreq.end(); ++obj)
			*obj = std::make_pair('\0', 0);

		return;
	}

	std::vector<std::pair<char, unsigned int>> & GetFreqsNSymbols() { return mCharsFreq; }

};