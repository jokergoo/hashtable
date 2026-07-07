load_ns <- function() {
    R_files = list.files(path = "R", full.names = TRUE)
    R_files = R_files[!grepl("RcppExports.R", R_files)]
    R_files = R_files[!grepl("zzz.R", R_files)]
    sapply(R_files, source)

    cpp_files = list.files(path = "src", pattern = "cpp$", full.names = TRUE)
    cpp_files = cpp_files[!grepl("RcppExports.cpp", cpp_files)]

    sapply(cpp_files, sourceCpp)

    lines = readLines("src/RcppExports.cpp")
    i = which(lines == "#include <Rcpp.h>")

    if(any(lines == '#include "hash_table.h"') && any(lines == '#include "hash_set.h"')) {

    } else if(any(lines == '#include "hash_table.h"')) {
        lines = c(lines[1:i], '#include "hash_set.h"', lines[(i+1):length(lines)])
    } else if(any(lines == '#include "hash_set.h"')) {
        lines = c(lines[1:i], '#include "hash_table.h"', lines[(i+1):length(lines)])
    } else {
        lines = c(lines[1:i], '#include "hash_table.h"', '#include "hash_set.h"', lines[(i+1):length(lines)])
    }

    writeLines(lines, "src/RcppExports.cpp")
}
