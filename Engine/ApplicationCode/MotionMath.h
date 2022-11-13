#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

class MotionMath
{
private:
	MotionMath() = default;
	~MotionMath() = default;
	MotionMath(const MotionMath& obj) = delete;
	MotionMath& operator=(const MotionMath& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static MotionMath* GetIns();

public: //���w��p�񋓌^
	enum Axis {
		X,
		Y,
		Z
	};

public: //�����o�֐�
	/// <summary>
	/// �~�^��
	/// </summary>
	/// <param name="centerPos">���S���W</param>
	/// <param name="rotPos">��]��������W</param>
	/// <param name="angle">�p�x</param>
	/// <param name="length">���S���W�Ƃ̋���</param>
	/// <param name="axis">�ǂ̎��𒆐S�ɉ�]�����邩</param>
	/// <returns>���W</returns>
	Vector3 CircularMotion(const Vector3& centerPos, const Vector3& rotPos, float angle, const float length, const Axis axis);
};
