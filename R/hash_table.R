
setClass("hash_unordered_map",
	slots = c(ptr = "ANY",
			  is_atomic = "logical",
		      value_class = "character"))


#' Hash table implemented by std::unordered_map
#' 
#' @export
#' @param keys A character vector. Keys should have no duplicates.
#' @param values An atomic vector or a list.
#' @rdname hash_table
#' @import methods
#' @import Rcpp
#' @useDynLib hashtable, .registration = TRUE
#' 
#' @details
#' `hash_values()` and `[` methods preserve the original format of `values`, which means, if `values`
#' was specified as an atomic vector, the two functions also returns atomic vectors.
#' 
#' @examples
#' hash_table(c("a", "b"), 1:2L)
#' hash_table(c("a", "b"), c(TRUE, FALSE))
#' hash_table(c("a", "b"), c(0.1, 0.2))
#' hash_table(c("a", "b"), c("one", "two"))
#' hash_table(c("a", "b"), as.Date(c("2025-01-01", "2025-02-01")))
#' hash_table(c("a", "b"), as.POSIXct(c("2025-01-01 00:00:01", "2025-02-01 00:00:01")))
#' hash_table(c("a", "b"), list(1:10, letters))
#' 
#' h = hash_table(letters, 1:26)
#' hash_keys(h)
#' hash_values(h)
#' hash_exists(h, c("a", "b", "foo"))
#' hash_delete(h, letters[1:20]); h
#' hash_insert(h, "foo", 100L) 
#' 
#' h = hash_table(letters, 1:26)
#' h$a
#' h[["a"]]
#' h[c("a", "b")]
#' 
#' as.vector(h)
#' as.list(h)
hash_table = function(keys, values) {
	if(is.null(keys)) {
		stop("`keys` cannot be NULL.")
	}
	if(is.null(values)) {
		stop("`values` cannot be NULL.")
	}
	if(!is.character(keys)) {
		stop("`keys` should be character.")
	}
	if(length(keys) != length(values)) {
		stop("`keys` and `values` should have the same length.")
	}

	if(any(duplicated(keys))) {
		stop("`keys` should not be duplicated.")
	}
	

	h = new("hash_unordered_map")
	cl = class(values)[1]
	h@value_class = cl
	h@is_atomic = is.atomic(values)
	h@ptr = switch(cl, 
		"integer"   = hash_table_create_int(keys, values),
		"logical"   = hash_table_create_bool(keys, values),
		"numeric"   = hash_table_create_double(keys, values),
		"character" = hash_table_create_string(keys, values),
		"Date"      = hash_table_create_date(keys, values),
		"POSIXct"   = hash_table_create_time(keys, values),
		"list"      = hash_table_create_list(keys, values),
		stop("Data type of `values` ('", cl, "') is not supported.")
	)

	h
}

#' @rdname hash_table
#' @export
#' @param h,x,object A `hash_unordered_map` object returned by `hash_table()`.
setMethod("hash_values", signature = "hash_unordered_map",
	definition = function(h, keys = NULL) {
	cl = h@value_class
	if(is.null(keys)) {
		switch(cl, 
			"integer"   = hash_table_get_all_values_int(h@ptr),
			"logical"   = hash_table_get_all_values_bool(h@ptr),
			"numeric"   = hash_table_get_all_values_double(h@ptr),
			"character" = hash_table_get_all_values_string(h@ptr),
			"Date"      = hash_table_get_all_values_date(h@ptr),
			"POSIXct"   = hash_table_get_all_values_time(h@ptr),
			"list"      = hash_table_get_all_values_list(h@ptr)
		)
	} else {
		switch(cl, 
			"integer"   = hash_table_get_values_int(h@ptr, keys),
			"logical"   = hash_table_get_values_bool(h@ptr, keys),
			"numeric"   = hash_table_get_values_double(h@ptr, keys),
			"character" = hash_table_get_values_string(h@ptr, keys),
			"Date"      = hash_table_get_values_date(h@ptr, keys),
			"POSIXct"   = hash_table_get_values_time(h@ptr, keys),
			"list"      = hash_table_get_values_list(h@ptr, keys)
		)
	}
})

#' @rdname hash_table
#' @export
setMethod("hash_exists", signature = "hash_unordered_map",
	definition = function(h, keys) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_table_exists_int(h@ptr, keys),
		"logical"   = hash_table_exists_bool(h@ptr, keys),
		"numeric"   = hash_table_exists_double(h@ptr, keys),
		"character" = hash_table_exists_string(h@ptr, keys),
		"Date"      = hash_table_exists_date(h@ptr, keys),
		"POSIXct"   = hash_table_exists_time(h@ptr, keys),
		"list"      = hash_table_exists_list(h@ptr, keys)
	)
})

#' @rdname hash_table
#' @export
setMethod("hash_insert", signature = "hash_unordered_map",
	definition = function(h, keys, values) {
	cl = h@value_class
	clv = class(values)[1]
	if(clv != cl) {
		stop("Data type of `values` (", clv, ") is not compatible with the hash table (", cl, ").")
	}

	switch(cl, 
		"integer"   = hash_table_set_values_int(h@ptr, keys, values),
		"logical"   = hash_table_set_values_bool(h@ptr, keys, values),
		"numeric"   = hash_table_set_values_double(h@ptr, keys, values),
		"character" = hash_table_set_values_string(h@ptr, keys, values),
		"Date"      = hash_table_set_values_date(h@ptr, keys, values),
		"POSIXct"   = hash_table_set_values_time(h@ptr, keys, values),
		"list"      = hash_table_set_values_list(h@ptr, keys, values)
	)
	invisible(h)
})

