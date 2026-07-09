
setClass("hash_env",
	slots = c(envir = "environment",
		      is_atomic = "logical",
		      value_class = "character"))

setClass("hash_env_set", contains = "hash_env")
setClass("hash_env_table", contains = "hash_env")


#' Hash table and hash set implemented by environment
#' 
#' @export
#' @param keys A character vector. Keys should have no duplicates.
#' @param values An atomic vector or a list.
#' @rdname hash_env
#' 
#' @details
#' `hash_values()` and `[` methods on the `hash_env_table` object preserve the original format of `values`, which means, if `values`
#' was specified as an atomic vector, the two functions also returns atomic vectors.
#' 
#' @return
#' `hash_env_table()` returns a `hash_env_table` object. `hash_env_set()` returns a `hash_env_set` object.
#' `hash_env_delete()`, `hash_env_insert()`, `hash_env_copy()` return a `hash_env_table` object
#' or a `hash_env_set` object. `hash_exists()` returns a logical vector. `hash_size()` returns an integer. `hash_keys()` returns 
#' a character vector. `hash_values()` on the `hash_env_table` object returns a vector of a list which has the same format as in the
#' constructor function. `hash_values()` on the `hash_env_set` object throws an error.
#' 
#' @examples
#' h = hash_env_table(letters, 1:26)
#' hash_keys(h)
#' hash_values(h)
#' h$a
#' 
#' h = hash_env_set(letters)
#' hash_exists(h, "a")
hash_env_table = function(keys, values) {
	
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
	
	h = new("hash_env_table")
	cl = class(values)[1]
	h@value_class = cl
	h@is_atomic = is.atomic(values)
	h@envir = switch(cl, 
		"integer"   = cpp_hash_env_table_create_int(keys, values),
		"logical"   = cpp_hash_env_table_create_bool(keys, values),
		"numeric"   = cpp_hash_env_table_create_double(keys, values),
		"character" = cpp_hash_env_table_create_string(keys, values),
		"Date"      = cpp_hash_env_table_create_date(keys, values),
		"POSIXct"   = cpp_hash_env_table_create_time(keys, values),
		"list"      = cpp_hash_env_table_create_list(keys, values),
		stop("Data type of `values` ('", cl, "') is not supported.")
	)
	h
}

#' @export
#' @rdname hash_env
hash_env_set = function(keys) {
	h = new("hash_env_set")
	h@envir = cpp_hash_env_table_create_bool(keys, rep(TRUE, length(keys)))
	h
}

#' @export
#' @rdname hash_env
#' @param h,x,object A `hash_env_table` returned by `hash_env_table()` or a `hash_env_set` object returned by `hash_env_set()`.
setMethod("hash_exists", signature = "hash_env",
	definition = function(h, keys) {
	cpp_hash_env_exists(h@envir, keys)
})

#' @export
#' @rdname hash_env
setMethod("hash_delete", signature = "hash_env",
	definition = function(h, keys) {
	invisible(cpp_hash_env_delete(h@envir, keys))
})

#' @export
#' @rdname hash_env
setMethod("hash_insert", signature = "hash_env_table",
	definition = function(h, keys, values) {
	
	cl = h@value_class
	clv = class(values)[1]
	if(clv != cl) {
		stop("Data type of `values` (", clv, ") is not compatible with the hash table (", cl, ").")
	}

	switch(cl, 
		"integer"   = cpp_hash_env_table_insert_int(h@envir, keys, values),
		"logical"   = cpp_hash_env_table_insert_bool(h@envir, keys, values),
		"numeric"   = cpp_hash_env_table_insert_double(h@envir, keys, values),
		"character" = cpp_hash_env_table_insert_string(h@envir, keys, values),
		"Date"      = cpp_hash_env_table_insert_date(h@envir, keys, values),
		"POSIXct"   = cpp_hash_env_table_insert_time(h@envir, keys, values),
		"list"      = cpp_hash_env_table_insert_list(h@envir, keys, values)
	)
	invisible(h)
})

#' @export
#' @rdname hash_env
setMethod("hash_insert", signature = "hash_env_set",
	definition = function(h, keys) {

	n = length(keys)
	values = rep(list(NULL), n)

	cpp_hash_env_table_insert_list(h@envir, keys, values)
	
	invisible(h)
})


#' @export
#' @rdname hash_env
setMethod("hash_size", signature = "hash_env",
	definition = function(h) {
	cpp_hash_env_size(h@envir)
})

#' @export
#' @rdname hash_env
length.hash_env = function(x) {
	hash_size(x)
}

#' @export
#' @rdname hash_env
setMethod("hash_keys", signature = "hash_env",
	definition = function(h) {
	cpp_hash_env_keys(h@envir)
})

