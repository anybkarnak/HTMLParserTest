//
// Created by akomandyr on 24.06.16.
//

#ifndef PAGE_SCANNER_H
#define PAGE_SCANNER_H

#include "common_types.h"


class PageScanner
{
public:
    std::string GetResult(const std::string& pageContent, const std::string sample);
    EntitiesList GetPageChildren(const std::string& url) const;
private:
    std::string GetPageContent(const std::string& url) const;
};

typedef std::shared_ptr<PageScanner> PageScannerPtr;
#endif //HTML_PARSER_TEST_PAGE_SCANNER_H