#' @rdname hash_table
#' @export
setMethod("hash_delete", signature = "hash_unordered_map",
	definition = function(h, keys) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_table_delete_pairs_int(h@ptr, keys),
		"logical"   = hash_table_delete_pairs_bool(h@ptr, keys),
		"numeric"   = hash_table_delete_pairs_double(h@ptr, keys),
		"character" = hash_table_delete_pairs_string(h@ptr, keys),
		"Date"      = hash_table_delete_pairs_date(h@ptr, keys),
		"POSIXct"   = hash_table_delete_pairs_time(h@ptr, keys),
		"list"      = hash_table_delete_pairs_list(h@ptr, keys)
	)
})

#' @rdname hash_table
#' @export
setMethod("hash_size", signature = "hash_unordered_map",
	definition = function(h) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_table_size_int(h@ptr),
		"logical"   = hash_table_size_bool(h@ptr),
		"numeric"   = hash_table_size_double(h@ptr),
		"character" = hash_table_size_string(h@ptr),
		"Date"      = hash_table_size_date(h@ptr),
		"POSIXct"   = hash_table_size_time(h@ptr),
		"list"      = hash_table_size_list(h@ptr)
	)
})

#' @rdname hash_table
#' @export
length.hash_unordered_map = function(x) {
	hash_size(x)
}


#' @rdname hash_table
#' @export
setMethod("hash_keys", signature = "hash_unordered_map",
	definition = function(h) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_table_get_all_keys_int(h@ptr),
		"logical"   = hash_table_get_all_keys_bool(h@ptr),
		"numeric"   = hash_table_get_all_keys_double(h@ptr),
		"character" = hash_table_get_all_keys_string(h@ptr),
		"Date"      = hash_table_get_all_keys_date(h@ptr),
		"POSIXct"   = hash_table_get_all_keys_time(h@ptr),
		"list"      = hash_table_get_all_keys_list(h@ptr)
	)
})

#' @rdname hash_table
#' @export
setMethod("hash_copy", signature = "hash_unordered_map",
	definition = function(h) {
	h2 = new("hash_unordered_map")
	cl = h@value_class
	h2@value_class = cl
	h2@is_atomic = h@is_atomic
	h2@ptr = switch(cl, 
		"integer"   = hash_table_copy_int(h@ptr),
		"logical"   = hash_table_copy_bool(h@ptr),
		"numeric"   = hash_table_copy_double(h@ptr),
		"character" = hash_table_copy_string(h@ptr),
		"Date"      = hash_table_copy_date(h@ptr),
		"POSIXct"   = hash_table_copy_time(h@ptr),
		"list"      = hash_table_copy_list(h@ptr)
	)
	h2
})


#' @rdname hash_table
#' @export
#' @param i,name,value Keys and values.
"[[.hash_unordered_map" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of index should only be one.")
	}
	hash_values(x, i)[[1]]
}

#' @rdname hash_table
#' @export
"[.hash_unordered_map" = function(x, i) {
	hash_values(x, i)
}


#' @rdname hash_table
#' @export
"$.hash_unordered_map" = function(x, name) {
	x[[name]]
}

#' @rdname hash_table
#' @export
"[[<-.hash_unordered_map" = function(x, i, value) {
	if(length(i) != 1) {
		stop("Length of index should only be one.")
	}
	if(x@is_atomic) {
		hash_insert(x, i, value)
	} else {
		hash_insert(x, i, list(value))
	}
	x
}


#' @rdname hash_table
#' @export
"[<-.hash_unordered_map" = function(x, i, value) {
	hash_insert(x, i, value)
	x
}

#' @rdname hash_table
#' @export
"$<-.hash_unordered_map" = function(x, name, value) {
	x[[name]] = value
	x
}

#' @rdname hash_table
#' @export
setMethod("show", signature = "hash_unordered_map",
	definition = function(object) {
	cl = object@value_class
	n = hash_size(object)
	cat("A hash table [hash_unordered_map] with ", n, " key-value (", cl, ") pair", ifelse(n > 1, "s", ""), "\n", sep = "")
	print_key_value_pairs(object, object@is_atomic)
})

print_key_value_pairs = function(x, are_values_atomic) {

	keys = hash_keys(x)
	n = hash_size(x)

	if(are_values_atomic) {
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

#' @rdname hash_table
#' @export
as.hash_table = function(x) {
	UseMethod("as.hash_table")
}

#' @rdname hash_table
#' @export
as.hash_table.default = function(x) {
	nm = names(x)
	if(is.null(nm)) {
		stop("`x` should have names.")
	}
	hash_table(nm, x)
}

#' @rdname hash_table
#' @export
#' @param mode,... Please ignore.
as.vector.hash_unordered_map = function(x, mode = "any") {
	structure(hash_values(x), names = hash_keys(x))
}

#' @rdname hash_table
#' @export
as.list.hash_unordered_map = function(x, ...) {
	if(x@is_atomic) {
		structure(as.list(hash_values(x)), names = hash_keys(x))
	} else {
		structure(hash_values(x), names = hash_keys(x))
	}
}



