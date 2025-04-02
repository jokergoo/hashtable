

#' Hash table
#' @param keys keys
#' @param values values
#'
#' @import Rcpp
#' @export
#' @useDynLib hashtable, .registration = TRUE
hash_table = function(keys, values) {
	cl = class(values)[1]
	h = switch(class(values), 
		"integer"   = create_hash_table_int(keys, values),
		"logical"   = create_hash_table_bool(keys, values),
		"numeric"   = create_hash_table_double(keys, values),
		"character" = create_hash_table_string(keys, values),
		"Date"      = create_hash_table_date(keys, values),
		"POSIXct"   = create_hash_table_time(keys, values),
		"list"      = create_hash_table_list(keys, values),
		stop("Data type of `values` ('", cl, "') is not supported.")
	)

	class(h) = c("hash_table", paste0("hash_table_", cl))
	h
}

#' Low-level Functions
#' @param h hash table
#' @param keys keys
#' @param values values
#' @export
#' @rdname low_level_functions
hash_table_get_values = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = get_values_int(h, keys),
		"hash_table_logical"   = get_values_bool(h, keys),
		"hash_table_numeric"   = get_values_double(h, keys),
		"hash_table_character" = get_values_string(h, keys),
		"hash_table_Date"      = get_values_date(h, keys),
		"hash_table_POSIXct"   = get_values_time(h, keys),
		"hash_table_list"      = get_values_list(h, keys)
	)
}

#' @export
#' @rdname low_level_functions
hash_table_set_values = function(h, keys, values) {
	cl = class(h)[2]

	clv = class(values)[1]
	clh = gsub("hash_table_", "", cl)
	if(clv != clh) {
		stop("Data type of `values` (", clv, ") is not compatible with the hash table (", clh, ").")
	}

	switch(cl, 
		"hash_table_integer"   = set_values_int(h, keys, values),
		"hash_table_logical"   = set_values_bool(h, keys, values),
		"hash_table_numeric"   = set_values_double(h, keys, values),
		"hash_table_character" = set_values_string(h, keys, values),
		"hash_table_Date"      = set_values_date(h, keys, values),
		"hash_table_POSIXct"   = set_values_time(h, keys, values),
		"hash_table_list"      = set_values_list(h, keys, values)
	)
}

#' @export
#' @rdname low_level_functions
hash_table_delete_pairs = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = delete_pairs_int(h, keys),
		"hash_table_logical"   = delete_pairs_bool(h, keys),
		"hash_table_numeric"   = delete_pairs_double(h, keys),
		"hash_table_character" = delete_pairs_string(h, keys),
		"hash_table_Date"      = delete_pairs_date(h, keys),
		"hash_table_POSIXct"   = delete_pairs_time(h, keys),
		"hash_table_list"      = delete_pairs_list(h, keys)
	)
}

#' @export
#' @rdname low_level_functions
hash_table_size = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_size_int(h),
		"hash_table_logical"   = hash_table_size_bool(h),
		"hash_table_numeric"   = hash_table_size_double(h),
		"hash_table_character" = hash_table_size_string(h),
		"hash_table_Date"      = hash_table_size_date(h),
		"hash_table_POSIXct"   = hash_table_size_time(h),
		"hash_table_list"      = hash_table_size_list(h)
	)
}

#' @export
#' @rdname low_level_functions
hash_table_get_all_keys = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = get_all_keys_int(h),
		"hash_table_logical"   = get_all_keys_bool(h),
		"hash_table_numeric"   = get_all_keys_double(h),
		"hash_table_character" = get_all_keys_string(h),
		"hash_table_Date"      = get_all_keys_date(h),
		"hash_table_POSIXct"   = get_all_keys_time(h),
		"hash_table_list"      = get_all_keys_list(h)
	)
}

#' @export
#' @rdname low_level_functions
hash_table_get_all_values = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = get_all_values_int(h),
		"hash_table_logical"   = get_all_values_bool(h),
		"hash_table_numeric"   = get_all_values_double(h),
		"hash_table_character" = get_all_values_string(h),
		"hash_table_Date"      = get_all_values_date(h),
		"hash_table_POSIXct"   = get_all_values_time(h),
		"hash_table_list"      = get_all_values_list(h)
	)
}

#' Functions
#' @param h,x hash table
#' @param i,name keys
#' @param value Values
#' @export
#' @rdname high_level_functions
hash_table_keys = function(h) {
	hash_table_get_all_keys(h)
} 

