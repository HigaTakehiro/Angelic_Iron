#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "Player.h"

class Player;

class UIManager
{
public: //�\����

	enum class UIType {
		Back,
		HP,
		Bullet,
		Anime
	};

	enum class ScoreNumber {
		zero = 64 * 0,
		one = 64 * 1,
		two = 64 * 2,
		three = 64 * 3,
		four = 64 * 4,
		five = 64 * 5,
		six = 64 * 6,
		seven = 64 * 7,
		eight = 64 * 8,
		nine = 64 * 9
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
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(bool isPause, Player* player);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(bool isPause, Player* player);

	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="score">�X�R�A</param>
	void SetScore(int32_t score) { score_ = score; }

private: //�����o�֐�
	/// <summary>
	/// n�̈ʂ̐����𔻒肷��
	/// </summary>
	/// <param name="score">���肵�����X�R�A</param>
	/// <param name="place">���肵�����X�R�A�̈�</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

private: //�萔
	//�A�j���[�V��������
	static const int32_t animeTime = 20;

	//�{���U������
	static const int32_t bombTime = 60 * 5;

private: //�����o�ϐ�
	//�S�Ă�UI
	std::list<UIData> allUI_;
	//�S�Ẵ{�^��
	std::list<ButtonData> allButton_;

	//UI
	//�X�R�A�e�L�X�g
	std::unique_ptr<Sprite> scoreSprite_ = nullptr;
	//�X�R�A����
	std::unique_ptr<Sprite> scoreNumber_[6] = {};
	//�{���U���^�C�}�[����
	std::unique_ptr<Sprite> bombTimerNumber_[3] = {};

	//�X�R�A
	int32_t score_;
};