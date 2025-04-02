#include <Rcpp.h>
#include <unordered_map>
#include <string>
#include <stdexcept> // For std::runtime_error

typedef std::unordered_map<std::string, int>         StringIntMap;
typedef std::unordered_map<std::string, double>      StringDoubleMap;
typedef std::unordered_map<std::string, std::string> StringStringMap;
typedef std::unordered_map<std::string, bool>        StringBoolMap;
typedef std::unordered_map<std::string, Rcpp::Date>  StringDateMap;
typedef std::unordered_map<std::string, time_t>      StringPOSIXctMap;
typedef std::unordered_map<std::string, SEXP>        StringListMap;


template <typename TRcppVector, typename StringMap, typename TValue>
Rcpp::XPtr<StringMap> create_hash_table(Rcpp::CharacterVector keys, TRcppVector values) {

    StringMap* map_ptr = new StringMap();

    map_ptr->reserve(keys.size());

    
        for (R_xlen_t i = 0; i < keys.size(); ++i) {
            std::string key_str = Rcpp::as<std::string>(keys[i]);

            TValue value_sexp = values[i];

            (*map_ptr)[key_str] = value_sexp;
        }



    Rcpp::XPtr<StringMap> ptr(map_ptr, true);

    return ptr;
}


template <typename TRcppVector, typename StringMap>
TRcppVector get_values(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys_to_get) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    TRcppVector results(keys_to_get.size());
    Rcpp::CharacterVector result_names(keys_to_get.size());

    for (R_xlen_t i = 0; i < keys_to_get.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys_to_get[i]);
        result_names[i] = keys_to_get[i];

        auto it = map_ptr->find(key_str);

        if (it != map_ptr->end()) {
            results[i] = it->second;
        } else {
            Rcpp::stop("Cannot find key");
        }
    }

    results.names() = result_names;

    return results;
}

template <typename TRcppVector, typename StringMap, typename TValue>
Rcpp::XPtr<StringMap> set_values(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys, TRcppVector values) {


    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

        for (R_xlen_t i = 0; i < keys.size(); ++i) {
            std::string key_str = Rcpp::as<std::string>(keys[i]);

            TValue value_sexp = values[i];

            (*map_ptr)[key_str] = value_sexp;
        }
    

    return map_xptr;
}


template <typename StringMap>
void delete_pairs(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    for (R_xlen_t i = 0; i < keys_to_delete.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys_to_delete[i]);

        map_ptr->erase(map_ptr->find(key_str));
    }

    return;
}

template <typename StringMap>
int hash_table_size(Rcpp::XPtr<StringMap> map_xptr) {
    StringMap* map_ptr = map_xptr.get();
    int size = map_ptr->size();
    return size;
}

template <typename StringMap>
Rcpp::CharacterVector get_all_keys(Rcpp::XPtr<StringMap> map_xptr) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    int size = map_ptr->size();
    Rcpp::CharacterVector all_keys(size);

    int i = 0;
    for (auto const& element : *map_ptr) {
        all_keys[i] = element.first;
        i ++;
    }

    return all_keys;
}

template <typename TRcppVector, typename StringMap>
TRcppVector get_all_values(Rcpp::XPtr<StringMap> map_xptr) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    int size = map_ptr->size();
    TRcppVector all_values(size);

    int i = 0;
    for (auto const& element : *map_ptr) {
        all_values[i] = element.second;
        i ++;
    }

    return all_values;
}

// ------- IntegerVector

// [[Rcpp::export]]
Rcpp::XPtr<StringIntMap> create_hash_table_int(Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return create_hash_table<Rcpp::IntegerVector, StringIntMap, int>(keys, values);
}

