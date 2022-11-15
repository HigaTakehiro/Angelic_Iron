#pragma once

class Easing final
{
private:
	Easing() = default;
	~Easing() = default;
	Easing(const Easing & obj) = delete;
	Easing& operator=(const Easing & obj) = delete;

public: //Ã“Iƒƒ“ƒoŠÖ”
	static Easing* GetIns() {
		static Easing instans;
		return &instans;
	}

public: //ƒƒ“ƒoŠÖ”
	inline float easeIn(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time + nowPos;
	}

	inline float easeOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	inline float easeInOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		if (maxTime / 2.0f < time) return maxTime / 2.0f * time * time + nowPos;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	inline float easeInBack(float time, float maxTime, float maxPos, float nowPos, float back = 1.70158f) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time * ((back + 1) * time - back) + nowPos;
	}

	inline float easeOutBack(float time, float maxTime, float maxPos, float nowPos, float back = 1) {
		maxPos -= nowPos;
		time = time / maxTime - 1;

		return maxPos * (time * time * ((back + 1) * time + back) + 1) + nowPos;
	}

	inline float easeInOutBack() {

	}
};

