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
    Entity():link(std::string()), status("in progress"){}
    std::string link;
    std::string status;
    void SetStatus(std::string stat)
    {
        status = stat;
    }
    bool operator<(const Entity& rhs) const { return link<rhs.link; }
};

typedef std::vector<Entity> EntitiesList;

enum class ErrorCode
{
    _SUCCESS = 1,
    _ERROR = 0
};

#endif //HTML_PARSER_TEST_COMMON_TYPES_H
