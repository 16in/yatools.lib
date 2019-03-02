#pragma once

#include <stdint.h>

#ifndef YATOOLS_IMPORT
#define YATOOLS_IMPORT
#endif

namespace yatools
{

	/**
	* @name ����
	* @{
	*/

	typedef int8_t int8;		//!< 8bit�����t������
	typedef int16_t int16;		//!< 16bit�����t������
	typedef int32_t int32;		//!< 32bit�����t������
	typedef int64_t int64;		//!< 64bit�����t������

	typedef uint8_t uint8;		//!< 8bit�����Ȃ�����
	typedef uint16_t uint16;	//!< 16bit�����Ȃ�����
	typedef uint32_t uint32;	//!< 32bit�����Ȃ�����
	typedef uint64_t uint64;	//!< 64bit�����Ȃ�����

	typedef int8_t sbyte;		//!< 8bit�����t������
	typedef uint8_t byte;		//!< 8bit�����Ȃ�����
	typedef uint16 ushort;		//!< 16bit�����Ȃ�����
	typedef uint32 uint;		//!< 32bit�����Ȃ�����
	typedef uint64 ulong;		//!< 64bit�����Ȃ�����

	typedef intptr_t intptr;	//!< �����t���|�C���^����
	typedef uintptr_t uintptr;	//!< �����Ȃ��|�C���^����

	/**
	* @}
	*/

}