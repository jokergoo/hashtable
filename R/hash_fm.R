setClass("hash_fm",
	slots = c(table = "character",
		      is_atomic = "logical",
		      values = "ANY"))

setClass("hash_fm_set", contains = "hash_fm")
setClass("hash_fm_table", contains = "hash_fm")


#' Hash table and hash set implemented by fastmatch
#' 
#' @export
#' @param keys A character vector.
#' @param values An atomic vector or a list.
#' @rdname hash_fm
#' @import fastmatch
#' 
#' @details
#' `hash_values()` and `[` methods on the `hash_fm_table` object preserve the original format of `values`, which means, if `values`
#' was specified as an atomic vector, the two functions also returns atomic vectors.
#' 
#' Once the hash table or the hash set is created, it is not allowed to modify.
#' 
#' @examples
#' h = hash_fm_table(letters, 1:26)
#' hash_keys(h)
#' hash_values(h)
#' h$a
#' try(h$a <- 2L)
#' 
#' h = hash_env_set(letters)
#' hash_exists(h, "a")
hash_fm_table = function(keys, values) {
	
	h = new("hash_fm_table")

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
	
	h@values = values
	
	h@table = fmatch.hash("", keys)
	h@is_atomic = is.atomic(values)
	
	h
}

#' @export
#' @rdname hash_fm
hash_fm_set = function(keys) {
	h = new("hash_fm_set")
	if(is.null(keys)) {
		stop("`keys` cannot be NULL.")
	}
	if(any(duplicated(keys))) {
		stop("Keys should not be duplicated.")
	}
	h@table = fmatch.hash("", keys)
	h
}

#' @export
#' @rdname hash_fm
#' @param h,x,object A `hash_fm_table` object returned by `hash_fm_table()` or a `hash_fm_set` object returned by `hash_fm_set()`.
setMethod("hash_exists", signature = "hash_fm",
	definition = function(h, keys) {
	keys %fin% h@table
})

#' @export
#' @rdname hash_fm
setMethod("hash_delete", signature = "hash_fm",
	definition = function(h, keys) {
	stop("hash_fm is not allowed to modify.")
})

#' @export
#' @rdname hash_fm
setMethod("hash_size", signature = "hash_fm",
	definition = function(h) {
	length(h@table)
})

#' @export
#' @rdname hash_fm
length.hash_fm = function(x) {
	hash_size(x)
}

#' @export
#' @rdname hash_fm
setMethod("hash_keys", signature = "hash_fm",
	definition = function(h) {
	keys = h@table
	attributes(keys) = NULL
	keys
})

#' @export
#' @rdname hash_fm
setMethod("hash_values", signature = "hash_fm_table",
	definition = function(h, keys = NULL) {

	if(is.null(keys)) {
		h@values
	} else {
		if(is.integer(keys)) {
			n = length(h@values)
			if(any(keys < 1)) {
				stop("Keys are out of bounds.")
			}
			if(any(keys > n)) {
				stop("Keys are out of bounds.")
			}
			h@values[keys]
		} else {
			ind = fmatch(keys, h@table)
			if(any(is.na(ind))) {
				stop("Some keys do not exist.")
			}
			h@values[ind]
		}
	}
})

#' @export
#' @rdname hash_fm
setMethod("hash_values", signature = "hash_fm_set",
	definition = function(h, keys = NULL) {
	hash_exists(h, keys)
})

#' @export
#' @rdname hash_fm
setMethod("hash_insert", signature = "hash_fm_table",
	definition = function(h, keys, values) {

	if(is.integer(keys)) {
		update_vector_elements(h@values, keys, values);
	} else {
		ind = fmatch(keys, h@table)
		if(any(is.na(ind))) {
			stop("hash_fm_table is not allowed to insert new keys.")
		}
		update_vector_elements(h@values, ind, values);
	}
	invisible(h)
})

#' @export
#' @rdname hash_fm
setMethod("hash_insert", signature = "hash_fm_set",
	definition = function(h, keys, values) {
	stop("hash_fm_set is not allowed to modify.")
})

#' @export
#' @rdname hash_fm
setMethod("hash_copy", signature = "hash_fm",
	definition = function(h) {
	h
})

#' @export
#' @rdname hash_fm
#' @param i,name,value Keys and values.
"[[.hash_fm" = function(x, i) {
	if(length(i) != 1) {
		stop("length of the index should be 1.")
	}
	hash_values(x, i)[[1]]
}

#' @export
#' @rdname hash_fm
"[[<-.hash_fm" = function(x, i, value) {
	if(length(i) != 1) {
		stop("length of the index should be 1.")
	}
	if(is.list(x@values)) {
		hash_insert(x, i, list(value))
	} else {
		hash_insert(x, i, value)
	}
	x
}

#' @export
#' @rdname hash_fm
"[.hash_fm" = function(x, i) {
	hash_values(x, i)
}

#' @export
#' @rdname hash_fm
"[<-.hash_fm" = function(x, i, value) {
	hash_insert(x, i, value)
	x
}

#' @export
#' @rdname hash_fm
"$.hash_fm" = function(x, name) {
	x[[name]]
}

#' @export
#' @rdname hash_fm
"$<-.hash_fm" = function(x, i, value) {
	x[[i]] <- value
	x
}

#' @export
#' @rdname hash_fm
as.hash_fm = function(x) {
	UseMethod("as.hash_fm")
}

#' @export
#' @rdname hash_fm
as.hash_fm.default = function(x) {
	nm = names(x)
	if(is.null(nm)) {
		if(is.atomic(x) && is.character(x)) {
			h = hash_fm_set(x)
			return(h)
		} 
		stop("`x` should have names.")
	}

	hash_fm_table(nm, unname(x))
}

#' @export
#' @rdname hash_fm
#' @param mode Please ignore.
as.vector.hash_fm_set = function(x, mode = "any") {
	x@table
}

#' @export
#' @rdname hash_fm
as.vector.hash_fm_table = function(x, mode = "any") {
	structure(x@value, names = x@table)
}

#' @export
#' @rdname hash_fm
setMethod("show", signature = "hash_fm_table",
	definition = function(object) {

	n = hash_size(object)
	
	cl_name = class(object@values)[1]
	cat("A hash table [hash_fm_table] with ", n, " key-value (", cl_name, ") pair", ifelse(n > 1, "s", ""), "\n", sep = "")

	are_values_atomic = is.atomic(object@values)

	print_key_value_pairs(object, are_values_atomic)
})

#' @export
#' @rdname hash_fm
setMethod("show", signature = "hash_fm_set",
	definition = function(object) {

	n = hash_size(object)
	keys = hash_keys(object)

	cat("A hash set [hash_fm_set] with ", n, " key", ifelse(n > 1, "s", ""), " (character)\n", sep = "")
})


