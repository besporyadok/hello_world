#ifndef __XRAYMATHCMN_H__
#define __XRAYMATHCMN_H__

#ifdef min
#	undef _MIN
#	undef _MAX
#	undef min
#	undef max
#endif

// generic
template <class T>	IC T		_min	(T a, T b)	{ return a<b?a:b;	}
template <class T>	IC T		_max	(T a, T b)	{ return a>b?a:b;	}
template <class T>	IC T		_sqr	(T a)		{ return a*a;		}

// int8
IC s8 		_min	(s8  x, s8  y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s8 ) * 8 - 1))); };
IC s8 		_max	(s8  x, s8  y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s8 ) * 8 - 1))); };

// int16
IC s16		_min	(s16 x, s16 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };
IC s16		_max	(s16 x, s16 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };

// int32
IC s32		_min	(s32 x, s32 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };
IC s32		_max	(s32 x, s32 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };

// int64
IC s64		_min	(s64 x, s64 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };
IC s64		_max	(s64 x, s64 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };

#endif