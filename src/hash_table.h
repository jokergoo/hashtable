#ifndef __HASH__
#define __HASH__

#include <Rcpp.h>
#include <unordered_map>
#include <string>

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
void set_values(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys, TRcppVector values) {


    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    for (R_xlen_t i = 0; i < keys.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys[i]);

        TValue value_sexp = values[i];

        (*map_ptr)[key_str] = value_sexp;
    }
    
    return;
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
void clear(Rcpp::XPtr<StringMap> map_xptr) {

}

template <typename StringMap>
Rcpp::XPtr<StringMap> copy(Rcpp::XPtr<StringMap> map_xptr) {
    
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

#endif

