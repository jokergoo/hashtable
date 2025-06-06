#ifndef __HASH_SET__
#define __HASH_SET__

#include <Rcpp.h>
#include <unordered_set>
#include <string>

template <typename StringMap, typename TRcppVector>
Rcpp::XPtr<StringMap> t_hash_set_create(TRcppVector keys) {

    StringMap* map_ptr = new StringMap();

    map_ptr->reserve(keys.size());

    (*map_ptr).insert(keys.begin(), keys.end());

    Rcpp::XPtr<StringMap> ptr(map_ptr, true);

    return ptr;
}

template <typename StringMap, typename TRcppVector>
void t_hash_set_insert(Rcpp::XPtr<StringMap> map_xptr, TRcppVector keys) {

    StringMap* map_ptr = map_xptr.get();

    (*map_ptr).insert(keys.begin(), keys.end());

    return;
}

template <typename StringMap, typename TRcppVector>
Rcpp::LogicalVector t_hash_set_exists(Rcpp::XPtr<StringMap> map_xptr, TRcppVector keys) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    Rcpp::LogicalVector l(keys.size());

    for (R_xlen_t i = 0; i < keys.size(); ++i) {

        auto it = map_ptr->find(keys[i]);

        if (it != map_ptr->end()) {
            l[i] = true;
        } else {
            l[i] = false;
        }
    }

    return l;
}

template <typename StringMap, typename TRcppVector, typename TValue>
Rcpp::LogicalVector t_hash_set_exists_with_type(Rcpp::XPtr<StringMap> map_xptr, TRcppVector keys) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    Rcpp::LogicalVector l(keys.size());

    for (R_xlen_t i = 0; i < keys.size(); ++i) {

        TValue k = Rcpp::as<TValue>(keys[i]);
        auto it = map_ptr->find(k);

        if (it != map_ptr->end()) {
            l[i] = true;
        } else {
            l[i] = false;
        }
    }

    return l;
}



template <typename StringMap, typename TRcppVector>
void t_hash_set_delete(Rcpp::XPtr<StringMap> map_xptr, TRcppVector keys_to_delete) {
    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    for (R_xlen_t i = 0; i < keys_to_delete.size(); ++i) {

        auto it = map_ptr->find(keys_to_delete[i]);
        if (it != map_ptr->end()) {
            map_ptr->erase(it);
        }

    }

    return;
}

template <typename StringMap, typename TRcppVector, typename TValue>
void t_hash_set_delete_with_type(Rcpp::XPtr<StringMap> map_xptr, TRcppVector keys_to_delete) {
    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    for (R_xlen_t i = 0; i < keys_to_delete.size(); ++i) {
        TValue k = Rcpp::as<TValue>(keys_to_delete[i]);

        auto it = map_ptr->find(k);
        if (it != map_ptr->end()) {
            map_ptr->erase(it);
        }
    }

    return;
}

template <typename StringMap>
void t_hash_set_clear(Rcpp::XPtr<StringMap> map_xptr) {
    StringMap& map = *map_xptr;
    map.clear();
    return;
}

template <typename StringMap>
Rcpp::XPtr<StringMap> t_hash_set_copy(Rcpp::XPtr<StringMap> map_xptr) {

    const StringMap& source_map = *map_xptr;

    StringMap* copy_map_ptr = new StringMap(source_map);

    Rcpp::XPtr<StringMap> new_xptr(copy_map_ptr, true);

    return new_xptr;
}

template <typename StringMap>
int t_hash_set_size(Rcpp::XPtr<StringMap> map_xptr) {
    StringMap* map_ptr = map_xptr.get();
    int size = map_ptr->size();
    return size;
}

template <typename StringMap, typename TRcppVector>
TRcppVector t_hash_set_get_all_keys(Rcpp::XPtr<StringMap> map_xptr) {

    StringMap* map_ptr = map_xptr.get();

    if (map_ptr == nullptr) {
        Rcpp::stop("The provided external pointer is NULL (points to an invalid or finalized map).");
    }

    int size = map_ptr->size();
    TRcppVector all_keys(size);

    int i = 0;
    for (auto const& element : *map_ptr) {
        all_keys[i] = element;
        i ++;
    }

    return all_keys;
}

#endif

