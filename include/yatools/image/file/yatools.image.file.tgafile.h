#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{


			/**
			* @enum TgaImageType
			* @brief TGA�C���[�W�^�C�v�񋓑�
			* @details
			*	TGA�̃C���[�W�^�C�v�񋓑̂ł��B	\n
			*	TgaHeader.ImageType����肤��l�ł��B
			*/
			enum TgaImageType
			{
				TGA_NO_IMAGE = 0,					//!< �摜�Ȃ�
				TGA_COLOR_MAP = 1,					//!< �J���[�}�b�v
				TGA_TRUE_COLOR = 2,					//!< �t���J���[
				TGA_GRAY_SCALE = 3,					//!< �O���[�X�P�[��
				TGA_COLOR_MAP_RLE = 9,				//!< �J���[�}�b�v ���������O�X
				TGA_TRUE_COLOR_RLE = 10,			//!< �t���J���[ ���������O�X
				TGA_GRAY_SCALE_RLE = 11,			//!< �O���[�X�P�[�� ���������O�X
			};

			/**
			* @enum TgaImageDirection
			* @brief TGA�C���[�W�i�[����
			* @details
			*	TGA�̃C���[�W�r�b�g���ǂ̕����Ŋi�[����Ă��邩��\���܂��B	\n
			*	TgaHeader.Descriptor.Direction����肤��l�ł��B
			*/
			enum TgaImageDirection
			{
				TGA_IMAGE_LEFT_DOWN = 0,			//!< �������E��
				TGA_IMAGE_LEFT_TOP = 1,				//!< ���と�E��
				TGA_IMAGE_RIGHT_DOWN = 2,			//!< �E��������
				TGA_IMAGE_RIGHT_TOP = 3,			//!< �E�と����
			};


#pragma pack( 1 )

			/**
			* @struct TgaColorMapSpecification
			* @brief �J���[�}�b�v�d�l�\����
			* @details
			*	TGA�J���[�}�b�v�Ɋւ���d�l���ł��B
			*/
			struct TgaColorMapSpecification
			{
				uint16	FirstEntryIndex;			//!< �J���[�}�b�v�ŏ��̃G���g���[�܂ł̃C���f�b�N�X
				uint16	Length;						//!< �J���[�}�b�v��
				uint8	EntrySize;					//!< �J���[�}�b�v�v�f�T�C�Y(bpp)
			};

			/**
			* @struct TgaColorMapSpecification
			* @brief �摜�d�l�\����
			* @details
			*	TGA�摜�Ɋւ���d�l���ł��B
			*/
			struct TgaImageSpecification
			{
				uint16	XOrigin;					//!< X���W
				uint16	YOrigin;					//!< Y���W
				uint16	Width;						//!< ����
				uint16	Height;						//!< �c��
				uint8	PixelDepth;					//!< �s�N�Z���[�x

				struct
				{
					uint8	AlphaDepth : 4;			//!< �A���t�@�[�x���
					uint8	Direction : 2;			//!< �������
					uint8	unuse : 2;
				} Descriptor;
			};

			/**
			* @struct TgaHeader
			* @brief TGA�t�@�C���w�b�_
			* @details
			*	TGA�t�@�C���w�b�_�\���ł��B
			*/
			struct TgaHeader
			{
				uint8	IdFieldLength;				//!< ID�t�B�[���h��
				uint8	ColorMapType;				//!< �J���[�}�b�v�^�C�v
				uint8	ImageType;					//!< �摜�^�C�v

				//! �J���[�}�b�v�d�l
				TgaColorMapSpecification ColorMapSpecification;

				//! �摜�d�l
				TgaImageSpecification ImageSpecification;
			};

			/**
			* @struct TgaFooter
			* @brief TGA�t�@�C���t�b�^�[
			* @details
			*	TGA�t�@�C���t�b�^�[�\���ł��B
			*/
			struct TgaFooter
			{
				uint32	ExtensionOffset;			//!< TgaExtension�ւ̃I�t�Z�b�g
				uint32	DeveloperAreaOffset;		//!< DeveloperArea�ւ̃I�t�Z�b�g
				char	Signature[ 18 ];			//!< 'TRUEVISION-XFILE.\0'
			};

			/**
			* @struct TgaExtension
			* @brief TGA�g���̈�
			* @details
			*	TGA�t�@�C���̊g���f�[�^�\���ł��B
			*/
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
				* @name �o�C�i������
				* @{
				*/
				/**
				* @brief �t�@�C���w�b�_�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							TGA�t�@�C���w�b�_�\����
				* @details
				*	�t�@�C���w�b�_���擾���܂��B
				*/
				static TgaHeader* GetHeader( uintptr buffer, uint64 length );

				/**
				* @brief �t�@�C���t�b�^�[�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							TGA�t�@�C���t�b�^�[�\����
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�t�@�C���t�b�^�[���擾���܂��B
				*/
				static TgaFooter* GetFooter( uintptr buffer, uint64 length );

				/**
				* @brief ImageID�t�B�[���h�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							ImageID�t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�C���[�WID�t�B�[���h���擾���܂��B
				*/
				static uintptr GetImageIdField( uintptr buffer, uint64 length );

				/**
				* @brief �J���[�}�b�v�t�B�[���h�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�J���[�}�b�v�t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�J���[�}�b�v�t�B�[���h���擾���܂��B		\n
				*	�J���[�}�b�v�̏����̓w�b�_���Q�Ƃ��Ă��������B
				*/
				static uintptr GetColorMapField( uintptr buffer, uint64 length );

				/**
				* @brief �摜�t�B�[���h�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�摜�t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�摜�t�B�[���h���擾���܂��B			\n
				*	�摜�t�B�[���h�̏��̓w�b�_���Q�Ƃ��Ă��������B
				*/
				static uintptr GetImageFile( uintptr buffer, uint64 length );

				/**
				* @brief �g�����t�B�[���h�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�g�����t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�g�����t�B�[���h���擾���܂��B
				*/
				static TgaExtension* GetExtensionField( uintptr buffer, uint64 length );

				/**
				* @brief �J���җ̈�t�B�[���h�擾
				* @param[in] buffer					TGA�t�@�C�����i�[�ς݂̃������̈�
				* @param[in] length					buffer�T�C�Y
				* @returns							�J���җ̈�t�B�[���h�̐擪�|�C���^
				* @retval NULL						���݂��Ȃ�
				* @details
				*	�J���җ̈�t�B�[���h���擾���܂��B
				*/
				static uintptr GetDeveloperAreaField( uintptr buffer, uint64 length );

				/**
				* @}
				*/


			};

		}
	}
}
