#pragma once

#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <array>

#include "Macro.h"
#include "StaticObjects.h"
#include "RedBird.h"
#include "YellowBird.h"
#include "BlueBird.h"
#include "BlackBird.h"
#include "World.h"



class LevelManager
{
public:
	LevelManager(std::shared_ptr<World> world);
	~LevelManager() = default;

	//getters
	void getNextLevel(std::vector<std::unique_ptr<Bird>>& birdsVec, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>> &objVec);
	void getSpecificLevel(const int &lvl, std::vector<std::unique_ptr<Bird>>& birdsVec, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>>& objVec);

private:
	std::ifstream m_lvlsFile;
	std::shared_ptr<World> m_world;

	/* private funcs */
	std::deque<std::string> ReadBirds();
	std::deque<std::string> ReadLevel();
	void CreateObj(std::deque<std::string> &objDeq, std::vector<std::unique_ptr<StaticObjects>>& pigsVec, std::vector<std::unique_ptr<StaticObjects>>& objVec);
	std::vector<std::unique_ptr<Bird>> CreateBirds(std::deque<std::string>& objDeq);

	

};

