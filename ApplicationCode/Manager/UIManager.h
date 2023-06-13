#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"
#include "Vector2.h"

class UIManager
{
public: //�\����

	enum class UIType {
		Back,
		HP,
		Bullet,
		Anime
	};

	struct HPUI {
		bool isHp_ = false;
		int32_t hp_ = 0;
		bool isRight_ = false;
	};

	struct BulletUI {
		bool isBullet_ = false;
		int32_t bulletCount_ = 0;
		bool isRight_ = false;
	};

	struct AnimeUI {
		bool isAnime_ = false;
		float animeSize_ = 0.0f;
		int32_t animeSpeed_ = 0;
		int32_t animeCount_ = 0;
	};

	struct UIData {
		Vector2 pos_;
		Vector2 size_;
		float rot_;
		std::unique_ptr<Sprite> uiSprite_;
		UIType type_;
		bool isPauseView_;
		struct HPUI hpType_;
		struct BulletUI bulletType_;
		struct AnimeUI animeType_;
	};

	struct ButtonData {
		Vector2 pos_;
		Vector2 size_;
		float rot_;
		std::unique_ptr<Button> button_;
		bool isPauseView_;
	};

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIManager() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UIManager() = default;
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="fileName">�ǂݍ��ރt�@�C����</param>
	void Initialize(const std::string fileName);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(bool isPause);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(bool isPause);

private: //�萔
	//�A�j���[�V��������
	static const int32_t animeTime = 20;

private: //�����o�ϐ�
	//�S�Ă�UI
	std::list<std::unique_ptr<UIData>> allUI_;
	//�S�Ẵ{�^��
	std::list<std::unique_ptr<ButtonData>> allButton_;
};