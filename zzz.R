load_ns <- function() {
    R_files = list.files(path = "R", full.names = TRUE)
    R_files = R_files[!grepl("RcppExports.R", R_files)]
    R_files = R_files[!grepl("zzz.R", R_files)]
    sapply(R_files, source)

    cpp_files = list.files(path = "src", pattern = "cpp$", full.names = TRUE)
    cpp_files = cpp_files[!grepl("RcppExports.cpp", cpp_files)]

    sapply(cpp_files, Rcpp::sourceCpp)

    lines = readLines("src/RcppExports.cpp")
    i = which(lines == "#include <Rcpp.h>")

    if(any(lines == '#include "hash.h"')) {

    } else {
        lines = c(lines[1:i], '#include "hash.h"', lines[(i+1):length(lines)])
    }

    writeLines(lines, "src/RcppExports.cpp")
}
