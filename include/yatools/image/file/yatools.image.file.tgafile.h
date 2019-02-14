#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @struct TgaHeader
			* @brief TGA�t�@�C���w�b�_
			* @details
			*	TGA�t�@�C���w�b�_�\���ł��B
			*/
#pragma pack( 1 )
			struct TgaHeader
			{
				uint8	IdFieldLength;				//!< ID�t�B�[���h��
				uint8	ColorMapType;				//!< �J���[�}�b�v�^�C�v
				uint8	ImageType;					//!< �摜�^�C�v
				uint16	ColorMapFirstEntryIndex;	//!< �J���[�}�b�v�ŏ��̃G���g���[�܂ł̃C���f�b�N�X
				uint16	ColorMapLength;				//!< �J���[�}�b�v��
				uint8	ColorMapEntrySize;			//!< �J���[�}�b�v�v�f�T�C�Y(bpp)
				uint16	XOrigin;					//!< X���W
				uint16	YOrigin;					//!< Y���W
				uint16	Width;						//!< ����
				uint16	Height;						//!< �c��
				uint8	PixelDepth;					//!< �s�N�Z���[�x
				uint8	Attribute : 4;				//!< ����
				uint8	Horizontal : 1;				//!< ������
				uint8	Vertical : 1;				//!< �c����
				uint8	reserve : 2;
			};
#pragma pack( )

			/**
			* @struct TgaFooter
			* @brief TGA�t�@�C���t�b�^�[
			* @details
			*	TGA�t�@�C���t�b�^�[�\���ł��B
			*/
#pragma pack( 1 )
			struct TgaFooter
			{
				uint32	ExtensionOffset;			//!< TgaExtension�ւ̃I�t�Z�b�g
				uint32	DeveloperAreaOffset;		//!< DeveloperArea�ւ̃I�t�Z�b�g
				char	Signature[ 18 ];			//!< 'TRUEVISION-XFILE.\0'
			};
#pragma pack( )

			/**
			* @struct TgaExtension
			* @brief TGA�g���̈�
			* @details
			*	TGA�t�@�C���̊g���f�[�^�\���ł��B
			*/
#pragma pack( 1 )
			struct TgaExtension
			{
				uint16	ExtensionSize;				//!< ���495
				char	AuthorName[ 41 ];			//!< ����Җ�
				char	AuthorComment[ 324 ];		//!< �R�����g
				char	DateTimeStamp[ 12 ];		//!< �^�C���X�^���v
				char	JobID[ 41 ];				//!< �W���uID
				char	JobTime[ 6 ];				//!< �����b�ł̍쐬����
				char	SoftwareID[ 41 ];			//!< �\�t�g�E�F�AID
				char	SoftwareVersion[ 3 ];		//!< �\�t�g�E�F�A�o�[�W����
				uint32	KeyColor;					//!< �L�[�J���[
				float	PixelAspectRatio;			//!< �s�N�Z���A�X�y�N�g��
				float	GammaValue;					//!< �K���}�l
				uint32	ColorCorrectionOffset;		//!< �J���[�R���N�V�����I�t�Z�b�g
				uint32  PostageStampOffset;
				uint32	ScanLineOffset;				//!< �X�L�������C���I�t�Z�b�g
				uint8	AttributesType;				//!< �����^�C�v
			};
#pragma pack( )

			/**
			* @class TgaFile
			* @brief TGA�t�@�C��
			* @details
			*	TGA�t�@�C���N���X�ł��B
			*/
			class YATOOLS_IMPORT TgaFile
			{
			public:
				/**
				* @name �t�@�C���o�C�i��
				* @{
				*/


				/**
				* @}
				*/


			};

		}
	}
}
