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
    
    Rcpp::Function new_env = Rcpp::Environment::base_env()["new.env"];
    Rcpp::Environment env = new_env(
        Rcpp::Named("hash") = true,
        Rcpp::Named("parent") = Rcpp::Environment::empty_env()
    );

    int n = keys.size();
    if (n == 0) {
        return env;
    }

    SEXP env_sexp = env;
    
    SEXP* symbols = (SEXP*)R_alloc(n, sizeof(SEXP));
    for (int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        symbols[i] = Rf_install(CHAR(name));
    }
    
    for (int i = 0; i < n; i++) {
        SEXP value = create_func(values[i]);
        Rf_defineVar(symbols[i], value, env_sexp);
    }
    
    return env;
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
