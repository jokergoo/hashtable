#include <Rcpp.h>
#include "utils.h"

// [[Rcpp::export]]
void validate_keys(Rcpp::CharacterVector keys, bool check_na, bool check_empty, bool check_duplicate) {
    int n = keys.size();
    std::unordered_set<SEXP> seen;
    seen.reserve(n);
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);

        if(check_na && name == NA_STRING) {
            Rcpp::stop("Invalid key at position %d: NA (missing value)", i + 1);
        }
        
        if(check_empty && (name == R_NilValue || LENGTH(name) == 0)) {
            Rcpp::stop("Invalid key at position %d: empty string", i + 1);
        }
        
        if(check_duplicate) {
            if(seen.find(name) != seen.end()) {
                Rcpp::stop("Duplicate key at position %d: '%s'", i + 1, CHAR(name));
            }
            seen.insert(name);
        }
    }
}

