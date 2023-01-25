#pragma once

class Easing final
{
private:
	Easing() = default;
	~Easing() = default;

public: //ÉÅÉìÉoä÷êî
	static inline float easeIn(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time + nowPos;
	}

	static inline float easeOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	static inline float easeInOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		if (maxTime / 2.0f < time) return maxTime / 2.0f * time * time + nowPos;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	static inline float easeInBack(float time, float maxTime, float maxPos, float nowPos, float back = 1.70158f) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time * ((back + 1) * time - back) + nowPos;
	}

	static inline float easeOutBack(float time, float maxTime, float maxPos, float nowPos, float back = 1.70158f) {
		maxPos -= nowPos;
		time /= maxTime;
		time -= 1;

		return maxPos * (time * time * ((back + 1) * time + back) + 1) + nowPos;
	}
};

