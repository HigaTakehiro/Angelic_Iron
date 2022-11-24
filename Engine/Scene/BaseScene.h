#pragma once

class BaseScene
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// XVˆ—
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// I—¹ˆ—
	/// </summary>
	virtual void Finalize() = 0;
};

