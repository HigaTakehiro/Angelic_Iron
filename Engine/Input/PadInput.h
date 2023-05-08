#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class PadInput final
{
public: //enum
	enum class PadButton {
		Button_A,
		Button_B,
		Button_X,
		Button_Y,
		Button_LB,
		Button_RB,
		Button_View,
		Button_Menu,
		Button_LS,
		Button_RS
	};

	enum class PadCrossKey {
		CrossKey_Neutral = -1,
		CrossKey_Up = 0,
		CrossKey_UpperRight = 4500,
		CrossKey_Right = 9000,
		CrossKey_LowerRight = 13500,
		CrossKey_Lower = 18000,
		CrossKey_LowerLeft = 22500,
		CrossKey_Left = 27000,
		CrossKey_UpperLeft = 31500
	};

private: //�G�C���A�X
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PadInput() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PadInput() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	PadInput(const PadInput& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	PadInput& operator=(const PadInput& obj) = delete;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �{�^���������m
	/// </summary>
	bool PushButton(BYTE buttonNumber);

	/// <summary>
	/// �{�^�����������u�Ԃ̂݌��m
	/// </summary>
	bool TriggerButton(BYTE buttonNumber);

	/// <summary>
	/// �\���L�[�������m
	/// </summary>
	bool PushCrossKey(LONG crossKeyNumber);

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static PadInput* GetIns();

private: //�����o�ϐ�
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dinput_;
	//�R���g���[���̃f�o�C�X
	ComPtr<IDirectInputDevice8> devPad_;
	//�R���g���[���̏��
	DIJOYSTATE padState_;
	DIJOYSTATE prePadState_;
	//WindowsAPI
	WinApp* winApp_ = nullptr;
};