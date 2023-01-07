#pragma once
#include "DirectXSetting.h"

class TextDraw
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�����o�֐�
	void FontHandleCreate();

private: //�ÓI�����o�ϐ�
	//�f�t�H���g�t�H���g�T�C�Y
	static const int defaultFontSize = 64;
	//�f�t�H���g�t�H���g����
	static const int defaultFontWeight = 1000;
	//�f�t�H���g�t�H���g
	static const char* defaultFont;

private: //�����o�ϐ�
	//�t�H���g�T�C�Y
	int fontSize;
	//�t�H���g����
	int fontWeight;
	//�t�H���g�n���h��
	LOGFONT lf;
};

