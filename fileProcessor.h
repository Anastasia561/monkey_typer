#pragma once

#include <set>
#include <string>
#include <fstream>

auto safeToFile(const std::set<int> &bestScores, std::string fileName) -> void;

auto readFromFile(std::set<int> &bestScores, std::string fileName) -> void;
