#ifndef __HASH__
#define __HASH__

#include <Rcpp.h>
#include <unordered_map>
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

using CharSXPIntMap = std::unordered_map<SEXP, int, CHARSXPHash, CHARSXPEqual>;
using CharSXPDoubleMap = std::unordered_map<SEXP, double, CHARSXPHash, CHARSXPEqual>;
using CharSXPStringMap = std::unordered_map<SEXP, std::string, CHARSXPHash, CHARSXPEqual>;
using CharSXPBoolMap = std::unordered_map<SEXP, bool, CHARSXPHash, CHARSXPEqual>;
using CharSXPDateMap = std::unordered_map<SEXP, Rcpp::Date, CHARSXPHash, CHARSXPEqual>;
using CharSXPPOSIXctMap = std::unordered_map<SEXP, time_t, CHARSXPHash, CHARSXPEqual>;
using CharSXPListMap = std::unordered_map<SEXP, SEXP, CHARSXPHash, CHARSXPEqual>;

using CharSXPSet = std::unordered_set<SEXP, CHARSXPHash, CHARSXPEqual>;


template <typename CharSXPTMap, typename TRcppVector>
Rcpp::XPtr<CharSXPTMap> t_hash_table_create(Rcpp::CharacterVector keys, TRcppVector values) {

    CharSXPTMap* map = new CharSXPTMap();
    map->max_load_factor(0.7);
    
    int n = keys.size();
    if(n > 0) {
        map->reserve(n);
        
        for(int i = 0; i < n; i++) {
            SEXP key = STRING_ELT(keys, i);
            auto result = map->emplace(key, values[i]);
            if(!result.second) {
                std::string duplicate_key = CHAR(key);
                Rcpp::stop("Duplicate key found: " + duplicate_key);
            }
        }
    }
    
    return Rcpp::XPtr<CharSXPTMap>(map);
}


template <typename CharSXPTMap>
Rcpp::LogicalVector t_hash_table_exists(Rcpp::XPtr<CharSXPTMap> ptr, Rcpp::CharacterVector keys) {
    if(!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    int n = keys.size();
    Rcpp::LogicalVector result(n);
    
    for(int i = 0; i < n; i++) {
        SEXP key = STRING_ELT(keys, i);
        auto it = map->find(key);
        result[i] = (it != map->end());
    }
    
    return result;
}

template <typename CharSXPTMap, typename TRcppVector>
TRcppVector t_hash_table_values(Rcpp::XPtr<CharSXPTMap> ptr, Rcpp::CharacterVector keys) {
    if (!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    int n = keys.size();
    TRcppVector result(n);
    
    for (int i = 0; i < n; i++) {
        SEXP key = STRING_ELT(keys, i);
        auto it = map->find(key);
        if (it == map->end()) {
            std::string key_str = CHAR(key);
            Rcpp::stop("Key not found: " + key_str);
        }
        result[i] = it->second;
    }
    
    return result;
}

template <typename CharSXPTMap, typename TRcppVector>
void t_hash_table_insert(Rcpp::XPtr<CharSXPTMap> ptr, Rcpp::CharacterVector keys, TRcppVector values) {
    if (!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    int n = keys.size();
    
    if(n > 0) {
        map->reserve(map->size() + n);
        for(int i = 0; i < n; i++) {
            SEXP key = STRING_ELT(keys, i);
            (*map)[key] = values[i];
        }
    }
}

template <typename CharSXPTMap>
int t_hash_table_size(Rcpp::XPtr<CharSXPTMap> ptr) {
    if(!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    return ptr->size();
}

template <typename CharSXPTMap>
Rcpp::XPtr<CharSXPTMap> t_hash_table_copy(Rcpp::XPtr<CharSXPTMap> ptr) {
    if(!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* original = ptr.get();
    
    CharSXPTMap* copy = new CharSXPTMap();
    copy->max_load_factor(0.7);
    copy->reserve(original->size());
    
    copy->insert(original->begin(), original->end());
    
    return Rcpp::XPtr<CharSXPTMap>(copy);
}

template <typename CharSXPTMap>
Rcpp::CharacterVector t_hash_table_all_keys(Rcpp::XPtr<CharSXPTMap> ptr) {
    if (!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    size_t n = map->size();
    
    Rcpp::CharacterVector result(n);
    
    size_t i = 0;
    for(const auto& pair : *map) {
        result[i] = pair.first;
        i++;
    }
    
    return result;
}

template <typename CharSXPTMap, typename TRcppVector>
TRcppVector t_hash_table_all_values(Rcpp::XPtr<CharSXPTMap> ptr) {
    if (!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    size_t n = map->size();
    
    TRcppVector result(n);
    
    size_t i = 0;
    for (const auto& pair : *map) {
        result[i] = pair.second;
        i++;
    }

    return result;
}


template <typename CharSXPTMap>
void t_hash_table_clear(Rcpp::XPtr<CharSXPTMap> ptr) {
    if(!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    ptr->clear();
}

template <typename CharSXPTMap>
void t_hash_table_delete(Rcpp::XPtr<CharSXPTMap> ptr, Rcpp::CharacterVector keys) {
    if(!ptr) {
        Rcpp::stop("Invalid external pointer.");
    }
    
    CharSXPTMap* map = ptr.get();
    int n = keys.size();
    
    for(int i = 0; i < n; i++) {
        SEXP key = STRING_ELT(keys, i);
        size_t erased = map->erase(key);
        if (erased == 0) {
            std::string key_str = CHAR(key);
            Rcpp::stop("Key not found: " + key_str);
        }
    }
    
}

#endif

