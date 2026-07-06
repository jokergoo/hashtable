#ifndef __HASH__
#define __HASH__

#include <Rcpp.h>
#include <unordered_map>
#include <string>

template <typename TRcppVector, typename StringMap, typename TValue>
Rcpp::XPtr<StringMap> t_hash_table_create(Rcpp::CharacterVector keys, TRcppVector values) {

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
TRcppVector t_hash_table_get_values(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys_to_get) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    TRcppVector results(keys_to_get.size());
    // Rcpp::CharacterVector result_names(keys_to_get.size());

    for (R_xlen_t i = 0; i < keys_to_get.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys_to_get[i]);
        //result_names[i] = keys_to_get[i];

        auto it = map_ptr->find(key_str);

        if (it != map_ptr->end()) {
            results[i] = it->second;
        } else {
            Rcpp::stop("Cannot find the key: %s.", key_str);
        }
    }

    //results.names() = result_names;

    return results;
}

template <typename StringMap>
Rcpp::LogicalVector t_hash_table_exists(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    Rcpp::LogicalVector l(keys.size());

    for (R_xlen_t i = 0; i < keys.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys[i]);

        auto it = map_ptr->find(key_str);

        if (it != map_ptr->end()) {
            l[i] = true;
        } else {
            l[i] = false;
        }
    }

    return l;
}



template <typename TRcppVector, typename StringMap, typename TValue>
void t_hash_table_set_values(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys, TRcppVector values) {


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
void t_hash_table_delete_pairs(Rcpp::XPtr<StringMap> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    for (R_xlen_t i = 0; i < keys_to_delete.size(); ++i) {
        std::string key_str = Rcpp::as<std::string>(keys_to_delete[i]);

        auto it = map_ptr->find(key_str);
        if (it != map_ptr->end()) {
            map_ptr->erase(it);
        }
    }

    return;
}

template <typename StringMap>
void t_hash_table_clear(Rcpp::XPtr<StringMap> map_xptr) {
    StringMap& map = *map_xptr;
    map.clear();
    return;
}

template <typename StringMap>
Rcpp::XPtr<StringMap> t_hash_table_copy(Rcpp::XPtr<StringMap> map_xptr) {

    const StringMap& source_map = *map_xptr;

    StringMap* copy_map_ptr = new StringMap(source_map);

    Rcpp::XPtr<StringMap> new_xptr(copy_map_ptr, true);

    return new_xptr;
}

template <typename StringMap>
int t_hash_table_size(Rcpp::XPtr<StringMap> map_xptr) {
    StringMap* map_ptr = map_xptr.get();
    int size = map_ptr->size();
    return size;
}

template <typename StringMap>
Rcpp::CharacterVector t_hash_table_get_all_keys(Rcpp::XPtr<StringMap> map_xptr) {

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
TRcppVector t_hash_table_get_all_values(Rcpp::XPtr<StringMap> map_xptr) {

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

