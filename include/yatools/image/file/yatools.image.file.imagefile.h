#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @class ImageFile
			* @brief �摜�t�@�C��
			* @details
			*	�摜�t�@�C�����N���X�ł��B
			*/
			class YATOOLS_IMPORT ImageFile
			{
			public:
				/**
				* @name �擾
				* @{
				*/
				/**
				* @brief �J���[�o�b�t�@�擾
				* @returns						�摜�t�@�C���S�̂�\���J���[�o�b�t�@
				* @details
				*	�摜�t�@�C���̑S�̂�\���J���[�o�b�t�@�𐶐����Ď擾���܂��B
				*/
				virtual ColorBuffer* GetColorBuffer( void ) = 0;

				/**
				* @brief �����擾
				* @returns						�摜����
				* @details
				*	�摜�t�@�C���̉������擾���܂��B
				*/
				virtual uint32 GetWidth( void ) = 0;

				/**
				* @brief �c���擾
				* @returns						�摜�c��
				* @details
				*	�摜�t�@�C���̏c�����擾���܂��B
				*/
				virtual uint32 GetHeight( void ) = 0;

				/**
				* @brief �J���[�t�H�[�}�b�g�擾
				* @returns						�J���[�t�H�[�}�b�g
				* @details
				*	�摜�t�@�C���̃J���[�t�H�[�}�b�g���擾���܂��B
				*/
				virtual ColorFormat GetFormat( void ) = 0;

				/**
				* @}
				*/


			protected:
				/**
				* @name �R���X�g���N�^/�f�X�g���N�^
				* @{
				*/
				/**
				* @brief �f�t�H���g�R���X�g���N�^
				* @details
				*	�f�t�H���g�R���X�g���N�^�ł��B
				*/
				ImageFile( void );

				/**
				* @brief �R�s�[�R���X�g���N�^
				* @param[ref] source			�R�s�[��
				* @details
				*	�R�s�[�R���X�g���N�^�ł��B
				*/
				ImageFile( ImageFile& source );

				/**
				* @brief �f�X�g���N�^
				* @details
				*	�f�X�g���N�^�ł��B
				*/
				virtual ~ImageFile( void );

				/**
				* @}
				*/

			};

		}
	}
}
