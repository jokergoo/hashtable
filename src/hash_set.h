#ifndef HASH_SET_H
#define HASH_SET_H

#include <Rcpp.h>
#include <unordered_set>

#ifdef Rf_hash
    struct CHARSXPHash {
        size_t operator()(SEXP s) const {
            return Rf_hash(s);
        }
    };
#else
    struct CHARSXPHash {
        size_t operator()(SEXP s) const {
            return reinterpret_cast<size_t>(s);
        }
    };
#endif

struct CHARSXPEqual {
    bool operator()(SEXP a, SEXP b) const {
        return a == b;
    }
};

using CharSXPSet = std::unordered_set<SEXP, CHARSXPHash, CHARSXPEqual>;


#endif // HASH_SET_H
