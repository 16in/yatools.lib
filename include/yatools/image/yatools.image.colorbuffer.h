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
			* @name �s�N�Z������
			* @{
			*/
			/**
			* @brief �s�N�Z���T�C�Y�擾
			* @returns						1�s�N�Z��������̃o�C�g��
			* @details
			*	�J���[�o�b�t�@��1�s�N�Z��������̃o�C�g�����擾���܂��B
			*/
			uint64 GetPixelSize( void );

			/**
			* @brief �s�N�Z���ݒ�
			* @param[in] x, y				���W
			* @param[in] pixel				�ݒ肷��J���[���i�[����Ă���̈�̐擪�|�C���^
			* @param[in] length				color���w���|�C���^�̗̈�T�C�Y
			* @retval true					�ݒ�ɐ���
			* @retval false					�ݒ�Ɏ��s
			* @details
			*	�w����W�̃s�N�Z���ɑ΂��ăs�N�Z���J���[��ݒ肵�܂��B
			*/
			bool SetPixel( uint32 x, uint32 y, uintptr pixel, uint64 length );

			/**
			* @brief �s�N�Z���ݒ�
			* @param[in] x, y				�ݒ�J�n�擪���W
			* @param[in] pixels				�ݒ肷��J���[���i�[����Ă���̈�̐擪�|�C���^
			* @param[in] length				�s�N�Z���̐ݒ�͈�
			* @retval true					�ݒ�ɐ���
			* @retval false					�ݒ�Ɏ��s
			* @details
			*	x, y�Ŏw�肳�����W�̃s�N�Z����擪�Ƃ��Alength/GetPixelSize()�����̃s�N�Z����pixels�̓��e�ŕύX���܂��B
			*/
			bool SetPixels( uint32 x, uint32 y, uintptr pixels, uint64 length );

			/**
			* @brief �s�N�Z���A�h���X�擾
			* @param[in] x, y				���W
			* @returns						���W�̃s�N�Z�����i�[����Ă���̈�̐擪�|�C���^
			* @retval NULL					�擾�Ɏ��s
			* @details
			*	�w����W�̃s�N�Z�����i�[����Ă���̈�̐擪�|�C���^���擾���܂��B	\n
			*	�擾�ɐ��������ꍇ�A���Ȃ��Ƃ��u�߂�l + GetPixelSize()�v�̗̈�͗L���ł��B
			*/
			uintptr GetPixelAddress( uint32 x, uint32 y );

			/**
			* @brief �s�N�Z���u���b�N�ݒ�
			* @param[in] x, y				�u���b�N������W
			* @param[in] width, height		���������u���b�N�T�C�Y
			* @param[in] blocks				���������u���b�N���e��ێ�����̈�̐擪�|�C���^
			* @param[in] length				blocks�̗̈�T�C�Y
			* @retval true					����
			* @retval false					���s
			* @details
			*	�J���[�o�b�t�@���̋�`�̈��ݒ肵�܂��B
			*/
			bool SetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blocks, uint64 length );

			/**
			* @brief �s�N�Z���u���b�N�ݒ�
			* @param[in] x, y				�u���b�N������W
			* @param[in] blockBuffer		������������e��ێ�����J���[�o�b�t�@	\n
			*								�J���[�t�H�[�}�b�g������ł���K�v������܂��B
			* @retval true					����
			* @retval false					���s
			* @details
			*	�J���[�o�b�t�@���̋�`�̈��ݒ肵�܂��B
			*/
			bool SetPixelBlock( uint32 x, uint32 y, ColorBuffer* blockBuffer );

			/**
			* @brief �s�N�Z���u���b�N�擾
			* @param[in] x, y				�擾�J�n������W
			* @param[in] width, height		�擾�����A�c��
			* @returns						�s�N�Z���u���b�N�S�̂̃J���[�o�b�t�@
			* @retval NULL					���s
			* @details
			*	�J���[�o�b�t�@���̋�`�����擾���܂��B
			*/
			ColorBuffer* GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height );

			/**
			* @brief �s�N�Z���u���b�N�擾
			* @param[in] x, y				�擾�J�n������W
			* @param[in] width, height		�擾�����A�c��
			* @param[in] blockBuffer		�s�N�Z���u���b�N�i�[��
			* @param[in] length				blockBuffer�̒���	\n
			*								�Œ�ł�width * height * GetPixelSize()���K�v�ł��B
			* @retval true					����
			* @retval false					���s
			* @details
			*	�J���[�o�b�t�@���̋�`�����擾���܂��B
			*/
			bool GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blockBuffer, uint64 length );

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
			uint64			m_PixelSize;		//!< 1�s�N�Z��������̃T�C�Y

		};


	}
}