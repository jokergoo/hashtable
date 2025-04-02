#include <Rcpp.h>
#include <string>

#include "hash_table.h"

// typedef std::unordered_map<std::string, int>         StringIntMap;
// typedef std::unordered_map<std::string, double>      StringDoubleMap;
// typedef std::unordered_map<std::string, std::string> StringStringMap;
// typedef std::unordered_map<std::string, bool>        StringBoolMap;
// typedef std::unordered_map<std::string, Rcpp::Date>  StringDateMap;
// typedef std::unordered_map<std::string, time_t>      StringPOSIXctMap;
// typedef std::unordered_map<std::string, SEXP>        StringListMap;

// ------- IntegerVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, int>> create_hash_table_int(Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return create_hash_table<Rcpp::IntegerVector, std::unordered_map<std::string, int>, int>(keys, values);
}

// [[Rcpp::export]]
Rcpp::IntegerVector get_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return set_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>, int>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, int>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::IntegerVector get_all_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return get_all_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>>(map_xptr);
}

// ------- NumericVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, double>> create_hash_table_double(Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return create_hash_table<Rcpp::NumericVector, std::unordered_map<std::string, double>, double>(keys, values);
}

// [[Rcpp::export]]
Rcpp::NumericVector get_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::NumericVector, std::unordered_map<std::string, double>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return set_values<Rcpp::NumericVector, std::unordered_map<std::string, double>, double>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, double>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::NumericVector get_all_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return get_all_values<Rcpp::NumericVector, std::unordered_map<std::string, double>>(map_xptr);
}

// ------- CharacterVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, std::string>> create_hash_table_string(Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return create_hash_table<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>, Rcpp::String>(keys, values);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return set_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>, Rcpp::String>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, std::string>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return get_all_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>>(map_xptr);
}

// ------- LogicalVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, bool>> create_hash_table_bool(Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return create_hash_table<Rcpp::LogicalVector, std::unordered_map<std::string, bool>, bool>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector get_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return set_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>, bool>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, bool>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::LogicalVector get_all_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return get_all_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>>(map_xptr);
}

// ------- DateVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> create_hash_table_date(Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return create_hash_table<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>, Rcpp::Date>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DateVector get_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return set_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>, Rcpp::Date>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, Rcpp::Date>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DateVector get_all_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return get_all_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// ------- DatetimeVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, time_t>> create_hash_table_time(Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return create_hash_table<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>, time_t>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector get_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return set_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>, time_t>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, time_t>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector get_all_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return get_all_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>>(map_xptr);
}

// ------- List

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, SEXP>> create_hash_table_list(Rcpp::CharacterVector keys, Rcpp::List values) {
    return create_hash_table<Rcpp::List, std::unordered_map<std::string, SEXP>, SEXP>(keys, values);
}

// [[Rcpp::export]]
Rcpp::List get_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::List, std::unordered_map<std::string, SEXP>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
void set_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys, Rcpp::List values) {
    return set_values<Rcpp::List, std::unordered_map<std::string, SEXP>, SEXP>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<std::unordered_map<std::string, SEXP>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return hash_table_size<std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return get_all_keys<std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::List get_all_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return get_all_values<Rcpp::List, std::unordered_map<std::string, SEXP>>(map_xptr);
}


