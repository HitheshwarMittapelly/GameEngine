#pragma once
#include <cstdint>
class BitArray {
public:
	void setMaxBytes(size_t maxBytes);
	void ClearAll(void);
	void SetAll(void);

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	bool IsBitSet(size_t) const;
	bool IsBitClear(size_t) const;

	void SetBit(size_t);
	void ClearBit(size_t);

	size_t GetFirstClearBit(void) const;
	size_t GetFirstSetBit(void) const;

	bool operator[](size_t i_index) const;
private:
	size_t bitArrayMax;
	size_t oneByte = 8;
	uint8_t  bitArray[25];


};