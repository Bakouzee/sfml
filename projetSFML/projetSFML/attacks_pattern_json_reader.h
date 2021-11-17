#pragma once
#include <vector>
#include "BlackHole.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "AssetsPath.h"

using json = nlohmann::json;

std::vector<AttackPattern> GetAllAttacks();