#' @export
#' @rdname hash_env
setMethod("hash_values", signature = "hash_env_table",
	definition = function(h, keys = NULL) {

	cl = h@value_class
	if(is.null(keys)) {
		switch(cl, 
			"integer"   = cpp_hash_env_table_all_values_int(h@envir),
			"logical"   = cpp_hash_env_table_all_values_bool(h@envir),
			"numeric"   = cpp_hash_env_table_all_values_double(h@envir),
			"character" = cpp_hash_env_table_all_values_string(h@envir),
			"Date"      = cpp_hash_env_table_all_values_date(h@envir),
			"POSIXct"   = cpp_hash_env_table_all_values_time(h@envir),
			"list"      = cpp_hash_env_table_all_values_list(h@envir)
		)
	} else {
		switch(cl, 
			"integer"   = cpp_hash_env_table_values_int(h@envir, keys),
			"logical"   = cpp_hash_env_table_values_bool(h@envir, keys),
			"numeric"   = cpp_hash_env_table_values_double(h@envir, keys),
			"character" = cpp_hash_env_table_values_string(h@envir, keys),
			"Date"      = cpp_hash_env_table_values_date(h@envir, keys),
			"POSIXct"   = cpp_hash_env_table_values_time(h@envir, keys),
			"list"      = cpp_hash_env_table_values_list(h@envir, keys)
		)
	}
})

#' @export
#' @rdname hash_env
setMethod("hash_values", signature = "hash_env_set",
	definition = function(h, keys = NULL) {
	stop("hash_env_set has no values.")
})

#' @export
#' @rdname hash_env
setMethod("hash_copy", signature = "hash_env",
	definition = function(h) {
	h2 = h
	h2@env = cpp_hash_env_copy(h@envir)
	h2
})


#' @export
#' @rdname hash_env
#' @param i,name,value Keys and values.
"[[.hash_env_table" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of the index should be 1.")
	}
	hash_values(x, i)[[1]]
}

#' @export
#' @rdname hash_env
#' @param i,name,value Keys and values.
"[[.hash_env_set" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of the index should be 1.")
	}
	hash_exists(x, i)
}

#' @export
#' @rdname hash_env
"[[<-.hash_env_table" = function(x, i, value) {
	if(length(i) != 1) {
		stop("Length of the index should be 1.")
	}
	if(x@is_atomic) {
		hash_insert(x, i, value)
	} else {
		hash_insert(x, i, list(value))
	}
	x
}

#' @export
#' @rdname hash_env
"[.hash_env_table" = function(x, i) {
	hash_values(x, i)
}

#' @export
#' @rdname hash_env
"[.hash_env_set" = function(x, i) {
	hash_exists(x, i)
}

#' @export
#' @rdname hash_env
"[<-.hash_env_table" = function(x, i, value) {
	hash_insert(x, i, value)
	x
}

#' @export
#' @rdname hash_env
"$.hash_env" = function(x, name) {
	x[[name]]
}

#' @export
#' @rdname hash_env
"$<-.hash_env_table" = function(x, i, value) {
	x[[i]] = value
	x
}


#' @export
#' @rdname hash_env
"[[<-.hash_env_set" = function(x, i, value) {
	if(is.null(value)) value = FALSE
	if(length(i) != 1) {
		stop("Length of index should only be one.")
	}

	if(is.logical(value)) {
		if(value) {
			hash_insert(x, i)
		} else {
			hash_delete(x, i)
		}
	} else {
		stop("`value` should be logical.")
	}
	x
}

#' @export
#' @rdname hash_env
"[<-.hash_env_set" = function(x, i, value) {
	if(is.null(value)) value = FALSE
	if(is.logical(value)) {
		if(length(value) == 1) {
			if(value) {
				hash_insert(x, i)
			} else {
				hash_delete(x, i)
			}
		} else {
			if(any(value)) {
				hash_insert(x, i[value])
			}
			if(any(!value)) {
				hash_delete(x, i[!value])
			}
		}
	} else {
		stop("`value` should be logical.")
	}
	x
}

#' @export
#' @rdname hash_env
"$<-.hash_env_set" = function(x, name, value) {
	x[[name]] = value
	x
}


#' @export
#' @rdname hash_env
as.hash_env = function(x) {
	UseMethod("as.hash_env")
}

#' @export
#' @rdname hash_env
as.hash_env.default = function(x) {
	nm = names(x)
	if(is.null(nm)) {
		if(is.atomic(x) && is.character(x)) {
			h = hash_env_set(x)
			return(h)
		} 
		stop("`x` should have names.")
	}

	hash_env_table(nm, x)
}

#' @export
#' @rdname hash_env
#' @param mode,... Please ignore.
as.vector.hash_env_set = function(x, mode = "any") {
	names(x@envir)
}

#' @export
#' @rdname hash_env
as.vector.hash_env_table = function(x, mode = "any") {
	structure(hash_values(x), names = hash_keys(x))
}

#' @export
#' @rdname hash_env
as.list.hash_env_table = function(x, ...) {
	as.list(x@envir)
}

#' @export
#' @rdname hash_env
setMethod("show", signature = "hash_env_table",
	definition = function(object) {

	n = hash_size(object)
	
	cl = object@value_class

	cat("A hash table [hash_env_table] with ", n, " key-value (", cl, ") pair", ifelse(n > 1, "s", ""), "\n", sep = "")

	print_key_value_pairs(object, object@is_atomic)
})

#' @export
#' @rdname hash_env
setMethod("show", signature = "hash_env_set",
	definition = function(object) {

	n = hash_size(object)
	keys = hash_keys(object)

	cat("A hash set [hash_env_set] with ", n, " key", ifelse(n > 1, "s", ""), " (character)\n", sep = "")
})


