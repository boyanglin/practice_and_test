// bind example
#include <iostream>     // std::cout
#include <functional>   // std::bind

class GameCharacter; // as before

int defaultHealthCalc(const GameCharacter& gc)
{
	return 3;
} // as before

class GameCharacter
{
public:
	typedef std::function<int(const GameCharacter&)> HealthCalcFunc;

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
		: healthFunc(hcf)
	{
	}

	int healthValue() const
	{
		return healthFunc(*this);
	}

private:
	HealthCalcFunc healthFunc;
};

short calcHealth(const GameCharacter&)
{
	return 5;
}// health calculation


struct HealthCalculator
{ // class for health
	int operator()(const GameCharacter&) const // calculation function
	{
		return 10;
	} // objects
};

class GameLevel
{
public:
	float health(const GameCharacter&) const
	{
		return 1.23;
		// health calculation
	}

}; // non-int return type

class EvilBadGuy : public GameCharacter
{ // as before
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf)
	{
	}
};

class EyeCandyCharacter : public GameCharacter
{ // another character
public:
	explicit EyeCandyCharacter(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf)
	{
	}

	// type; assume same
}; // constructor as

void test()
{
	using namespace std::placeholders;
	// EvilBadGuy
	EvilBadGuy ebg1(calcHealth); // character using a
	std::cout << ebg1.healthValue() << std::endl;
	// health calculation
	// function

	HealthCalculator a;
	EyeCandyCharacter ecc1(HealthCalculator()); // character using a
	ecc1.healthValue();



	// health calculation
	// function object
	GameLevel currentLevel;

	EvilBadGuy ebg2( // character using a
					std::bind(&GameLevel::health, // health calculation
					currentLevel, // member function;
					_1) // see below for details
					);
	std::cout << ebg2.healthValue() << std::endl;

	EyeCandyCharacter ecc2(std::bind(&GameLevel::health, // health calculation
		currentLevel, // member function;
		_1) // see below for details
		);

	ecc2.healthValue();
}