#include <string>

#ifndef LCS_H
#define LCS_H

std::string randomString(const std::string&, size_t);

std::string lcs(const std::string&, const std::string&);

static std::string lcs(const std::string&, const std::string&, int, int);

#endif