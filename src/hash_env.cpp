#include <Rcpp.h>

#include <Rinternals.h>
#include <Rdefines.h>
#include <Rversion.h>

#include "hash_env.h"
#include "utils.h"

SEXP create_integer_value(int value) {
    return Rf_ScalarInteger(value);
}

SEXP create_double_value(double value) {
    return Rf_ScalarReal(value);
}

SEXP create_bool_value(int value) {
    return Rf_ScalarLogical(value);
}

SEXP create_string_value(SEXP value) {
    SEXP result = Rf_allocVector(STRSXP, 1);
    SET_STRING_ELT(result, 0, value);
    return result;
}

SEXP create_date_value(int value) {
    SEXP result = Rf_allocVector(INTSXP, 1);
    INTEGER(result)[0] = value;
    SEXP class_attr = Rf_mkString("Date");
    Rf_setAttrib(result, R_ClassSymbol, class_attr);
    return result;
}

SEXP create_datetime_value(double value) {
    SEXP result = Rf_allocVector(REALSXP, 1);
    REAL(result)[0] = value;
    
    SEXP class_attr = PROTECT(Rf_allocVector(STRSXP, 2));
    SET_STRING_ELT(class_attr, 0, Rf_mkChar("POSIXct"));
    SET_STRING_ELT(class_attr, 1, Rf_mkChar("POSIXt"));
    Rf_setAttrib(result, R_ClassSymbol, class_attr);
    
    SEXP tzone_attr = PROTECT(Rf_mkString("UTC"));
    Rf_setAttrib(result, Rf_install("tzone"), tzone_attr);
    
    UNPROTECT(2);
    return result;
}

SEXP create_list_value(SEXP value) {
    return value;
}

