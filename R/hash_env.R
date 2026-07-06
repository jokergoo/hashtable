
setClass("hash_env",
	slots = c(envir = "environment",
		      is_atomic = "logical",
		      value_class = "character"))

setClass("hash_env_set", contains = "hash_env")
setClass("hash_env_table", contains = "hash_env")


#' Hash table and hash set implemented by environment
#' 
#' @export
#' @param keys A character vector.
#' @param values An atomic vector or a list.
#' @rdname hash_env
#' 
#' @details
#' `hash_values()` and `[` methods on the `hash_env_table` object preserve the original format of `values`, which means, if `values`
#' was specified as an atomic vector, the two functions also returns atomic vectors.
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
	
	h = new("hash_env_table")

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

	if(is.list(values)) {
		lt = values
		names(lt) = keys
	} else {
		lt = split(values, keys)
	}
	e = list2env(lt, hash = TRUE, parent = emptyenv())
	
	h@envir = e
	h@is_atomic = is.atomic(values)
	h@value_class = class(values)[1]
	
	h
}

#' @export
#' @rdname hash_env
hash_env_set = function(keys) {
	if(is.null(keys)) {
		stop("`keys` cannot be NULL.")
	}
	if(any(duplicated(keys))) {
		stop("Keys should not be duplicated.")
	}
	h = new("hash_env_set")
	e = hash_env_hash_set_create(keys)

	h@envir = e
	
	h
}

#' @export
#' @rdname hash_env
#' @param h,x,object A `hash_env_table` returned by `hash_env_table()` or a `hash_env_set` object returned by `hash_env_set()`.
setMethod("hash_exists", signature = "hash_env",
	definition = function(h, keys) {
	internal_hash_env_exists(h@envir, keys)
})

#' @export
#' @rdname hash_env
setMethod("hash_delete", signature = "hash_env",
	definition = function(h, keys) {
	invisible(internal_hash_env_delete(h@envir, keys))
})

#' @export
#' @rdname hash_env
setMethod("hash_insert", signature = "hash_env_table",
	definition = function(h, keys, values) {
	
	if(h@is_atomic) {
		if(!inherits(values, h@value_class)) {
			stop("`values` should be ", h@value_class, ".")
		}

		switch(h@value_class,
			"logical" = internal_hash_env_set_values_logical(h@envir, keys, values),
			"integer" = internal_hash_env_set_values_integer(h@envir, keys, values),
			"numeric" = internal_hash_env_set_values_numeric(h@envir, keys, values),
			"character" = internal_hash_env_set_values_character(h@envir, keys, values),
			"Date" = internal_hash_env_set_values_date(h@envir, keys, values),
			"POSIXct" = internal_hash_env_set_values_time(h@envir, keys, values)
		)

	} else {
		if(is.list(values)) {
			if(length(keys) == 1) {
				assign(keys, values[[1]], envir = h$envir)
			} else {
				internal_hash_env_set_values_list(h@envir, keys, values)
			}
		} else {
			stop("if `values` is not atomics, it should be a list.")
		}
	}
	
	invisible(h)
})

#' @export
#' @rdname hash_env
setMethod("hash_insert", signature = "hash_env_set",
	definition = function(h, keys) {
	internal_hash_env_set_values_null(h@envir, keys)
	invisible(h)
})


#' @export
#' @rdname hash_env
setMethod("hash_size", signature = "hash_env",
	definition = function(h) {
	internal_hash_env_size(h@envir)
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
	ls(envir = h@envir, all.names = TRUE, sorted = FALSE)
})

#' @export
#' @rdname hash_env
setMethod("hash_values", signature = "hash_env_table",
	definition = function(h, keys = NULL) {

	if(is.null(keys)) {
		keys = hash_keys(h)
	}
	if(length(keys) == 1) {
		get(keys, envir = h@envir, inherits = FALSE)
	} else {
		if(h@is_atomic) {
			switch(h@value_class,
				"logical" = internal_hash_env_values_logical(h@envir, keys),
				"integer" = internal_hash_env_values_integer(h@envir, keys),
				"numeric" = internal_hash_env_values_numeric(h@envir, keys),
				"character" = internal_hash_env_values_character(h@envir, keys),
				"Date" = internal_hash_env_values_date(h@envir, keys),
				"POSIXct" = internal_hash_env_values_time(h@envir, keys)
			)
		} else {
			unname(mget(keys, envir = h@envir, inherits = FALSE))
		}
	}
})

#' @export
#' @rdname hash_env
setMethod("hash_values", signature = "hash_env_set",
	definition = function(h, keys = NULL) {
	hash_exists(h, keys)
})

#' @export
#' @rdname hash_env
setMethod("hash_copy", signature = "hash_env",
	definition = function(h) {
	h2 = h
	h2@env = hash_env_copy(h@envir)
	h2
})


#' @export
#' @rdname hash_env
#' @param i,name,value Keys and values.
"[[.hash_env" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of the index should be 1.")
	}
	hash_values(x, i)[[1]]
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
"[.hash_env" = function(x, i) {
	hash_values(x, i)
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

	are_values_atomic = object@is_atomic

	print_key_value_pairs(object, are_values_atomic)
})

#' @export
#' @rdname hash_env
setMethod("show", signature = "hash_env_set",
	definition = function(object) {

	n = hash_size(object)
	keys = hash_keys(object)

	cat("A hash set [hash_env_set] with ", n, " key", ifelse(n > 1, "s", ""), " (character)\n", sep = "")
})


