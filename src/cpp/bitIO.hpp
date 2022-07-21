#pragma once
#include <cstring>

static unsigned char kPIInput[10];
static unsigned char kPIOutput[10];

#define INPUT(name) BitIO name(#name, sizeof(#name))

class BitIO
{
public:
	static unsigned short byteCount;
	static unsigned char bitCount;

public:
	struct Mask
	{
		enum MaskIO : unsigned char
		{
			actualBit		= 1u << 0,	// => 1
			lastBit			= 1u << 1,	// => 2
			edgePos			= 1u << 2,	// => 4
			edgePosMem		= 1u << 3,	// => 8

			edgeNeg			= 1u << 4,	// => 16
			edgeNegMem		= 1u << 5,	// => 32
			edge			= 1u << 6,	// => 64
			edgeReserve		= 1u << 7,	// => 128

			edgePosAll = edgePos | edgePosMem,
			edgeNegAll = edgeNeg | edgeNegMem
		};

		unsigned char ma[8];

		Mask()
		{
			for (int i = 0; i <= 7; ++i)
				ma[i] = 1u << i;
		};
	} mask;

protected:
	unsigned char _name[40];
	unsigned char _io;
	unsigned short _byte;
	unsigned char _bit;
public:
	static void Init()
	{
		byteCount = 0;
		bitCount = 0;;
	}

	BitIO(char const* name, size_t size)
	{
		BitIO();

		memcpy(_name, name, size);
	};

	BitIO(unsigned short byte, unsigned char bit)
	{
		BitIO();

		_byte = byte;
		_bit = bit;
	};

	BitIO()
	{
		_name[0] = 0;
		_io = 0;
		_byte = byteCount;
		_bit = bitCount;

		if (++bitCount >= 8)
		{
			++byteCount;
			bitCount = 0;
		}
	};

	~BitIO()
	{
		byteCount = 0;
		bitCount = 0;
	};


	void Update()
	{
		// Shift act bit to last
		if (_io & mask.actualBit)
			_io |= 2;
		else
			_io &= ~2;

		// Save old io
		_io &= 0x2a; // _io | 0010 1010	

		if (kPIInput[_byte] & mask.ma[_bit])
			_io |= mask.actualBit;

		// Check if there is something to do
		if ((bool)(_io & mask.lastBit) == (bool)(_io & mask.actualBit))
			return;



		// Define Edge
		// ___ => _|¯ act = 1
		// ¯¯¯ => ¯|_ act = 0
		_io |= mask.edge;

		if (_io & mask.actualBit)
			_io |= mask.edgePosAll;
		else
			_io |= mask.edgeNegAll;
	}

	bool Get()
	{
		return _io & 1;
	}

	bool GetEdge()
	{
		return _io & mask.edge;
	}

	bool GetPos()
	{
		return _io & mask.edgePos;
	}

	bool GetNeg()
	{
		return _io & mask.edgeNeg;
	}

	bool GetPosMem()
	{
		return _io & mask.edgePosMem;
	}

	bool GetNegMem()
	{
		return _io & mask.edgeNegMem;
	}

	void Set(bool state)
	{
		if (state) // set
			kPIInput[_byte] |= mask.ma[_bit] & 0xff;
		else // reset
			kPIInput[_byte] &= ~mask.ma[_bit] & 0xff;
	}

	void ResetMem()
	{
		_io &= ~0x28;
	}
};

unsigned short BitIO::byteCount = 0;
unsigned char BitIO::bitCount = 0;
