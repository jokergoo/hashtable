#include <Rcpp.h>
#include <string>

#include "hash_set.h"


// ------- IntegerVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_set<int>> hash_set_create_int(Rcpp::IntegerVector keys) {
    return t_hash_set_create<std::unordered_set<int>, Rcpp::IntegerVector>(keys);
}

// [[Rcpp::export]]
void hash_set_insert_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr, Rcpp::IntegerVector keys) {
    return t_hash_set_insert<std::unordered_set<int>, Rcpp::IntegerVector>(map_xptr, keys);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_set_exists_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr, Rcpp::IntegerVector keys) {
    return t_hash_set_exists<std::unordered_set<int>, Rcpp::IntegerVector>(map_xptr, keys);
}

int _sum_logical(Rcpp::LogicalVector l) {
    int v = 0;
    for(int i = 0; i < l.size(); i ++) {
        if(l[i]) {
            v ++;
        }
    }
    return(v);
}

// [[Rcpp::export]]
Rcpp::List hash_set_intersect_to_list_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr, Rcpp::List lt) {
    int n = lt.size();
    Rcpp::List res(n);

    for(int i = 0; i < n; i ++) {
        Rcpp::IntegerVector keys = lt[i];
        Rcpp::LogicalVector l = hash_set_exists_int(map_xptr, keys);
        int k = _sum_logical(l);
        Rcpp::IntegerVector keys2(k);
        int x = 0;
        for(int j = 0; j < keys.size(); j ++) {
            if(l[j]) {
                keys2[x] = keys[j];
                x ++;
            }
        }
        res[i] = keys2;
    }

    return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector hash_set_intersect_to_list_int_n(Rcpp::XPtr<std::unordered_set<int>> map_xptr, Rcpp::List lt) {
    int n = lt.size();
    Rcpp::IntegerVector res(n);

    for(int i = 0; i < n; i ++) {
        Rcpp::IntegerVector keys = lt[i];
        Rcpp::LogicalVector l = hash_set_exists_int(map_xptr, keys);
        res[i] = _sum_logical(l);
    }

    return res;
}


// [[Rcpp::export]]
void hash_set_delete_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr, Rcpp::IntegerVector keys_to_delete) {
    return t_hash_set_delete<std::unordered_set<int>, Rcpp::IntegerVector>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
void hash_set_clear_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr) {
    return t_hash_set_clear<std::unordered_set<int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_set<int>> hash_set_copy_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr) {
    return t_hash_set_copy<std::unordered_set<int>>(map_xptr);
}

// [[Rcpp::export]]
int hash_set_size_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr) {
    return t_hash_set_size<std::unordered_set<int>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::IntegerVector hash_set_get_all_keys_int(Rcpp::XPtr<std::unordered_set<int>> map_xptr) {
    return t_hash_set_get_all_keys<std::unordered_set<int>, Rcpp::IntegerVector>(map_xptr);
}


// ------- CharacterVector

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_set<std::string>> hash_set_create_string(Rcpp::CharacterVector keys) {
    return t_hash_set_create<std::unordered_set<std::string>, Rcpp::CharacterVector>(keys);
}

// [[Rcpp::export]]
void hash_set_insert_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_set_insert<std::unordered_set<std::string>, Rcpp::CharacterVector>(map_xptr, keys);
}

// [[Rcpp::export]]
Rcpp::LogicalVector hash_set_exists_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr, Rcpp::CharacterVector keys) {
    return t_hash_set_exists_with_type<std::unordered_set<std::string>, Rcpp::CharacterVector, std::string>(map_xptr, keys);
}

// [[Rcpp::export]]
Rcpp::List hash_set_intersect_to_list_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr, Rcpp::List lt) {
    int n = lt.size();
    Rcpp::List res(n);

    for(int i = 0; i < n; i ++) {
        Rcpp::CharacterVector keys = lt[i];
        Rcpp::LogicalVector l = hash_set_exists_string(map_xptr, keys);
        int k = _sum_logical(l);
        Rcpp::CharacterVector keys2(k);
        int x = 0;
        for(int j = 0; j < keys.size(); j ++) {
            if(l[j]) {
                keys2[x] = keys[j];
                x ++;
            }
        }
        res[i] = keys2;
    }

    return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector hash_set_intersect_to_list_string_n(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr, Rcpp::List lt) {
    int n = lt.size();
    Rcpp::IntegerVector res(n);

    for(int i = 0; i < n; i ++) {
        Rcpp::CharacterVector keys = lt[i];
        Rcpp::LogicalVector l = hash_set_exists_string(map_xptr, keys);
        res[i] = _sum_logical(l);
    }

    return res;
}

// [[Rcpp::export]]
void hash_set_delete_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr, Rcpp::CharacterVector keys_to_delete) {
    return t_hash_set_delete_with_type<std::unordered_set<std::string>, Rcpp::CharacterVector, std::string>(map_xptr, keys_to_delete);
}

// [[Rcpp::export]]
void hash_set_clear_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr) {
    return t_hash_set_clear<std::unordered_set<std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::XPtr<std::unordered_set<std::string>> hash_set_copy_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr) {
    return t_hash_set_copy<std::unordered_set<std::string>>(map_xptr);
}

// [[Rcpp::export]]
int hash_set_size_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr) {
    return t_hash_set_size<std::unordered_set<std::string>>(map_xptr);
}

// [[Rcpp::export]]
Rcpp::CharacterVector hash_set_get_all_keys_string(Rcpp::XPtr<std::unordered_set<std::string>> map_xptr) {
    return t_hash_set_get_all_keys<std::unordered_set<std::string>, Rcpp::CharacterVector>(map_xptr);
}
