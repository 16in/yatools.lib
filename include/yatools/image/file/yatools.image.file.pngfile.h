#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @struct PngInfomation
			* @brief PNG�t�@�C�����
			* @details
			*	PNG�t�@�C���̉摜�`�����N���ł��B
			*/
			struct PngInfomation
			{
				uint32		Width;			//!< ����
				uint32		Height;			//!< �c��
				ColorFormat	ColorFormat;	//!< �J���[�o�b�t�@�̑Ή��t�H�[�}�b�g\n�J���[�o�b�t�@���Ή��̏ꍇ��Unknown

				// libPng�l�C�e�B�u�̒l
				uint32		Format;			//!< �t�H�[�}�b�g
				uint32		Flags;			//!< �r�b�g�}�X�N�t���O
				uint32		ColorMapCount;	//!< �J���[�}�b�v��
			};


			/**
			* @class PngFile
			* @brief PNG�t�@�C��
			* @details
			*	PNG�t�@�C���N���X�ł��B
			*/
			class PngFile
			{
			public:
				/**
				* @name �o�C�i������
				* @{
				*/
				/**
				* @brief PNG�t�@�C�����擾
				* @param[int,out] infomation		PNG�t�@�C�����i�[��
				* @param[in] buffer					PNG�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @retval true						�擾�ɐ���
				* @retval false						�擾�Ɏ��s
				* @details
				*	��������ɓW�J����Ă���PNG�t�@�C���̏����擾���܂��B
				*/
				static bool GetInfomation( PngInfomation* infomation, uintptr buffer, uint64 length );

				/**
				* @brief �J���[�o�b�t�@�擾
				* @param[in] buffer					PNG�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�������ꂽ�J���[�o�b�t�@
				* @retval NULL						�����Ɏ��s
				* @details
				*	PNG�摜���J���[�o�b�t�@�����܂��B
				*/
				static ColorBuffer* GetColorBuffer( uintptr buffer, uint64 length );

				/**
				* @brief BMP�t�@�C�������o��
				* @param[in] colorBuffer			PNG�t�@�C���Ƃ��ď����o���J���[�o�b�t�@
				* @param[in, out] buffer			�����o���惁�����̈�	\n
				*									NULL�̏ꍇ�͖߂�l���K�v�ȗ̈�T�C�Y��Ԃ��܂��B
				* @param[in] length					buffer�Ɋi�[�\�ȃo�C�g��
				* @returns							buffer�ɏ����o���ꂽ�o�C�g��		\n
				*									buffer��NULL�̏ꍇ�͕K�v�ȃo�C�g��
				* @retval 0							colorBuffer��PNG�t�@�C���ɏ����o���\�Ȍ`���ł͂Ȃ�
				* @details
				*	�J���[�o�b�t�@��PNG�t�@�C���Ƃ��ă������̈�ɏ����o���܂��B		\n
				*	�����o���\�ȃJ���[�o�b�t�@�̃t�H�[�}�b�g�͎��̂Ƃ���ł��B	\n
				*	�EColorFormatR8G8B8		\n
				*	�EColorFormatA8R8G8B8	\n
				*	\n
				*	buffer��NULL�̏ꍇ�AColorBuffer�̏����o���ɕK�v�ȃo�C�g����Ԃ��܂��B
				*/
				static uint64 WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length );

			private:
				//! �Ăяo���J�n
				static bool OpenReadPngOnMemory( uintptr image, uintptr buffer, uint64 length );

				//! ���ݒ�
				static void SetupInfomation( PngInfomation* info, uintptr image );

				/**
				* @}
				*/
				

			};


		}
	}
}
