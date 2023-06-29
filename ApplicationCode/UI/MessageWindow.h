#pragma once
#include "Sprite.h"
#include "TextDraw.h"

class MessageWindow
{
public: //�񋓌^
	//��O���t�B�b�N
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SMILEFACE,
		OPE_SURPRISEFACE
	};

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MessageWindow() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MessageWindow() = default;

	/// <summary>
	/// ������
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

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�ϐ�
	//�I�y���[�^�ʏ��O���t�B�b�N
	std::unique_ptr<Sprite> opeNormalFace_[3];
	//�I�y���[�^�Ί��O���t�B�b�N
	std::unique_ptr<Sprite> opeSmileFace_[3];
	//�I�y���[�^������O���t�B�b�N
	std::unique_ptr<Sprite> opeSurpriseFace_[3];
	//�e�L�X�g�E�B���h�E
	std::unique_ptr<Sprite> textWindow_;
	//��E�B���h�E
	std::unique_ptr<Sprite> faceWindow_;

};

