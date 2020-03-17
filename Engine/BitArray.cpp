#include "BitArray.h"
#include <intrin.h>


void BitArray::setMaxBytes(size_t maxBytes)
{
	bitArrayMax = maxBytes;
}

void BitArray::ClearAll(void)
{
	for (size_t i = 0; i < bitArrayMax; i++)
	{
		bitArray[i] &= 0x00;
	}
	
}

void BitArray::SetAll(void)
{
	for (size_t i = 0; i < bitArrayMax; i++)
	{
		bitArray[i] |= 0xFF;
	}
}

bool BitArray::AreAllClear(void) const
{
	for (size_t i = 0; i < bitArrayMax; i++)
	{
		if (bitArray[i] != 0x00)
			return false;
	}
	return true;
}

bool BitArray::AreAllSet(void) const
{
	for (size_t i = 0; i < bitArrayMax; i++)
	{
		if (bitArray[i] != 0xFF)
			return false;
	}
	return true;
	
}

bool BitArray::IsBitSet(size_t) const
{

	return false;
}

bool BitArray::IsBitClear(size_t) const
{
	return false;
}

void BitArray::SetBit(size_t position)
{
	size_t byteIndex = position / oneByte;
	size_t bitIndex = position % oneByte;
	bitArray[byteIndex] |= 0x01 << bitIndex;
}

void BitArray::ClearBit(size_t position)
{
	size_t byteIndex = position / oneByte;
	size_t bitIndex = position % oneByte;
	bitArray[byteIndex] &= ~(0x01 << bitIndex);
}

size_t BitArray::GetFirstClearBit(void) const
{
	size_t byteIndex = 0;
	while ((bitArray[byteIndex] == 0xff) && (byteIndex < bitArrayMax)) {
		byteIndex++;
	}
	unsigned long bitIndex;
	unsigned char isNonZero;
	
	isNonZero = _BitScanForward(&bitIndex, ~bitArray[byteIndex]);
	if (isNonZero)
	{
		return (byteIndex * oneByte) + (bitIndex);
	}
	else
	{
		size_t notFound = 500;
		return notFound;
	}
	

	
}

size_t BitArray::GetFirstSetBit(void) const
{
	size_t byteIndex = 0;
	while ((bitArray[byteIndex] == 0xff) && (byteIndex < bitArrayMax)) {
		byteIndex++;
	}
	unsigned long bitIndex;
	unsigned char isNonZero;
	isNonZero = _BitScanForward(&bitIndex, bitArray[byteIndex]);
	if (isNonZero)
	{
		return (byteIndex * oneByte) + (bitIndex);
	}
	else
		return NULL;
}

bool BitArray::operator[](size_t i_index) const
{
	return bitArray[i_index];
}
