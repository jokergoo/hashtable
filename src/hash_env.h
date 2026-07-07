#ifndef HASH_ENV_H
#define HASH_ENV_H

#include <Rcpp.h>

#include <Rinternals.h>
#include <Rdefines.h>
#include <Rversion.h>

void validate_keys(Rcpp::CharacterVector keys) {
    int n = keys.size();
    std::unordered_set<SEXP> seen;
    seen.reserve(n);
    for (int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if (name == R_NilValue || LENGTH(name) == 0) {
            Rcpp::stop("Invalid key at position %d: empty string", i + 1);
        }
        if (seen.find(name) != seen.end()) {
            Rcpp::stop("Duplicate key at position %d: '%s'", i + 1, CHAR(name));
        }
        seen.insert(name);
    }
}


template <typename VectorType>
Rcpp::Environment t_hash_env_table_create(Rcpp::CharacterVector keys, VectorType values, 
                                           std::function<SEXP(typename VectorType::value_type)> create_func) {
    
    int n = keys.size();
    if (n == 0) {
        return Rcpp::Environment(R_NewEnv(R_EmptyEnv, 29, 1));
    }
    
    if (keys.size() != values.size()) {
        Rcpp::stop("Keys and values must have the same length");
    }
    
    validate_keys(keys);
    
    SEXP env_sexp = R_NewEnv(R_EmptyEnv, n * 2 + 1, 1);
        
    // 批量插入
    for (int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = create_func(values[i]);
        Rf_defineVar(symbol, value, env_sexp);
    }
    
    return Rcpp::Environment(env_sexp);
}


template <typename VectorType>
void t_hash_env_table_insert(Rcpp::Environment env, Rcpp::CharacterVector keys, VectorType values, 
                             std::function<SEXP(typename VectorType::value_type)> create_func) {
    int n = keys.size();
    if (n == 0) return;
    
    if (keys.size() != values.size()) {
        Rcpp::stop("Keys and values must have the same length");
    }
    
    validate_keys(keys);
    
    SEXP env_sexp = env;
    for (int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = create_func(values[i]);
        Rf_defineVar(symbol, value, env_sexp);
    }
}

#endif // HASH_ENV_H
