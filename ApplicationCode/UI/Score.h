#pragma once
#include "Sprite.h"
#include "ImageManager.h"

class Score final
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Score() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Score() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	Score(const Score& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	Score& operator=(const Score& obj) = delete;

public:
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

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Score* GetIns();

public: //�����o�֐�
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
	/// n�̈ʂ̐����𔻒肷��
	/// </summary>
	/// <param name="score">���肵�����X�R�A</param>
	/// <param name="place">���肵�����X�R�A�̈�</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

	/// <summary>
	/// �X�R�A�����Z
	/// </summary>
	/// <param name="score">���Z����X�R�A</param>
	void AddScore(int32_t score);

	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="score">�Z�b�g����X�R�A</param>
	void SetScore(int32_t score) { score_ = score; }
	
	/// <summary>
	/// �X�R�A���擾
	/// </summary>
	/// <returns></returns>
	int32_t GetScore() { return score_; }

private: //�����o�֐�
	/// <summary>
	/// �X�R�A���Z���o
	/// </summary>
	void AddScorePerformance();

private: //�ÓI�����o�ϐ�
	//�X�R�A���Z���o����
	const static int32_t scoreAddTime = 60;
	//�X�R�A
	static int32_t score_;

private: //�����o�ϐ�
	//�X�R�A���[�����o�p���W
	float scoreRollPosX_[6];
	//���Z����X�R�A
	int32_t addScore_;
	//���Z����X�R�A�̃A���t�@�l
	float addScoreAlpha_;
	//�X�R�A���Z���o�^�C�}�[
	int32_t scoreAddTimer_;
	//�X�R�A�摜
	std::unique_ptr<Sprite> scoreNumber_[6];
	//�v���X�摜
	std::unique_ptr<Sprite> plus_;
	//���Z�X�R�A�摜
	std::unique_ptr<Sprite> addScoreNumber_[4];
	//�X�R�A���Z�t���O
	bool isAddScore_;
};