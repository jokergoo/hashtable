#include <Rcpp.h>

// [[Rcpp::export]]
void cpp_update_vector_elements(SEXP x, Rcpp::IntegerVector ind, SEXP values) {
    int n = ind.size();
    int type = TYPEOF(x);
    
    if(type != TYPEOF(values)) {
        Rcpp::stop("x and values must be of the same type");
    }
    
    for(int i = 0; i < n; i++) {
        int idx = ind[i] - 1;  // R索引从1开始
        if(idx < 0 || idx >= Rf_length(x)) {
            Rcpp::stop("Index out of bounds: %d", idx + 1);
        }
        
        switch(type) {
            case INTSXP: {
                INTEGER(x)[idx] = INTEGER(values)[i];
                break;
            }
            case REALSXP: {
                REAL(x)[idx] = REAL(values)[i];
                break;
            }
            case STRSXP: {
                SET_STRING_ELT(x, idx, STRING_ELT(values, i));
                break;
            }
            case LGLSXP: {
                LOGICAL(x)[idx] = LOGICAL(values)[i];
                break;
            }
            case VECSXP: {
                SET_VECTOR_ELT(x, idx, VECTOR_ELT(values, i));
                break;
            }
            default:
                Rcpp::stop("Unsupported vector type: %s", Rf_type2char(type));
        }
    }
}
