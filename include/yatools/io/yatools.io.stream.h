#pragma once

#include "../yatools.type.h"


namespace yatools
{
	namespace io
	{

		/**
		* @class Stream
		* @brief ���o�̓X�g���[��
		* @details
		*	���o�͐���p�̃X�g���[�����N���X�ł��B
		*/
		class YATOOLS_IMPORT Stream
		{
		public:
			/**
			* @enum SeekBase
			* @brief �V�[�N�
			* @details
			*	�V�[�N�̊�ʒu�ł��B
			*/
			enum SeekBase
			{
				Head = 0,		/**< �X�g���[���擪 */
				Current,		/**< ���݈ʒu */
				End				/**< ���[ */
			};

		public:
			/**
			* @name �ʒu�֌W
			* @{
			*/
			/**
			* @brief �V�[�N
			* @param[in] offset			base����̃I�t�Z�b�g�ʒu
			* @param[in] base			�V�[�N�
			* @returns					�ύX��̌��݈ʒu	\n
			*							�ύX��̈ʒu���X�g���[�����[�𒴂��Ă����ꍇ��-1
			* @details
			*	�X�g���[���̌��݈ʒu���w��̈ʒu�֕ύX���܂��B
			*/
			virtual int64 Seek( int64 offset, SeekBase base ) = 0;

			/**
			* @brief ���݈ʒu�ݒ�
			* @param[in] pos			�X�g���[���擪����̈ʒu
			* @returns					�ݒ肳�ꂽ���݈ʒu		\n
			*							pos���X�g���[�����[�𒴂��Ă����ꍇ��-1
			* @details
			*	�X�g���[���̌��݈ʒu���w�肳�ꂽ�ꏊ�֐ݒ肵�܂��B
			*/
			virtual int64 SetPosition( int64 pos );

			/**
			* @brief ���݈ʒu�擾
			* @returns					�X�g���[���̌��݈ʒu
			* @details
			*	�X�g���[���̌��݈ʒu���擾���܂��B
			*/
			virtual int64 GetPosition( void );

			/**
			* @brief �X�g���[���T�C�Y�ݒ�
			* @param[in] length			�V�����ݒ肷��X�g���[���T�C�Y
			* @returns					�ύX��̃X�g���[���T�C�Y
			* @retval -1				�ύX�Ɏ��s
			* @details
			*	�X�g���[���T�C�Y��ݒ肵�܂��B
			*/
			virtual int64 SetLength( int64 length ) = 0;

			/**
			* @brief �X�g���[���T�C�Y�擾
			* @returns					�X�g���[���T�C�Y
			* @details
			*	�X�g���[���T�C�Y���擾���܂��B
			*/
			virtual int64 GetLength( void ) = 0;

			/**
			* @}
			*/
			/**
			* @name �ǂݏ���
			* @{
			*/
			/**
			* @brief �ǂݍ���
			* @param[in,out] buffer				�ǂݍ��݃f�[�^�̊i�[��o�b�t�@
			* @param[in] size					�ǂݍ��ރT�C�Y
			* @returns							buffer�Ɋi�[���ꂽ�f�[�^�T�C�Y
			* @retval -1						�X�g���[�����[
			* @details
			*	�X�g���[���̌��݈ʒu����w��̃o�C�g����ǂݍ��݂܂��B	\n
			*	���Ȃ��Ƃ�buffer��size�Ŏw�肵���o�C�g�����A�̈���m�ۍς݂łȂ��Ă͂����܂���B
			*/
			virtual int32 Read( uintptr buffer, int32 size ) = 0;

			/**
			* @brief 1byte�ǂݍ���
			* @returns							int32�փL���X�g���ꂽ�o�C�g�f�[�^
			* @retval -1						�ǂݍ��݂Ɏ��s
			* @details
			*	�X�g���[���̌��݈ʒu����1�o�C�g�ǂݍ��݂܂��B
			*/
			virtual int32 ReadByte( void );

			/**
			* @brief ��������
			* @param[in] buffer					�������݃f�[�^
			* @param[in] size					�������ރT�C�Y
			* @returns							���ۂɏ������܂ꂽ�T�C�Y	\n
			*									���s����-1
			* @details
			*	�X�g���[���̌��݈ʒu��buffer�Ŏw�肳�ꂽ���e���������݂܂��B
			*/
			virtual int32 Write( uintptr buffer, int32 size ) = 0;

			/**
			* @brief 1byte��������
			* @param[in] byte					�������ރo�C�g�f�[�^
			* @retval true						����
			* @retval false						���s
			* @details
			*	�X�g���[���̌��݈ʒu�֎w�肵���o�C�g�f�[�^���������݂܂��B
			*/
			virtual bool WriteByte( byte byte );

			/**
			* @}
			*/

		};

	}
}