#' @export
#' @rdname high_level_functions
hash_table_values = function(h) {
	hash_table_get_all_values(h)
}

#' @export
#' @rdname high_level_functions
"[[.hash_table" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of index in `[[` should only be one.")
	}
	if(inherits(x, "hash_table_list")) {
		hash_table_get_values(x, i)[[1]]
	} else {
		hash_table_get_values(x, i)
	}
}

#' @export
#' @rdname high_level_functions
"[.hash_table" = function(x, i) {
	hash_table_get_values(x, i)
}

#' @export
#' @rdname high_level_functions
"$.hash_table" = function(x, name) {
	if(inherits(x, "hash_table_list")) {
		hash_table_get_values(x, name)[[1]]
	} else {
		hash_table_get_values(x, name)
	}
}

#' @export
#' @rdname high_level_functions
"[[<-.hash_table" = function(x, i, value) {
	if(length(i) != 1) {
		stop("Length of index in `[[` should only be one.")
	}
	if(inherits(x, "hash_table_list")) {
		hash_table_set_values(x, i, list(value))
	} else {
		hash_table_set_values(x, i, value)
	}
	x
}

#' @export
#' @rdname high_level_functions
"[<-.hash_table" = function(x, i, value) {
	hash_table_set_values(x, i, value)
	x
}

#' @export
#' @rdname high_level_functions
"$<-.hash_table" = function(x, name, value) {
	if(inherits(x, "hash_table_list")) {
		hash_table_set_values(x, name, list(value))
	} else {
		hash_table_set_values(x, name, value)
	}
	x
}

#' @export
#' @rdname high_level_functions
length.hash_table = function(x) {
	hash_table_size(x)
}


#' @param ... Other arguments.
#' @export
#' @rdname high_level_functions
print.hash_table = function(x, ...) {
	cl = class(x)

	n = hash_table_size(x)
	keys = hash_table_keys(x)

	cat("A hash table with ", n, " key-value pair", ifelse(n > 1, "s", ""), "\n", sep = "")

	if(cl[2] %in% c("hash_table_integer", "hash_table_logical", "hash_table_numeric",
		         "hash_table_character", "hash_table_Date", "hash_table_POSIXct")) {
		if(n <= 6) {
			values = x[keys]
			for(i in seq_len(n)) {
				cat("  ", keys[i], " => ", values[i], "\n", sep = "")
			}
		} else {
			values = x[keys[1:3]]
			for(i in 1:3) {
				cat("  ", keys[i], " => ", values[i], "\n", sep = "")
			}
			cat("  ......\n", sep = "")
			values = x[keys[(n-2):n]]
			for(i in 1:3) {
				cat("  ", keys[i+n-3], " => ", values[i], "\n", sep = "")
			}
		}
	} else {
		if(n <= 6) {
			values = x[keys]
			for(i in seq_len(n)) {
				if(is.atomic(values[[i]])) {
					k = length(values[[i]])
					vtxt = paste0(class(values[[i]])[1], " [", ifelse(k == 1, "1", paste0(1,":",k)), "] ", paste(values[[i]], collapse = " "))
					cat("  ", keys[i], " => ", vtxt, "\n", sep = "")
				} else {
					cat("  ", keys[i], " => complex value\n", sep = "")
				}
			}
		} else {
			values = x[keys[1:3]]
			for(i in 1:3) {
				if(is.atomic(values[[i]])) {
					k = length(values[[i]])
					vtxt = paste0(class(values[[i]])[1], " [", ifelse(k == 1, "1", paste0(1,":",k)), "] ", paste(values[[i]], collapse = " "))
					cat("  ", keys[i], " => ", vtxt, "\n", sep = "")
				} else {
					cat("  ", keys[i], " => complex value\n", sep = "")
				}
			}
			cat("  ......\n", sep = "")
			values = x[keys[(n-2):n]]
			for(i in 1:3) {
				if(is.atomic(values[[i]])) {
					k = length(values[[i]])
					vtxt = paste0(class(values[[i]])[1], " [", ifelse(k == 1, "1", paste0(1,":",k)), "] ", paste(values[[i]], collapse = " "))
					cat("  ", keys[i+n-3], " => ", vtxt, "\n", sep = "")
				} else {
					cat("  ", keys[i+n-3], " => complex value\n", sep = "")
				}
			}
		}
	}
}

