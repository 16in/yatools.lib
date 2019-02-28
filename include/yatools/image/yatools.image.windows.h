#pragma once

#include "yatools.image.colorbuffer.h"

#ifndef _WIN32
#error This API is Windows only.
#endif
#include <Windows.h>


namespace yatools
{
	namespace image
	{

		/**
		* @class Windows
		* @brief Windows�֌W
		* @details
		*	Windows���L�̌`���Ɋ֘A�Â����I�u�W�F�N�g�̐���N���X�ł��B
		*/
		class YATOOLS_IMPORT Windows
		{
		public:

			/**
			* @brief �J���[�o�b�t�@�擾
			* @param[in] hWnd				�擾���̃E�B���h�E�n���h��
			* @retturns						�������ꂽ�J���[�o�b�t�@
			* @retval NULL					�擾�Ɏ��s
			* @details
			*	�E�B���h�E�n���h���Ŏw�肳�ꂽ�E�B���h�E�S�̂��J���[�o�b�t�@�Ƃ��Ď擾���܂��B
			*/
			static ColorBuffer* GetColorBuffer( HWND hWnd );

			/**
			* @brief �J���[�o�b�t�@�擾
			* @param[in] hDc				�擾����r�b�g�}�b�v���܂܂�Ă���f�o�C�X�R���e�L�X�g
			* @param[in] width, height		�����A�c��
			* @returns						�������ꂽ�J���[�o�b�t�@
			* @retval NULL					�擾�Ɏ��s
			* @details
			*	�f�o�C�X�R���e�L�X�g�̃r�b�g�}�b�v����J���[�o�b�t�@���擾���܂��B
			*/
			static ColorBuffer* GetColorBuffer( HDC hDc, uint32 width, uint32 height );

			/**
			* @brief �J���[�o�b�t�@�擾
			* @param[in] hBitMap			�擾���̃r�b�g�}�b�v�n���h��
			* @returns						�擾���ꂽ�J���[�o�b�t�@
			* @retval NULL					�擾�Ɏ��s
			* @details
			*	�r�b�g�}�b�v�n���h������J���[�o�b�t�@���擾���܂��B
			*/
			static ColorBuffer* GetColorBuffer( HBITMAP hBitMap );

		};

	}
}