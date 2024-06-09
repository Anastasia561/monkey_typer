#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "complexText.h"

auto saveToFile(const std::set<int> &bestScores, const std::string &fileName) -> void {
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    for (auto score: bestScores) {
        file << score << " ";
    }
}

auto readFromFile(std::set<int> &bestScores, const std::string &fileName) -> void {
    auto file = std::fstream(fileName);
    for (auto score = std::string(); file >> score;) {
        bestScores.insert(std::stoi(score));
    }
}

auto saveWordsToFile(std::vector<ComplexText> &texts, const std::string &fileName) -> void {
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    for (auto &text: texts) {
        if (text.getFillColor() != sf::Color(0, 71, 100)) {
            file << text.getString() << " ";
        }
    }
}

auto savePositionsToFile(std::vector<ComplexText> &texts, const std::string &fileName) -> void {
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    for (auto &text: texts) {
        if (text.getFillColor() != sf::Color(0, 71, 100)) {
            file << text.getPositionX() << " " << text.getPositionY() << " ";
        }
    }
}

auto readPositionsFromFile(const std::string &fileName) -> std::vector<std::pair<int, int>> {
    auto file = std::fstream(fileName);
    auto result = std::vector<std::pair<int, int>>();
    auto v = std::vector<int>();
    for (auto i = std::string(); file >> i;) {
        v.push_back(std::stoi(i));
    }

    for (auto i = 1; i < v.size(); i += 2) {
        auto pair = std::make_pair(v[i - 1], v[i]);
        result.push_back(pair);
    }

    return result;
}

auto saveIntsTofile(int score, int charSize, const std::string &fileName) -> void {
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    file << score << " " << charSize;
}

auto readScoreFromFile(const std::string &fileName) -> int {
    auto file = std::fstream(fileName);
    auto result = std::vector<int>();
    for (auto i = std::string(); file >> i;) {
        result.push_back(std::stoi(i));
    }
    return result[0];
}

auto readCharSizeFromFile(const std::string &fileName) -> int {
    auto file = std::fstream(fileName);
    auto result = std::vector<int>();
    for (auto i = std::string(); file >> i;) {
        result.push_back(std::stoi(i));
    }
    return result[1];
}
