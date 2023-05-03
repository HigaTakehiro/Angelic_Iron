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
	/// �X�R�A�����Z
	/// </summary>
	/// <param name="score">���Z����X�R�A</param>
	void AddScore(int32_t score) { score += score; }

private: //�����o�ϐ�
	//�X�R�A
	int32_t score_;
	//�ȑO�̃X�R�A
	int32_t preScore_;

	std::unique_ptr<Sprite> scoreNumber_[6];
};