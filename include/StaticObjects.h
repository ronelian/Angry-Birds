#pragma once
#include "Objects.h"



class StaticObjects : public Objects
{
public:
	StaticObjects(std::shared_ptr<World> world, const int& hp = 50, const int& score = 0) : Objects(world, hp), m_score(score) {};
	virtual ~StaticObjects() = default;

	inline int getScore() const { return m_score; }

	//virtual funcs
	virtual void hitState() = 0;

private:
	int m_score;
};

