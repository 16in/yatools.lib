#pragma once

#include <stdint.h>

#ifndef YATOOLS_IMPORT
#define YATOOLS_IMPORT
#endif

namespace yatools
{

	/**
	* @name 整数
	* @{
	*/

	typedef int8_t int8;		//!< 8bit符号付き整数
	typedef int16_t int16;		//!< 16bit符号付き整数
	typedef int32_t int32;		//!< 32bit符号付き整数
	typedef int64_t int64;		//!< 64bit符号付き整数

	typedef uint8_t uint8;		//!< 8bit符号なし整数
	typedef uint16_t uint16;	//!< 16bit符号なし整数
	typedef uint32_t uint32;	//!< 32bit符号なし整数
	typedef uint64_t uint64;	//!< 64bit符号なし整数

	typedef int8_t sbyte;		//!< 8bit符号付き整数
	typedef uint8_t byte;		//!< 8bit符号なし整数
	typedef uint16 ushort;		//!< 16bit符号なし整数
	typedef uint32 uint;		//!< 32bit符号なし整数
	typedef uint64 ulong;		//!< 64bit符号なし整数

	typedef intptr_t intptr;	//!< 符号付きポインタ整数
	typedef uintptr_t uintptr;	//!< 符号なしポインタ整数

	/**
	* @}
	*/

}