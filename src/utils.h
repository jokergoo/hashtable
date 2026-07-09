#ifndef UTILS_H
#define UTILS_H

#include <Rcpp.h>

void validate_keys(Rcpp::CharacterVector keys, bool check_na = true, bool check_empty = true, bool check_duplicate = true);

#endif
