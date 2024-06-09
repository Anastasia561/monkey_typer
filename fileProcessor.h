#pragma once

#include <set>
#include <string>
#include <fstream>

auto saveToFile(const std::set<int> &bestScores, const std::string &fileName) -> void;

auto readFromFile(std::set<int> &bestScores, const std::string &fileName) -> void;

auto saveWordsToFile(std::vector<ComplexText> &texts, const std::string &fileName) -> void;

auto savePositionsToFile(std::vector<ComplexText> &texts, const std::string &fileName) -> void;

auto readPositionsFromFile(const std::string &fileName) -> std::vector<std::pair<int, int>>;

auto saveIntsTofile(int score, int charSize, const std::string &fileName) -> void;

auto readScoreFromFile(const std::string &fileName) -> int;

auto readCharSizeFromFile(const std::string &fileName) -> int;