// ==== create

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_int(Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    return t_hash_env_table_create<Rcpp::IntegerVector>(keys, values, create_integer_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_double(Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    return t_hash_env_table_create<Rcpp::NumericVector>(keys, values, create_double_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_bool(Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    return t_hash_env_table_create<Rcpp::LogicalVector>(keys, values, create_bool_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_string(Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    return t_hash_env_table_create<Rcpp::CharacterVector>(keys, values, create_string_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_date(Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    return t_hash_env_table_create<Rcpp::DateVector>(keys, values, create_date_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_time(Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    return t_hash_env_table_create<Rcpp::DatetimeVector>(keys, values, create_datetime_value);
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_table_create_list(Rcpp::CharacterVector keys, Rcpp::List values) {
    return t_hash_env_table_create<Rcpp::List>(keys, values, create_list_value);
}


// ===== insert

// [[Rcpp::export]]
void cpp_hash_env_table_insert_int(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::IntegerVector values) {
    t_hash_env_table_insert<Rcpp::IntegerVector>(env, keys, values, create_integer_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_double(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::NumericVector values) {
    t_hash_env_table_insert<Rcpp::NumericVector>(env, keys, values, create_double_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_bool(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::LogicalVector values) {
    t_hash_env_table_insert<Rcpp::LogicalVector>(env, keys, values, create_bool_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_string(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::CharacterVector values) {
    t_hash_env_table_insert<Rcpp::CharacterVector>(env, keys, values, create_string_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_date(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::DateVector values) {
    t_hash_env_table_insert<Rcpp::DateVector>(env, keys, values, create_date_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_time(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::DatetimeVector values) {
    t_hash_env_table_insert<Rcpp::DatetimeVector>(env, keys, values, create_datetime_value);
}

// [[Rcpp::export]]
void cpp_hash_env_table_insert_list(Rcpp::Environment env, Rcpp::CharacterVector keys, Rcpp::List values) {
    t_hash_env_table_insert<Rcpp::List>(env, keys, values, create_list_value);
}


// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_env_exists(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    SEXP env_sexp = env;
    int n = keys.size();
    Rcpp::LogicalVector result(n);

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        const char* key_str = CHAR(STRING_ELT(keys, i));
        SEXP symbol = Rf_install(key_str);
        
        #if defined(R_VERSION) && R_VERSION >= R_Version(4, 5, 0)
            SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
            result[i] = (value != R_NilValue);
        #else
            SEXP value = Rf_findVar(symbol, env_sexp);
            result[i] = (value != R_UnboundValue);
        #endif
    }
    
    return result;
}


// [[Rcpp::export]]
int cpp_hash_env_size(Rcpp::Environment env) {
    Rcpp::CharacterVector names = env.ls(false);
    return names.size();
}

// [[Rcpp::export]]
void cpp_hash_env_clear(Rcpp::Environment env) {
    Rcpp::CharacterVector keys = env.ls(false);
    for(int i = 0; i < keys.size(); i++) {
        env.remove(Rcpp::as<std::string>(keys[i]));
    }
}

// [[Rcpp::export]]
void cpp_hash_env_delete(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    if(n == 0) return;

    validate_keys(keys, true, true, true);
    
    for(int i = 0; i < n; i++) {
        Rcpp::String key = keys[i];
        if(!env.exists(key)) {
            Rcpp::stop("Key not found at position %d: '%s'", i + 1, key.get_cstring());
        }
        env.remove(key);
    }
}

// [[Rcpp::export]]
Rcpp::Environment cpp_hash_env_copy(Rcpp::Environment env) {
    Rcpp::CharacterVector all_keys = env.ls(true);
    int n = all_keys.size();
    Rcpp::Environment env2 = new_env(Rcpp::Environment::empty_env());
    for(int i = 0; i < n; i ++) {
        Rcpp::String key = all_keys[i];
        Rcpp::RObject value = env.get(key);
        env2.assign(key, value);
    }

    return env2;
}


SEXP get_env_keys(SEXP env_sexp) {
    #if defined(R_VERSION) && R_VERSION >= R_Version(3, 5, 0)
        return R_lsInternal3(env_sexp, (Rboolean)1, (Rboolean)0);
    #else
        return R_lsInternal(env_sexp, 1);
    #endif
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_env_keys(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    return Rcpp::as<Rcpp::CharacterVector>(names);
}

// ===== get values 


// [[Rcpp::export]]
Rcpp::IntegerVector cpp_hash_env_table_all_values_int(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::IntegerVector();
    }
    
    int n = Rf_length(names);
    Rcpp::IntegerVector result(n);
    int* result_ptr = &result[0];
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        result_ptr[i] = INTEGER(value)[0];
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::NumericVector cpp_hash_env_table_all_values_double(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::NumericVector();
    }
    
    int n = Rf_length(names);
    Rcpp::NumericVector result(n);
    double* result_ptr = &result[0];
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        result_ptr[i] = REAL(value)[0];
    }

    return result;
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_env_table_all_values_string(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::CharacterVector();
    }
    
    int n = Rf_length(names);
    Rcpp::CharacterVector result(n);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        result[i] = STRING_ELT(value, 0);
    }

    return result;
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_env_table_all_values_bool(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::LogicalVector();
    }
    
    int n = Rf_length(names);
    Rcpp::LogicalVector result(n);
    int* result_ptr = &result[0];
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        result_ptr[i] = LOGICAL(value)[0];
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::DateVector cpp_hash_env_table_all_values_date(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::DateVector(0);
    }
    
    int n = Rf_length(names);
    Rcpp::DateVector result(n);
    double* result_ptr = &result[0];
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        if (name == R_NilValue || LENGTH(name) == 0) {
            result_ptr[i] = NA_INTEGER;
            continue;
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        result_ptr[i] = INTEGER(value)[0];
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::DatetimeVector cpp_hash_env_table_all_values_time(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::DatetimeVector(0);
    }
    
    int n = Rf_length(names);
    Rcpp::DatetimeVector result(n);
    double* result_ptr = &result[0];
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        if (name == R_NilValue || LENGTH(name) == 0) {
            result_ptr[i] = NA_INTEGER;
            continue;
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        result_ptr[i] = REAL(value)[0];
    }
    
    return result;
}


// [[Rcpp::export]]
Rcpp::List cpp_hash_env_table_all_values_list(Rcpp::Environment env) {
    SEXP env_sexp = env;
    
    SEXP names = get_env_keys(env_sexp);
    
    if(names == R_NilValue) {
        return Rcpp::List(0);
    }
    
    int n = Rf_length(names);
    Rcpp::List result(n);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(names, i);
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        result[i] = value;
    }
    
    return result;
}

// ==========================


// [[Rcpp::export]]
Rcpp::IntegerVector cpp_hash_env_table_values_int(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::IntegerVector result(n);
    int* result_ptr = &result[0];
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result_ptr[i] = INTEGER(value)[0];
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::NumericVector cpp_hash_env_table_values_double(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::NumericVector result(n);
    double* result_ptr = &result[0];
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result_ptr[i] = REAL(value)[0];
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::CharacterVector cpp_hash_env_table_values_string(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::CharacterVector result(n);
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result[i] = STRING_ELT(value, 0);
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::LogicalVector cpp_hash_env_table_values_bool(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::LogicalVector result(n);
    int* result_ptr = &result[0];
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result_ptr[i] = LOGICAL(value)[0];
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::DateVector cpp_hash_env_table_values_date(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::DateVector result(n);
    double* result_ptr = &result[0];
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result_ptr[i] = REAL(value)[0];
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::DatetimeVector cpp_hash_env_table_values_time(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::DatetimeVector result(n);
    double* result_ptr = &result[0];
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result_ptr[i] = REAL(value)[0];
        }
    }
    
    return result;
}

// [[Rcpp::export]]
Rcpp::List cpp_hash_env_table_values_list(Rcpp::Environment env, Rcpp::CharacterVector keys) {
    int n = keys.size();
    Rcpp::List result(n);
    SEXP env_sexp = env;

    validate_keys(keys, true, true, false);
    
    for(int i = 0; i < n; i++) {
        SEXP name = STRING_ELT(keys, i);
        if(name == R_NilValue || LENGTH(name) == 0) {
            Rf_error("Invalid key at position %d: empty string", i + 1);
        }
        
        SEXP symbol = Rf_install(CHAR(name));
        SEXP value = R_getVarEx(symbol, env_sexp, TRUE, R_NilValue);
        
        if(value == R_NilValue) {
            Rf_error("Key not found: %s", CHAR(name));
        } else {
            result[i] = value;
        }
    }
    
    return result;
}
