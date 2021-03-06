#include <bitmrc_endian.h>

#ifdef __cplusplus
extern "C" {
#endif

/* \todo: pin this to stdint.h-types (int16/int32/uint16/uint32) etc .. -steady286-*/

short (*BigShort) ( short s );
short (*LittleShort) ( short s );
int (*BigLong) (int32_t i);
int (*LittleLong) ( int32_t i );
int64_t (*BigLongLong) ( int64_t i );
int64_t (*LittleLongLong) ( int64_t i );
float (*BigFloat) ( float f );
float (*LittleFloat) ( float f );
void x() {

}
short ShortSwap( short s )
{
	unsigned char b1, b2;

	b1 = s & 255;
	b2 = (s >> 8) & 255;

	return (b1 << 8) + b2;
}

short ShortNoSwap( short s )
{
	return s;
}

int LongSwap (int32_t i)
{
	unsigned char b1, b2, b3, b4;

	b1 = i & 255;
	b2 = ( i >> 8 ) & 255;
	b3 = ( i>>16 ) & 255;
	b4 = ( i>>24 ) & 255;

	return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}

int LongNoSwap( int32_t i )
{
	return i;
}

int64_t LongLongSwap (int64_t i)
{
	unsigned char b1, b2, b3, b4, b5, b6, b7, b8;

	b1 = i & 255;
	b2 = ( i >> 8 ) & 255;
	b3 = ( i >> 16 ) & 255;
	b4 = ( i >> 24 ) & 255;
	b5 = ( i >> 32 ) & 255;
	b6 = ( i >> 40 ) & 255;
	b7 = ( i >> 48 ) & 255;
	b8 = ( i >> 56 ) & 255;

	return ((int64_t)b1 << 56) + ((int64_t)b2 << 48) + ((int64_t)b3 << 40) + ((int64_t)b4 << 32) + ((int64_t)b5 << 24) + ((int64_t)b6 << 16) + ((int64_t)b7 << 8) + b8;
}

int64_t LongLongNoSwap( int64_t i )
{
	return i;
}

float FloatSwap( float f )
{
	union
	{
		float f;
		unsigned char b[4];
	} dat1, dat2;

	dat1.f = f;
	dat2.b[0] = dat1.b[3];
	dat2.b[1] = dat1.b[2];
	dat2.b[2] = dat1.b[1];
	dat2.b[3] = dat1.b[0];
	return dat2.f;
}

float FloatNoSwap( float f )
{
	return f;
}

bool BigEndianSystem;  //you might want to extern this

void InitEndian(void)
{
	unsigned char SwapTest[2] = { 1, 0 };

	if( *(short *) SwapTest == 1 )
	{
		//little endian
		BigEndianSystem = false;

		//set func pointers to correct funcs
		BigShort = ShortSwap;
		LittleShort = ShortNoSwap;
		BigLong = LongSwap;
		LittleLong = LongNoSwap;
		BigLongLong = LongLongSwap;
		LittleLongLong = LongLongNoSwap;
		BigFloat = FloatSwap;
		LittleFloat = FloatNoSwap;
	}
	else
	{
		//big endian
		BigEndianSystem = true;

		BigShort = ShortNoSwap;
		LittleShort = ShortSwap;
		BigLong = LongNoSwap;
		LittleLong = LongSwap;
		BigLongLong = LongLongNoSwap;
		LittleLongLong = LongLongSwap;
		BigFloat = FloatSwap;
		LittleFloat = FloatNoSwap;
	}
}
#ifdef __cplusplus
}
#endif
