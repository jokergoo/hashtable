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
Rcpp::XPtr<std::unordered_map<std::string, int>> hash_table_create_int(Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return t_hash_table_create<Rcpp::IntegerVector, std::unordered_map<std::string, int>, int>(keys, values);
}

// [[Rcpp::export]]
Rcpp::IntegerVector hash_table_get_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, int>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return t_hash_table_set_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>, int>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, int>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::IntegerVector hash_table_get_all_values_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::IntegerVector, std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, int>> hash_table_copy_int(Rcpp::XPtr<std::unordered_map<std::string, int>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, int>>(map_xptr);
}

// ------- NumericVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, double>> hash_table_create_double(Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return t_hash_table_create<Rcpp::NumericVector, std::unordered_map<std::string, double>, double>(keys, values);
}

// [[Rcpp::export]]
Rcpp::NumericVector hash_table_get_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::NumericVector, std::unordered_map<std::string, double>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, double>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return t_hash_table_set_values<Rcpp::NumericVector, std::unordered_map<std::string, double>, double>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, double>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::NumericVector hash_table_get_all_values_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::NumericVector, std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, double>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, double>> hash_table_copy_double(Rcpp::XPtr<std::unordered_map<std::string, double>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, double>>(map_xptr);
}

// ------- CharacterVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, std::string>> hash_table_create_string(Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return t_hash_table_create<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>, Rcpp::String>(keys, values);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, std::string>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return t_hash_table_set_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>, Rcpp::String>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, std::string>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_values_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::CharacterVector, std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, std::string>> hash_table_copy_string(Rcpp::XPtr<std::unordered_map<std::string, std::string>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, std::string>>(map_xptr);
}

// ------- LogicalVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, bool>> hash_table_create_bool(Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return t_hash_table_create<Rcpp::LogicalVector, std::unordered_map<std::string, bool>, bool>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_get_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, bool>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return t_hash_table_set_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>, bool>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, bool>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_get_all_values_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::LogicalVector, std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, bool>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, bool>> hash_table_copy_bool(Rcpp::XPtr<std::unordered_map<std::string, bool>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, bool>>(map_xptr);
}

// ------- DateVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> hash_table_create_date(Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return t_hash_table_create<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>, Rcpp::Date>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DateVector hash_table_get_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, Rcpp::Date>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return t_hash_table_set_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>, Rcpp::Date>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, Rcpp::Date>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DateVector hash_table_get_all_values_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::DateVector, std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> hash_table_copy_date(Rcpp::XPtr<std::unordered_map<std::string, Rcpp::Date>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, Rcpp::Date>>(map_xptr);
}

// ------- DatetimeVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, time_t>> hash_table_create_time(Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return t_hash_table_create<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>, time_t>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector hash_table_get_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, time_t>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return t_hash_table_set_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>, time_t>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, time_t>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector hash_table_get_all_values_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::DatetimeVector, std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, time_t>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, time_t>> hash_table_copy_time(Rcpp::XPtr<std::unordered_map<std::string, time_t>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, time_t>>(map_xptr);
}

// ------- List

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, SEXP>> hash_table_create_list(Rcpp::CharacterVector keys, Rcpp::List values) {
    return t_hash_table_create<Rcpp::List, std::unordered_map<std::string, SEXP>, SEXP>(keys, values);
}

// [[Rcpp::export]]
Rcpp::List hash_table_get_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return t_hash_table_get_values<Rcpp::List, std::unordered_map<std::string, SEXP>>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_table_exists_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<std::unordered_map<std::string, SEXP>>(map_xptr, keys);
}

// [[Rcpp::export]]
void hash_table_set_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys, Rcpp::List values) {
    return t_hash_table_set_values<Rcpp::List, std::unordered_map<std::string, SEXP>, SEXP>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void hash_table_delete_pairs_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_table_delete_pairs<std::unordered_map<std::string, SEXP>>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return t_hash_table_size<std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_table_get_all_keys_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return t_hash_table_get_all_keys<std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::List hash_table_get_all_values_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return t_hash_table_get_all_values<Rcpp::List, std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
void hash_table_clear_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return t_hash_table_clear<std::unordered_map<std::string, SEXP>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_map<std::string, SEXP>> hash_table_copy_list(Rcpp::XPtr<std::unordered_map<std::string, SEXP>> map_xptr) {
    return t_hash_table_copy<std::unordered_map<std::string, SEXP>>(map_xptr);
}
