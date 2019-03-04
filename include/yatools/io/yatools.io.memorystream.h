#pragma once

#include "yatools.io.stream.h"


namespace yatools
{
	namespace io
	{

		/**
		* @class MemoryStream
		* @brief �������X�g���[��
		* @details
		*	��������̃o�b�t�@�ɑ΂�����o�̓X�g���[���ł��B	\n
		*	���̃X�g���[���͊m�ۍς݂̗̈�ɑ΂��Ă̓ǂݏ������s���܂����A�T�C�Y��ύX���邱�Ƃ͂ł��܂���B
		*/
		class YATOOLS_IMPORT MemoryStream : Stream
		{
		public:
			/**
			* @name �R���X�g���N�^/�f�X�g���N�^
			* @{
			*/
			/**
			* @brief �R���X�g���N�^
			* @param[in] buffer			�������̏������
			* @param[in] length			buffer�̒���
			* @details
			*	�R���X�g���N�^�ł��B
			*/
			MemoryStream( uintptr buffer, int64 length )
			{
				m_Buffer = buffer;
				m_Length = length;
				m_Position = 0;
			}

			/**
			* @}
			*/
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
			virtual int64 Seek( int64 offset, SeekBase base );

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
			virtual int64 SetLength( int64 length )
			{
				return -1;
			}

			/**
			* @brief �X�g���[���T�C�Y�擾
			* @returns					�X�g���[���T�C�Y
			* @details
			*	�X�g���[���T�C�Y���擾���܂��B
			*/
			virtual int64 GetLength( void )
			{
				return m_Length;
			}

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
			virtual int32 Read( uintptr buffer, int32 size );

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
			virtual int32 Write( uintptr buffer, int32 size );

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

		protected:
			uintptr m_Buffer;			//!< �Ǘ��o�b�t�@
			int64	m_Length;			//!< �o�b�t�@��
			int64	m_Position;			//!< ���݈ʒu

		};

	}
}
