#include <Rcpp.h>
using namespace Rcpp;

#include "hash_env.h"


// [[Rcpp::export]]
Environment hash_env_hash_set_create(CharacterVector keys) {
	int n = keys.size();
	Environment env = new_env(Environment::empty_env());
	for(int i = 0; i < n; i ++) {
    	String key = keys[i];
    	env.assign(key, R_NilValue);
    }

    return env;
}

// [[Rcpp::export]]
Environment hash_env_copy(Environment env) {
	CharacterVector all_keys = env.ls(true);
	int n = all_keys.size();
	Environment env2 = new_env(Environment::empty_env());
	for(int i = 0; i < n; i ++) {
    	String key = all_keys[i];
    	RObject value = env.get(key);
    	env2.assign(key, value);
    }

    return env2;
}


// [[Rcpp::export]]
LogicalVector internal_hash_env_exists(Environment env, CharacterVector keys) {
	int n = keys.size();
    LogicalVector l(n);
    for(int i = 0; i < n; i ++) {
    	String key = keys[i];
    	l[i] = env.exists(key);
    }
    return l;
}


// [[Rcpp::export]]
LogicalVector internal_hash_env_delete(Environment env, CharacterVector keys) {
	int n = keys.size();
    LogicalVector l(n);
    for(int i = 0; i < n; i ++) {
    	String key = keys[i];
    	l[i] = env.remove(key);
    }
    return l;
}

// [[Rcpp::export]]
int internal_hash_env_size(Environment env) {
	CharacterVector obj = env.ls(true);
	return obj.size();
}

// ==================================================

// [[Rcpp::export]]
LogicalVector internal_hash_env_values_logical(Environment env, CharacterVector keys) {
	return internal_hash_env_values<LogicalVector>(env, keys);
}

// [[Rcpp::export]]
IntegerVector internal_hash_env_values_integer(Environment env, CharacterVector keys) {
	return internal_hash_env_values<IntegerVector>(env, keys);
}

// [[Rcpp::export]]
CharacterVector internal_hash_env_values_character(Environment env, CharacterVector keys) {
	return internal_hash_env_values<CharacterVector>(env, keys);
}

// [[Rcpp::export]]
NumericVector internal_hash_env_values_numeric(Environment env, CharacterVector keys) {
	return internal_hash_env_values<NumericVector>(env, keys);
}

// [[Rcpp::export]]
DateVector internal_hash_env_values_date(Environment env, CharacterVector keys) {
	return internal_hash_env_values<DateVector>(env, keys);
}

// [[Rcpp::export]]
DatetimeVector internal_hash_env_values_time(Environment env, CharacterVector keys) {
	return internal_hash_env_values<DatetimeVector>(env, keys);
}


// ===================================================

// [[Rcpp::export]]
Environment internal_hash_env_set_values_logical(Environment env, CharacterVector keys, LogicalVector values) {
	return internal_hash_env_set_values<LogicalVector, bool>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_integer(Environment env, CharacterVector keys, IntegerVector values) {
	return internal_hash_env_set_values<IntegerVector, int>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_character(Environment env, CharacterVector keys, CharacterVector values) {
	return internal_hash_env_set_values<CharacterVector, String>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_numeric(Environment env, CharacterVector keys, NumericVector values) {
	return internal_hash_env_set_values<NumericVector, double>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_date(Environment env, CharacterVector keys, DateVector values) {
	return internal_hash_env_set_values<DateVector, Rcpp::Date>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_time(Environment env, CharacterVector keys, DatetimeVector values) {
	return internal_hash_env_set_values<DatetimeVector, time_t>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_list(Environment env, CharacterVector keys, List values) {
	return internal_hash_env_set_values<List, RObject>(env, keys, values);
}

// [[Rcpp::export]]
Environment internal_hash_env_set_values_null(Environment env, CharacterVector keys) {
	int n = keys.size();
	for(int i = 0; i < n; i ++) {
		std::string key = Rcpp::as<std::string>(keys[i]);
		env.assign(key, R_NilValue);
	}

	return env;
}

