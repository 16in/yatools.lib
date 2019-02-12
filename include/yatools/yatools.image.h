#pragma once

#include <yatools.type.h>

namespace yatools
{
	namespace image
	{

		/**
		* @name �s�N�Z���J���[�\��
		* @{
		*/
		/**
		* @enum ColorFormat
		* @brief �J���[�t�H�[�}�b�g
		* @details
		*	�s�N�Z���P�ʂł̃J���[�t�H�[�}�b�g�ł��B
		*/
		enum ColorFormat
		{

			Gray8,		//!< Gray 8bit
			Gray16,		//!< Gray 16bit
			R5G5B5,		//!< Red 5bit, Green 5bit, Blue 5bit
			R5G6B5,		//!< Red 5bit, Green 6bit, Blue 5bit
			R4G4B4,		//!< Red 4bit, Green 4bit, Blue 4bit
			R4G4B4A4,	//!< Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
			A4R4G4B4,	//!< Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
			R8G8B8,		//!< Red 8bit, Green 8bit, Blue 8bit
			R8G8B8A8,	//!< Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
			A8R8G8B8,	//!< Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit

			RsGsBs,		//! Red, Green, Blue single float
			RsGsBsAs,	//! Red, Green, Blue, Alpha single float
			AsRsGsBs,	//! Alpha, Red, Green, Blue single float

			RdGdBd,		//! Red, Green, Blue double float
			RdGdBdAd,	//! Red, Green, Blue, Alpha double float
			AdRdGdBd,	//! Alpha, Red, Green, Blue double float

		};


#pragma pack( 0 )

		//! Gray 8bit
		struct YATOOLS_IMPORT ColorGray8
		{
			uint8 Gray;
		};

		//! Gray 16bit
		struct YATOOLS_IMPORT ColorGray16
		{
			uint16 Gray;
		};

		//! Red 5bit, Green 5bit, Blue 5bit
		struct YATOOLS_IMPORT ColorR5G6B5
		{
			uint8 Red : 5;
			uint8 Green : 5;
			uint8 Blue : 5;
			uint8 reserve : 1;
		};

		//! Red 5bit, Green 6bit, Blue 5bit
		struct YATOOLS_IMPORT ColorR5G6B5
		{
			uint8 Red : 5;
			uint8 Green : 6;
			uint8 Blue : 5;
		};

		//! Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorR4G4B4
		{
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
			uint8 reserve : 4;
		};

		//! Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
		struct YATOOLS_IMPORT ColorR4G4B4A4
		{
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
			uint8 Alpha : 4;
		};

		//! Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorA4R4G4B4
		{
			uint8 Alpha : 4;
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
		};

		//! Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorR8G8B8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
		struct YATOOLS_IMPORT ColorR8G8B8A8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
			uint8 Alpha;
		};

		//! Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorA8R8G8B8
		{
			uint8 Alpha;
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorRsGsBs
		{
			float Red;
			float Green;
			float Blue;
		};

		//! Red, Green, Blue, Alpha single float
		struct YATOOLS_IMPORT ColorRsGsBsAs
		{
			float Red;
			float Green;
			float Blue;
			float Alpha;
		};

		//! Alpha, Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorAsRsGsBs
		{
			float Alpha;
			float Red;
			float Green;
			float Blue;
		};

		//! Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorRdGdBd
		{
			double Red;
			double Green;
			double Blue;
		};

		//! Red, Green, Blue, Alpha double float
		struct YATOOLS_IMPORT ColorRdGdBdAd
		{
			double Red;
			double Green;
			double Blue;
			double Alpha;
		};

		//! Alpha, Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorAdRdGdBd
		{
			double Alpha;
			double Red;
			double Green;
			double Blue;
		};

		/**
		* @}
		*/

#pragma pack( )


		/**
		* @class ColorBuffer
		* @brief �J���[�o�b�t�@
		* @details
		*	�J���[�o�b�t�@�Ǘ��N���X�ł��B
		*/
		class YATOOLS_IMPORT ColorBuffer
		{
		public:
			/**
			* @name ����/�J��
			* @{
			*/
			/**
			* @brief ����
			* @param[in] format				�J���[�o�b�t�@�t�H�[�}�b�g
			* @param[in] width				����
			* @param[in] height				�c��
			* @returns �������ꂽ�J���[�o�b�t�@�B���s����NULL
			* @details
			*	��̃J���[�o�b�t�@�𐶐����ĕԂ��܂��B
			*/
			static ColorBuffer* Create( ColorFormat format, uint32 width, uint32 height );

			/**
			* @brief ����
			* @param[in] format				�J���[�o�b�t�@�t�H�[�}�b�g
			* @param[in] width, height		�����A�c��
			* @param[in] buffer				�R�s�[���̃J���[�o�b�t�@
			* @param[in] length				buffer�T�C�Y
			* @returns �������ꂽ�J���[�o�b�t�@�B���s����NULL
			* @details
			*	�J���[�o�b�t�@�𐶐����ĕԂ��܂��B
			*/
			static ColorBuffer* Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length );

			/**
			* @brief �J��
			* @details
			*	�J���[�o�b�t�@���J�����܂��B
			*/
			virtual void Release( );

			/**
			* @}
			*/


		protected:
			ColorFormat		m_Format;			//!< �t�H�[�}�b�g
			uint32			m_Width;			//!< ����
			uint32			m_Height;			//!< �c��
			byte*			m_Buffer;			//!< �o�b�t�@
			uint64			m_BufferSize;		//!< �o�b�t�@�T�C�Y

		};


	}
}