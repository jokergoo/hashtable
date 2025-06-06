

#' Hash table
#' @param keys Keys as a character vector.
#' @param values Values. It supports vectors in the following classes: integer, logical, numeric, character, Date, POSIXct and list (i.e. a list of R objects).
#'
#' @import Rcpp
#' @export
#' @useDynLib hashtable, .registration = TRUE
#' @return A `hash_table` object.
#' @examples
#' hash_table(c("a", "b"), 1:2L)
#' hash_table(c("a", "b"), c(TRUE, FALSE))
#' hash_table(c("a", "b"), c(0.1, 0.2))
#' hash_table(c("a", "b"), c("one", "two"))
#' hash_table(c("a", "b"), as.Date(c("2025-01-01", "2025-02-01")))
#' hash_table(c("a", "b"), as.POSIXct(c("2025-01-01 00:00:01", "2025-02-01 00:00:01")))
#' hash_table(c("a", "b"), list(1:10, letters))
#' 
#' # a nested hash table
#' h = hash_table_empty("Robj")
#' h$a = hash_table_empty("Robj")
#' h$a$b = hash_table("c", 1L)
#' h$a$b$c
hash_table = function(keys, values) {
	if(missing(keys)) {
		stop("If you want to create an empty hash table, use the form 'hash_table(character(0), numeric(0))' where you can replace 'numeric(0)' to other data types you are using.")
	}
	if(length(keys) == 0 && length(values) > 0) {
		stop("You should provide keys.")
	}
	if(!is.character(keys)) {
		stop("`keys` should be character.")
	}
	if(length(keys) != length(values)) {
		stop("`keys` and `values` should have the same length.")
	}
	cl = class(values)[1]
	h = switch(cl, 
		"integer"   = hash_table_create_int(keys, values),
		"logical"   = hash_table_create_bool(keys, values),
		"numeric"   = hash_table_create_double(keys, values),
		"character" = hash_table_create_string(keys, values),
		"Date"      = hash_table_create_date(keys, values),
		"POSIXct"   = hash_table_create_time(keys, values),
		"list"      = hash_table_create_list(keys, values),
		stop("Data type of `values` ('", cl, "') is not supported.")
	)

	class(h) = c("hash_table", paste0("hash_table_", cl))
	h
}

