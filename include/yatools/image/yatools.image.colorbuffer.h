#pragma once

#include "yatools.image.type.h"


namespace yatools
{
	namespace image
	{

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
			/**
			* @name �ϊ�
			* @{
			*/
			/**
			* @brife �t�H�[�}�b�g�ϊ�
			* @param[in] format				�V�����t�H�[�}�b�g
			* @returns						�V�����t�H�[�}�b�g�ɕϊ����ꂽ�J���[�o�b�t�@
			* @details
			*	�V�����t�H�[�}�b�g�ɃJ���[�o�b�t�@��ϊ����܂��B
			*/
			ColorBuffer* Convert( ColorFormat format );

			/**
			* @}
			*/
			/**
			* @name �s�N�Z������
			* @{
			*/

			bool SetPixel( uint32 x, uint32 y, float r, float g, float b, float a = 1.0f );

			/**
			* @}
			*/


		protected:
			/**
			* @name �R���X�g���N�^/�f�X�g���N�^
			* @{
			*/
			/**
			* @brief �R���X�g���N�^
			* @details
			*	�f�t�H���g�R���X�g���N�^�ł��B
			*/
			ColorBuffer( void );

			/**
			* @biref �R�s�[�R���X�g���N�^
			* @param[ref] source			�R�s�[��
			* @details
			*	�R�s�[�R���X�g���N�^�ł��B
			*/
			ColorBuffer( ColorBuffer& source );

			/**
			* @brief �f�X�g���N�^
			* @details
			*	�f�X�g���N�^�ł��B
			*/
			virtual ~ColorBuffer( void );

			/**
			* @}
			*/


		protected:
			ColorFormat		m_Format;			//!< �t�H�[�}�b�g
			uint32			m_Width;			//!< ����
			uint32			m_Height;			//!< �c��
			uintptr			m_Buffer;			//!< �o�b�t�@
			uint64			m_BufferSize;		//!< �o�b�t�@�T�C�Y
			uint			m_PixelSize;		//!< 1�s�N�Z��������̃T�C�Y

		};


	}
}