// [[Rcpp::export]]
Rcpp::IntegerVector get_values_int(Rcpp::XPtr<StringIntMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::IntegerVector, StringIntMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringIntMap> set_values_int(Rcpp::XPtr<StringIntMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return set_values<Rcpp::IntegerVector, StringIntMap, int>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_int(Rcpp::XPtr<StringIntMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringIntMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_int(Rcpp::XPtr<StringIntMap> map_xptr) {
    return hash_table_size<StringIntMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_int(Rcpp::XPtr<StringIntMap> map_xptr) {
    return get_all_keys<StringIntMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::IntegerVector get_all_values_int(Rcpp::XPtr<StringIntMap> map_xptr) {
    return get_all_values<Rcpp::IntegerVector, StringIntMap>(map_xptr);
}

// ------- NumericVector

// [[Rcpp::export]]
Rcpp::XPtr<StringDoubleMap> create_hash_table_double(Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return create_hash_table<Rcpp::NumericVector, StringDoubleMap, double>(keys, values);
}

// [[Rcpp::export]]
Rcpp::NumericVector get_values_double(Rcpp::XPtr<StringDoubleMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::NumericVector, StringDoubleMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringDoubleMap> set_values_double(Rcpp::XPtr<StringDoubleMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return set_values<Rcpp::NumericVector, StringDoubleMap, double>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_double(Rcpp::XPtr<StringDoubleMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringDoubleMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_double(Rcpp::XPtr<StringDoubleMap> map_xptr) {
    return hash_table_size<StringDoubleMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_double(Rcpp::XPtr<StringDoubleMap> map_xptr) {
    return get_all_keys<StringDoubleMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::NumericVector get_all_values_double(Rcpp::XPtr<StringDoubleMap> map_xptr) {
    return get_all_values<Rcpp::NumericVector, StringDoubleMap>(map_xptr);
}

// ------- CharacterVector

// [[Rcpp::export]]
Rcpp::XPtr<StringStringMap> create_hash_table_string(Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return create_hash_table<Rcpp::CharacterVector, StringStringMap, Rcpp::String>(keys, values);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_values_string(Rcpp::XPtr<StringStringMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::CharacterVector, StringStringMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringStringMap> set_values_string(Rcpp::XPtr<StringStringMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return set_values<Rcpp::CharacterVector, StringStringMap, Rcpp::String>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_string(Rcpp::XPtr<StringStringMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringStringMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_string(Rcpp::XPtr<StringStringMap> map_xptr) {
    return hash_table_size<StringStringMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_string(Rcpp::XPtr<StringStringMap> map_xptr) {
    return get_all_keys<StringStringMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_values_string(Rcpp::XPtr<StringStringMap> map_xptr) {
    return get_all_values<Rcpp::CharacterVector, StringStringMap>(map_xptr);
}

// ------- LogicalVector

// [[Rcpp::export]]
Rcpp::XPtr<StringBoolMap> create_hash_table_bool(Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return create_hash_table<Rcpp::LogicalVector, StringBoolMap, bool>(keys, values);
}

// [[Rcpp::export]]
Rcpp::LogicalVector get_values_bool(Rcpp::XPtr<StringBoolMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::LogicalVector, StringBoolMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringBoolMap> set_values_bool(Rcpp::XPtr<StringBoolMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return set_values<Rcpp::LogicalVector, StringBoolMap, bool>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_bool(Rcpp::XPtr<StringBoolMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringBoolMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_bool(Rcpp::XPtr<StringBoolMap> map_xptr) {
    return hash_table_size<StringBoolMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_bool(Rcpp::XPtr<StringBoolMap> map_xptr) {
    return get_all_keys<StringBoolMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::LogicalVector get_all_values_bool(Rcpp::XPtr<StringBoolMap> map_xptr) {
    return get_all_values<Rcpp::LogicalVector, StringBoolMap>(map_xptr);
}

// ------- DateVector

// [[Rcpp::export]]
Rcpp::XPtr<StringDateMap> create_hash_table_date(Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return create_hash_table<Rcpp::DateVector, StringDateMap, Rcpp::Date>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DateVector get_values_date(Rcpp::XPtr<StringDateMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::DateVector, StringDateMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringDateMap> set_values_date(Rcpp::XPtr<StringDateMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return set_values<Rcpp::DateVector, StringDateMap, Rcpp::Date>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_date(Rcpp::XPtr<StringDateMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringDateMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_date(Rcpp::XPtr<StringDateMap> map_xptr) {
    return hash_table_size<StringDateMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_date(Rcpp::XPtr<StringDateMap> map_xptr) {
    return get_all_keys<StringDateMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DateVector get_all_values_date(Rcpp::XPtr<StringDateMap> map_xptr) {
    return get_all_values<Rcpp::DateVector, StringDateMap>(map_xptr);
}

// ------- DatetimeVector

// [[Rcpp::export]]
Rcpp::XPtr<StringPOSIXctMap> create_hash_table_time(Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return create_hash_table<Rcpp::DatetimeVector, StringPOSIXctMap, time_t>(keys, values);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector get_values_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::DatetimeVector, StringPOSIXctMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringPOSIXctMap> set_values_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return set_values<Rcpp::DatetimeVector, StringPOSIXctMap, time_t>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringPOSIXctMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr) {
    return hash_table_size<StringPOSIXctMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr) {
    return get_all_keys<StringPOSIXctMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::DatetimeVector get_all_values_time(Rcpp::XPtr<StringPOSIXctMap> map_xptr) {
    return get_all_values<Rcpp::DatetimeVector, StringPOSIXctMap>(map_xptr);
}

// ------- List

// [[Rcpp::export]]
Rcpp::XPtr<StringListMap> create_hash_table_list(Rcpp::CharacterVector keys, Rcpp::List values) {
    return create_hash_table<Rcpp::List, StringListMap, SEXP>(keys, values);
}

// [[Rcpp::export]]
Rcpp::List get_values_list(Rcpp::XPtr<StringListMap> map_xptr, Rcpp::CharacterVector keys_to_get) {
    return get_values<Rcpp::List, StringListMap>(map_xptr, keys_to_get);
}

// [[Rcpp::export]]
Rcpp::XPtr<StringListMap> set_values_list(Rcpp::XPtr<StringListMap> map_xptr, Rcpp::CharacterVector keys, Rcpp::List values) {
    return set_values<Rcpp::List, StringListMap, SEXP>(map_xptr, keys, values);
}

// [[Rcpp::export]]
void delete_pairs_list(Rcpp::XPtr<StringListMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return delete_pairs<StringListMap>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
int hash_table_size_list(Rcpp::XPtr<StringListMap> map_xptr) {
    return hash_table_size<StringListMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_all_keys_list(Rcpp::XPtr<StringListMap> map_xptr) {
    return get_all_keys<StringListMap>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::List get_all_values_list(Rcpp::XPtr<StringListMap> map_xptr) {
    return get_all_values<Rcpp::List, StringListMap>(map_xptr);
}