#' Low-level functions for hash tables
#' @param h A `hash_table` object.
#' @param keys A character vector of keys.
#' @param values The corresponding values.
#' @export
#' @rdname low_level_functions_hash_table
#' @return
#' - `hash_table_get_values()` returns a vector of values.
#' - `hash_table_exists()` returns a logical vector.
#' - `hash_table_set_values()`/`hash_table_delete_pairs()`/`hash_table_clear()` directly modifies the input object `h`.
#' - `hash_table_size()` returns a single integer.
#' - `hash_table_get_all_keys()` returns a vector of all keys.
#' - `hash_table_get_all_values()` returns a vector of all values.
#' - `hash_table_copy()` returns a new hash table.
#' @examples
#' h = hash_table(c("a", "b"), 1:2L)
#' hash_table_get_values(h, "a")
#' hash_table_exists(h, c("a", "c"))
#' hash_table_set_values(h, "a", 100L)
#' hash_table_get_values(h, "a")
#' hash_table_delete_pairs(h, "a")
#' h
#' hash_table_clear(h)
#' h
hash_table_get_values = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_get_values_int(h, keys),
		"hash_table_logical"   = hash_table_get_values_bool(h, keys),
		"hash_table_numeric"   = hash_table_get_values_double(h, keys),
		"hash_table_character" = hash_table_get_values_string(h, keys),
		"hash_table_Date"      = hash_table_get_values_date(h, keys),
		"hash_table_POSIXct"   = hash_table_get_values_time(h, keys),
		"hash_table_list"      = hash_table_get_values_list(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_exists = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_exists_int(h, keys),
		"hash_table_logical"   = hash_table_exists_bool(h, keys),
		"hash_table_numeric"   = hash_table_exists_double(h, keys),
		"hash_table_character" = hash_table_exists_string(h, keys),
		"hash_table_Date"      = hash_table_exists_date(h, keys),
		"hash_table_POSIXct"   = hash_table_exists_time(h, keys),
		"hash_table_list"      = hash_table_exists_list(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_set_values = function(h, keys, values) {
	cl = class(h)[2]

	clv = class(values)[1]
	clh = gsub("hash_table_", "", cl)
	if(clv != clh) {
		stop("Data type of `values` (", clv, ") is not compatible with the hash table (", clh, ").")
	}

	switch(cl, 
		"hash_table_integer"   = hash_table_set_values_int(h, keys, values),
		"hash_table_logical"   = hash_table_set_values_bool(h, keys, values),
		"hash_table_numeric"   = hash_table_set_values_double(h, keys, values),
		"hash_table_character" = hash_table_set_values_string(h, keys, values),
		"hash_table_Date"      = hash_table_set_values_date(h, keys, values),
		"hash_table_POSIXct"   = hash_table_set_values_time(h, keys, values),
		"hash_table_list"      = hash_table_set_values_list(h, keys, values)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_delete_pairs = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_delete_pairs_int(h, keys),
		"hash_table_logical"   = hash_table_delete_pairs_bool(h, keys),
		"hash_table_numeric"   = hash_table_delete_pairs_double(h, keys),
		"hash_table_character" = hash_table_delete_pairs_string(h, keys),
		"hash_table_Date"      = hash_table_delete_pairs_date(h, keys),
		"hash_table_POSIXct"   = hash_table_delete_pairs_time(h, keys),
		"hash_table_list"      = hash_table_delete_pairs_list(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
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
#' @rdname low_level_functions_hash_table
hash_table_get_all_keys = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_get_all_keys_int(h),
		"hash_table_logical"   = hash_table_get_all_keys_bool(h),
		"hash_table_numeric"   = hash_table_get_all_keys_double(h),
		"hash_table_character" = hash_table_get_all_keys_string(h),
		"hash_table_Date"      = hash_table_get_all_keys_date(h),
		"hash_table_POSIXct"   = hash_table_get_all_keys_time(h),
		"hash_table_list"      = hash_table_get_all_keys_list(h)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_get_all_values = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_get_all_values_int(h),
		"hash_table_logical"   = hash_table_get_all_values_bool(h),
		"hash_table_numeric"   = hash_table_get_all_values_double(h),
		"hash_table_character" = hash_table_get_all_values_string(h),
		"hash_table_Date"      = hash_table_get_all_values_date(h),
		"hash_table_POSIXct"   = hash_table_get_all_values_time(h),
		"hash_table_list"      = hash_table_get_all_values_list(h)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_clear = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_table_integer"   = hash_table_clear_int(h),
		"hash_table_logical"   = hash_table_clear_bool(h),
		"hash_table_numeric"   = hash_table_clear_double(h),
		"hash_table_character" = hash_table_clear_string(h),
		"hash_table_Date"      = hash_table_clear_date(h),
		"hash_table_POSIXct"   = hash_table_clear_time(h),
		"hash_table_list"      = hash_table_clear_list(h)
	)
}

#' @export
#' @rdname low_level_functions_hash_table
hash_table_copy = function(h) {
	cl = class(h)[2]
	h2 = switch(cl, 
		"hash_table_integer"   = hash_table_copy_int(h),
		"hash_table_logical"   = hash_table_copy_bool(h),
		"hash_table_numeric"   = hash_table_copy_double(h),
		"hash_table_character" = hash_table_copy_string(h),
		"hash_table_Date"      = hash_table_copy_date(h),
		"hash_table_POSIXct"   = hash_table_copy_time(h),
		"hash_table_list"      = hash_table_copy_list(h)
	)
	class(h2) = class(h)
	h2
}

#' High-level functions for hash tables
#' @param h,x A `hash_table` object.
#' @param i,name A single or a vector of character keys.
#' @param value The corresponding values.
#' @export
#' @rdname high_level_functions_hash_table
#' @return
#' - `hash_table_keys()` returns a vector of all keys. 
#' - `hash_table_values()` returns a vector of all values. 
#' - `[[` or `$` returns a single value. 
#' - `[` returns a vector of values.
#' @examples
#' h = hash_table(c("a", "b"), 1:2L)
#' hash_table_keys(h)
#' hash_table_values(h)
#' h[["a"]]
#' h$a
#' h[c("a", "b")]
#' h[["a"]] = 10L
#' h[["a"]]
#' h$a = 100L
#' h$a
#' length(h)
hash_table_keys = function(h) {
	hash_table_get_all_keys(h)
} 

#' @export
#' @rdname high_level_functions_hash_table
hash_table_values = function(h) {
	hash_table_get_all_values(h)
}

#' @export
#' @rdname high_level_functions_hash_table
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
#' @rdname high_level_functions_hash_table
#' @details
#' For `[` and `[<-` methods, multiple keys are allowed.
"[.hash_table" = function(x, i) {
	hash_table_get_values(x, i)
}

#' @export
#' @rdname high_level_functions_hash_table
"$.hash_table" = function(x, name) {
	if(inherits(x, "hash_table_list")) {
		hash_table_get_values(x, name)[[1]]
	} else {
		hash_table_get_values(x, name)
	}
}

#' @export
#' @rdname high_level_functions_hash_table
#' @details
#' For the assignment, when the values in the hash table are not R object, if the assigned value is `NULL`,
#' the corresponding key-value pair is deleted.
#' @examples
#' h = hash_table(c("a", "b"), 1:2L)
#' h$a = NULL
#' h
"[[<-.hash_table" = function(x, i, value) {
	if(length(i) != 1) {
		stop("Length of index in `[[` should only be one.")
	}
	if(inherits(x, "hash_table_list")) {
		hash_table_set_values(x, i, list(value))
	} else {
		if(is.null(value)) {
			hash_table_delete_pairs(x, i)
		} else {
			hash_table_set_values(x, i, value)
		}
	}
	x
}

#' @export
#' @rdname high_level_functions_hash_table
"[<-.hash_table" = function(x, i, value) {
	if(inherits(x, "hash_table_list")) {
		hash_table_set_values(x, i, value)
	} else {
		if(is.null(value)) {
			hash_table_delete_pairs(x, i)
		} else {
			hash_table_set_values(x, i, value)
		}
	}
	x
}

#' @export
#' @rdname high_level_functions_hash_table
"$<-.hash_table" = function(x, name, value) {
	if(inherits(x, "hash_table_list")) {
		hash_table_set_values(x, name, list(value))
	} else {
		if(is.null(value)) {
			hash_table_delete_pairs(x, name)
		} else {
			hash_table_set_values(x, name, value)
		}
	}
	x
}

#' @export
#' @rdname high_level_functions_hash_table
length.hash_table = function(x) {
	hash_table_size(x)
}


#' @param ... Other arguments.
#' @export
#' @rdname high_level_functions_hash_table
print.hash_table = function(x, ...) {
	cl = class(x)

	n = hash_table_size(x)
	keys = hash_table_keys(x)

	cl_name = gsub("hash_table_", "", cl[2])
	if(cl_name == "list") cl_name = "R object"
	cat("A hash table with ", n, " key-value (", cl_name, ") pair", ifelse(n > 1, "s", ""), "\n", sep = "")

	if(cl[2] %in% c("hash_table_integer", "hash_table_logical", "hash_table_numeric",
		         "hash_table_character", "hash_table_Date", "hash_table_POSIXct")) {
		if(n <= 6) {
			values = as.character(x[keys])
			for(i in seq_len(n)) {
				cat("  ", keys[i], " => ", values[i], "\n", sep = "")
			}
		} else {
			values = as.character(x[keys[1:3]])
			for(i in 1:3) {
				cat("  ", keys[i], " => ", values[i], "\n", sep = "")
			}
			cat("  ......\n", sep = "")
			values = as.character(x[keys[(n-2):n]])
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
					cl = class(values[[i]])
					cat("  ", keys[i], " => complex value (", cl[length(cl)], ")\n", sep = "")
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
					cl = class(values[[i]])
					cat("  ", keys[i], " => complex value(", cl[length(cl)], ")\n", sep = "")
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
					cl = class(values[[i]])
					cat("  ", keys[i+n-3], " => complex value(", cl[length(cl)], ")\n", sep = "")
				}
			}
		}
	}
}


#' Convert to a hash table
#' 
#' @param x The input vector-like object with names.
#' 
#' @export
#' @return A hash table.
#' @rdname as_hash_table
#' @examples
#' as.hash_table(c("a" = 1L, "b" = 2L))
#' as.hash_table(c("a" = 1, "b" = 2))
#' as.hash_table(c("a" = TRUE, "b" = FALSE))
#' as.hash_table(c("a" = "one", "b" = "two"))
#' as.hash_table(c("a" = as.Date("2025-01-01"), 
#'                 "b" = as.Date("2025-02-01")))
#' as.hash_table(c("a" = as.POSIXct("2025-01-01 00:00:01"), 
#'                 "b" = as.POSIXct("2025-02-01 00:00:01")))
#' as.hash_table(list("a" = 1:10, "b" = letters))
as.hash_table = function(x) {
	UseMethod("as.hash_table")
}

#' @export
#' @rdname as_hash_table
as.hash_table.integer = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.numeric = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.character = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.logical = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.Date = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.POSIXct = function(x) {
	hash_table(names(x), x)
}

#' @export
#' @rdname as_hash_table
as.hash_table.list = function(x) {
	hash_table(names(x), x)
}


#' @rdname hash_table
#' @param cl One of "integer", "logical", "numeric", "character", "Date", "POSIXct" and "Robj".
#' @export
#' @examples
#' hash_table_empty("integer")
#' hash_table_empty("character")
#' hash_table_empty("Robj")
hash_table_empty = function(cl) {
	switch(cl, 
		"integer" = hash_table(character(0), integer(0)),
		"numeric" = hash_table(character(0), numeric(0)),
		"character" = hash_table(character(0), character(0)),
		"logical" = hash_table(character(0), logical(0)),
		"Date" = hash_table(character(0), structure(integer(0), class = "Date")),
		"POSIXct" = hash_table(character(0), structure(numeric(0), class = c("POSIXct", "POSIXt"))),
		"Robj" = hash_table(character(0), list()),
		"Robject" = hash_table(character(0), list()),
		"Wrong class"
	)
}




