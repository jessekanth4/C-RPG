#pragma once

#include <string>
#include <vector>

struct Area {
    std::string name;
    std::vector<int> connections;
};

extern const std::vector<Area> worldMap;

void mapMenu(std::size_t& currentArea);
