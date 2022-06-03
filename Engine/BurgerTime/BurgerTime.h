#pragma once

class BurgerTime
{
public:
	BurgerTime() = default;
	~BurgerTime() = default;
	BurgerTime(const BurgerTime& other) = delete;
	BurgerTime(BurgerTime&& other) = delete;
	BurgerTime& operator=(const BurgerTime& other) = delete;
	BurgerTime& operator=(BurgerTime&& other) = delete;

	void Load() const;

private:

};

