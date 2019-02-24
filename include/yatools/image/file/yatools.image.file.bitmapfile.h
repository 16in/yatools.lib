#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

#pragma pack( 1 )
			/**
			* @struct BmpHeader
			* @name BMP�t�@�C���w�b�_
			* @details
			*	BMP�t�@�C���w�b�_�\���̂ł��B
			*/
			struct YATOOLS_IMPORT BmpHeader
			{
				union
				{
					uint16 Type;		//!< 'BM'
					char   Kind[ 2 ];	//!< { 'B', 'M' }
				};
				uint32 FileSize;		//!< �t�@�C���T�C�Y
				uint16 reserve00;		//!< �\��̈�
				uint16 reserve01;		//!< �\��̈�
				uint32 OffsetImage;		//!< �摜�̈�I�t�Z�b�g
			};

			/**
			* @struct BmpInfomationHeader
			* @name BMP���w�b�_
			* @details
			*	BMP���w�b�_�\���̂ł��B
			*/
			struct YATOOLS_IMPORT BmpInfomationHeader
			{
				uint32 InfomationSize;	//!< ���w�b�_�T�C�Y
				int32 Width;			//!< ����
				int32 Height;			//!< �c��
				uint16 Plane;			//!< �v���[����
				uint16 BitDepth;		//!< �r�b�g�[�x
				uint32 Compression;		//!< ���k�`��
				uint32 SizeImage;		//!< �摜�T�C�Y
				int32 BppmWidth;		//!< �����𑜓x
				int32 BppmHeight;		//!< �����𑜓x
				uint32 ClrUsed;			//!< �i�[�p���b�g��
				uint32 CirImportant;	//!< �d�v�F��
			};
#pragma pack( )


			/**
			* @class BmpFile
			* @brief BMP�t�@�C��
			* @details
			*	BMP�t�@�C���N���X�ł��B
			*/
			class YATOOLS_IMPORT BmpFile
			{
			public:
				/**
				* @name �o�C�i������
				* @{
				*/
				/**
				* @brief �t�@�C���w�b�_�擾
				* @param[in] buffer					BMP�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							BMP�t�@�C���w�b�_�\����
				* @details
				*	�t�@�C���w�b�_���擾���܂��B
				*/
				static BmpHeader* GetHeader( uintptr buffer, uint64 length );

				/**
				* @brief ���w�b�_�擾
				* @param[in] buffer					BMP�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							BMP���w�b�_�\����
				* @details
				*	���w�b�_���擾���܂��B
				*/
				static BmpInfomationHeader* GetInfomationHeader( uintptr buffer, uint64 length );

				/**
				* @brief �J���[�p���b�g�擾
				* @param[in] buffer					BMP�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�J���[�p���b�g�擪�A�h���X	\n
				*									���݂��Ȃ��ꍇ��NULL
				* @details
				*	�J���[�p���b�g�̐擪�A�h���X���擾���܂��B
				*/
				static uintptr GetColorPalets( uintptr buffer, uint64 length );

				/**
				* @brief �摜�t�B�[���h�擾
				* @param[in] buffer					BMP�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�摜�t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�摜�t�B�[���h���擾���܂��B			\n
				*	�摜�t�B�[���h�̏��̓w�b�_���Q�Ƃ��Ă��������B
				*/
				static uintptr GetImageField( uintptr buffer, uint64 length );

				/**
				* @brief �J���[�o�b�t�@�擾
				* @param[in] buffer					BMP�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�������ꂽ�J���[�o�b�t�@
				* @retval NULL						�����Ɏ��s
				* @details
				*	�摜�t�B�[���h���w�b�_���ɏ]���ăJ���[�o�b�t�@�����܂��B	\n
				*	���k�`���̏ꍇ�A���̊֐��͎��s���܂��B
				*/
				static ColorBuffer* GetColorBuffer( uintptr buffer, uint64 length );

				/**
				* @brief BMP�t�@�C�������o��
				* @param[in] colorBuffer			BMP�t�@�C���Ƃ��ď����o���J���[�o�b�t�@
				* @param[in, out] buffer			�����o���惁�����̈�	\n
				*									NULL�̏ꍇ�͖߂�l���K�v�ȗ̈�T�C�Y��Ԃ��܂��B
				* @param[in] length					buffer�Ɋi�[�\�ȃo�C�g��
				* @returns							buffer�ɏ����o���ꂽ�o�C�g��		\n
				*									buffer��NULL�̏ꍇ�͕K�v�ȃo�C�g��
				* @retval 0							colorBuffer��BMP�t�@�C���ɏ����o���\�Ȍ`���ł͂Ȃ�
				* @details
				*	�J���[�o�b�t�@��BMP�t�@�C���Ƃ��ă������̈�ɏ����o���܂��B		\n
				*	�����o���\�ȃJ���[�o�b�t�@�̃t�H�[�}�b�g�͎��̂Ƃ���ł��B	\n
				*	�EColorFormatR8G8B8		\n
				*	�EColorFormatA8R8G8B8	\n
				*	\n
				*	buffer��NULL�̏ꍇ�AColorBuffer�̏����o���ɕK�v�ȃo�C�g����Ԃ��܂��B
				*/
				static uint64 WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length );

				/**
				* @}
				*/

			private:
				//! 32bit�J���[�擾
				static ColorBuffer* GetColorBuffer32( uintptr buffer, uint64 length );

				//! 24bit�J���[�擾
				static ColorBuffer* GetColorBuffer24( uintptr buffer, uint64 length );

				//! �p���b�g�J���[�擾
				static ColorBuffer* GetColorBufferPalet( uintptr buffer, uint64 length );

			};

		}
	}
}
