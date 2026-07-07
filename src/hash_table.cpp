#include <Rcpp.h>
#include <unordered_map>

#include "hash_table.h"

//========= IntegerVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPIntMap> cpp_hash_table_create_int(Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return t_hash_table_create<CharSXPIntMap, Rcpp::IntegerVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_int(Rcpp::XPtr<CharSXPIntMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPIntMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::IntegerVector cpp_hash_table_values_int(Rcpp::XPtr<CharSXPIntMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPIntMap, Rcpp::IntegerVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_int(Rcpp::XPtr<CharSXPIntMap> ptr, Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return t_hash_table_insert<CharSXPIntMap, Rcpp::IntegerVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_int(Rcpp::XPtr<CharSXPIntMap> ptr) {
    return t_hash_table_size<CharSXPIntMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPIntMap> cpp_hash_table_copy_int(Rcpp::XPtr<CharSXPIntMap> ptr) {
    return t_hash_table_copy<CharSXPIntMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_int(Rcpp::XPtr<CharSXPIntMap> ptr) {
    return t_hash_table_all_keys<CharSXPIntMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::IntegerVector cpp_hash_table_all_values_int(Rcpp::XPtr<CharSXPIntMap> ptr) {
    return t_hash_table_all_values<CharSXPIntMap, Rcpp::IntegerVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_int(Rcpp::XPtr<CharSXPIntMap> ptr) {
    return t_hash_table_clear<CharSXPIntMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_int(Rcpp::XPtr<CharSXPIntMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPIntMap>(ptr, keys);
}

//========= NumericVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPDoubleMap> cpp_hash_table_create_double(Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return t_hash_table_create<CharSXPDoubleMap, Rcpp::NumericVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_double(Rcpp::XPtr<CharSXPDoubleMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPDoubleMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::NumericVector cpp_hash_table_values_double(Rcpp::XPtr<CharSXPDoubleMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPDoubleMap, Rcpp::NumericVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_double(Rcpp::XPtr<CharSXPDoubleMap> ptr, Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return t_hash_table_insert<CharSXPDoubleMap, Rcpp::NumericVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_double(Rcpp::XPtr<CharSXPDoubleMap> ptr) {
    return t_hash_table_size<CharSXPDoubleMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPDoubleMap> cpp_hash_table_copy_double(Rcpp::XPtr<CharSXPDoubleMap> ptr) {
    return t_hash_table_copy<CharSXPDoubleMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_double(Rcpp::XPtr<CharSXPDoubleMap> ptr) {
    return t_hash_table_all_keys<CharSXPDoubleMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::NumericVector cpp_hash_table_all_values_double(Rcpp::XPtr<CharSXPDoubleMap> ptr) {
    return t_hash_table_all_values<CharSXPDoubleMap, Rcpp::NumericVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_double(Rcpp::XPtr<CharSXPDoubleMap> ptr) {
    return t_hash_table_clear<CharSXPDoubleMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_double(Rcpp::XPtr<CharSXPDoubleMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPDoubleMap>(ptr, keys);
}


//========= CharacterVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPStringMap> cpp_hash_table_create_string(Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return t_hash_table_create<CharSXPStringMap, Rcpp::CharacterVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_string(Rcpp::XPtr<CharSXPStringMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPStringMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_values_string(Rcpp::XPtr<CharSXPStringMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPStringMap, Rcpp::CharacterVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_string(Rcpp::XPtr<CharSXPStringMap> ptr, Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return t_hash_table_insert<CharSXPStringMap, Rcpp::CharacterVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_string(Rcpp::XPtr<CharSXPStringMap> ptr) {
    return t_hash_table_size<CharSXPStringMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPStringMap> cpp_hash_table_copy_string(Rcpp::XPtr<CharSXPStringMap> ptr) {
    return t_hash_table_copy<CharSXPStringMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_string(Rcpp::XPtr<CharSXPStringMap> ptr) {
    return t_hash_table_all_keys<CharSXPStringMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_values_string(Rcpp::XPtr<CharSXPStringMap> ptr) {
    return t_hash_table_all_values<CharSXPStringMap, Rcpp::CharacterVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_string(Rcpp::XPtr<CharSXPStringMap> ptr) {
    return t_hash_table_clear<CharSXPStringMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_string(Rcpp::XPtr<CharSXPStringMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPStringMap>(ptr, keys);
}


//========= LogicalVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPBoolMap> cpp_hash_table_create_bool(Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return t_hash_table_create<CharSXPBoolMap, Rcpp::LogicalVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_bool(Rcpp::XPtr<CharSXPBoolMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPBoolMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_values_bool(Rcpp::XPtr<CharSXPBoolMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPBoolMap, Rcpp::LogicalVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_bool(Rcpp::XPtr<CharSXPBoolMap> ptr, Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return t_hash_table_insert<CharSXPBoolMap, Rcpp::LogicalVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_bool(Rcpp::XPtr<CharSXPBoolMap> ptr) {
    return t_hash_table_size<CharSXPBoolMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPBoolMap> cpp_hash_table_copy_bool(Rcpp::XPtr<CharSXPBoolMap> ptr) {
    return t_hash_table_copy<CharSXPBoolMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_bool(Rcpp::XPtr<CharSXPBoolMap> ptr) {
    return t_hash_table_all_keys<CharSXPBoolMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_all_values_bool(Rcpp::XPtr<CharSXPBoolMap> ptr) {
    return t_hash_table_all_values<CharSXPBoolMap, Rcpp::LogicalVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_bool(Rcpp::XPtr<CharSXPBoolMap> ptr) {
    return t_hash_table_clear<CharSXPBoolMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_bool(Rcpp::XPtr<CharSXPBoolMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPBoolMap>(ptr, keys);
}


//========= DateVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPDateMap> cpp_hash_table_create_date(Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return t_hash_table_create<CharSXPDateMap, Rcpp::DateVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_date(Rcpp::XPtr<CharSXPDateMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPDateMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::DateVector cpp_hash_table_values_date(Rcpp::XPtr<CharSXPDateMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPDateMap, Rcpp::DateVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_date(Rcpp::XPtr<CharSXPDateMap> ptr, Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return t_hash_table_insert<CharSXPDateMap, Rcpp::DateVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_date(Rcpp::XPtr<CharSXPDateMap> ptr) {
    return t_hash_table_size<CharSXPDateMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPDateMap> cpp_hash_table_copy_date(Rcpp::XPtr<CharSXPDateMap> ptr) {
    return t_hash_table_copy<CharSXPDateMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_date(Rcpp::XPtr<CharSXPDateMap> ptr) {
    return t_hash_table_all_keys<CharSXPDateMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::DateVector cpp_hash_table_all_values_date(Rcpp::XPtr<CharSXPDateMap> ptr) {
    return t_hash_table_all_values<CharSXPDateMap, Rcpp::DateVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_date(Rcpp::XPtr<CharSXPDateMap> ptr) {
    return t_hash_table_clear<CharSXPDateMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_date(Rcpp::XPtr<CharSXPDateMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPDateMap>(ptr, keys);
}


//========= DatetimeVector

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPPOSIXctMap> cpp_hash_table_create_time(Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return t_hash_table_create<CharSXPPOSIXctMap, Rcpp::DatetimeVector>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPPOSIXctMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector cpp_hash_table_values_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPPOSIXctMap, Rcpp::DatetimeVector>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr, Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return t_hash_table_insert<CharSXPPOSIXctMap, Rcpp::DatetimeVector>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr) {
    return t_hash_table_size<CharSXPPOSIXctMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPPOSIXctMap> cpp_hash_table_copy_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr) {
    return t_hash_table_copy<CharSXPPOSIXctMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr) {
    return t_hash_table_all_keys<CharSXPPOSIXctMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector cpp_hash_table_all_values_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr) {
    return t_hash_table_all_values<CharSXPPOSIXctMap, Rcpp::DatetimeVector>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr) {
    return t_hash_table_clear<CharSXPPOSIXctMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_time(Rcpp::XPtr<CharSXPPOSIXctMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPPOSIXctMap>(ptr, keys);
}


//========= List

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPListMap> cpp_hash_table_create_list(Rcpp::CharacterVector keys, Rcpp::List values) {
    return t_hash_table_create<CharSXPListMap, Rcpp::List>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_table_exists_list(Rcpp::XPtr<CharSXPListMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_exists<CharSXPListMap>(ptr, keys);
}

// [[Rcpp::export]]
Rcpp::List cpp_hash_table_values_list(Rcpp::XPtr<CharSXPListMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_values<CharSXPListMap, Rcpp::List>(ptr, keys);
}

// [[Rcpp::export]]
void cpp_hash_table_insert_list(Rcpp::XPtr<CharSXPListMap> ptr, Rcpp::CharacterVector keys, Rcpp::List values) {
    return t_hash_table_insert<CharSXPListMap, Rcpp::List>(ptr, keys, values);
}

// [[Rcpp::export]]
int cpp_hash_table_size_list(Rcpp::XPtr<CharSXPListMap> ptr) {
    return t_hash_table_size<CharSXPListMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<CharSXPListMap> cpp_hash_table_copy_list(Rcpp::XPtr<CharSXPListMap> ptr) {
    return t_hash_table_copy<CharSXPListMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_table_all_keys_list(Rcpp::XPtr<CharSXPListMap> ptr) {
    return t_hash_table_all_keys<CharSXPListMap>(ptr);
}

// [[Rcpp::export]]
Rcpp::List cpp_hash_table_all_values_list(Rcpp::XPtr<CharSXPListMap> ptr) {
    return t_hash_table_all_values<CharSXPListMap, Rcpp::List>(ptr); 
}

// [[Rcpp::export]]
void cpp_hash_table_clear_list(Rcpp::XPtr<CharSXPListMap> ptr) {
    return t_hash_table_clear<CharSXPListMap>(ptr);
}

// [[Rcpp::export]]
void cpp_hash_table_delete_list(Rcpp::XPtr<CharSXPListMap> ptr, Rcpp::CharacterVector keys) {
    return t_hash_table_delete<CharSXPListMap>(ptr, keys);
}



