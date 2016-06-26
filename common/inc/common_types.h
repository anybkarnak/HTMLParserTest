//
// Created by karnak on 26.06.16.
//

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <string>
#include <memory>
#include <set>
#include <vector>


struct Entity
{
    std::string link;
    std::string status;
};

typedef std::vector<Entity> EntitiesList;

enum class ErrorCode
{
    SUCCESS = 1,
    ERROR = 0
};

#endif //HTML_PARSER_TEST_COMMON_TYPES_H
