

#' Hash set
#' @param keys An integer vector or a character vector where all elements are unique.
#'
#' @import Rcpp
#' @export
#' @return A `hash_set` object.
#' @examples
#' hash_set(letters)
#' hash_set(1:10)
hash_set = function(keys) {
	cl = class(keys)[1]
	h = switch(cl, 
		"integer"   = hash_set_create_int(keys),
		"character" = hash_set_create_string(keys),
		stop("Data type of `keys` ('", cl, "') is not supported.")
	)

	class(h) = c("hash_set", paste0("hash_set_", cl))
	h
}

#' Low-level functions for hash sets
#' @param h A `hash_set` object.
#' @param keys A single or a vector of keys.
#' @export
#' @rdname low_level_functions_hash_set
#' @return
#' - `hash_set_exists()` returns a logical vector.
#' - `hash_set_insert()`/`hash_set_delete()`/`hash_set_clear()` directly modifies the input object `h`.
#' - `hash_set_size()` returns a single integer.
#' - `hash_set_get_all_keys()` returns a vector of all keys.
#' - `hash_set_copy()` returns a new `hash_table` object. 
#' @examples
#' h = hash_set(letters)
#' hash_set_exists(h, "a")
#' hash_set_exists(h, "aa")
#' hash_set_insert(h, "aa")
#' hash_set_exists(h, "aa")
#' hash_set_delete(h, "aa")
hash_set_exists = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_set_integer"   = hash_set_exists_int(h, keys),
		"hash_set_character" = hash_set_exists_string(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_set
hash_set_insert = function(h, keys) {
	cl = class(h)[2]

	clv = class(keys)[1]
	clh = gsub("hash_set_", "", cl)
	if(clv != clh) {
		stop("Data type of `values` (", clv, ") is not compatible with the hash set (", clh, ").")
	}

	switch(cl, 
		"hash_set_integer"   = hash_set_insert_int(h, keys),
		"hash_set_character" = hash_set_insert_string(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_set
hash_set_delete = function(h, keys) {
	cl = class(h)[2]
	switch(cl, 
		"hash_set_integer"   = hash_set_delete_int(h, keys),
		"hash_set_character" = hash_set_delete_string(h, keys)
	)
}

#' @export
#' @rdname low_level_functions_hash_set
hash_set_size = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_set_integer"   = hash_set_size_int(h),
		"hash_set_character" = hash_set_size_string(h)
	)
}

#' @export
#' @rdname low_level_functions_hash_set
hash_set_get_all_keys = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_set_integer"   = hash_set_get_all_keys_int(h),
		"hash_set_character" = hash_set_get_all_keys_string(h)
	)
}


#' @export
#' @rdname low_level_functions_hash_set
hash_set_clear = function(h) {
	cl = class(h)[2]
	switch(cl, 
		"hash_set_integer"   = hash_set_clear_int(h),
		"hash_set_character" = hash_set_clear_string(h)
	)
}

#' @export
#' @rdname low_level_functions_hash_set
hash_set_copy = function(h) {
	cl = class(h)[2]
	h2 = switch(cl, 
		"hash_set_integer"   = hash_set_copy_int(h),
		"hash_set_character" = hash_set_copy_string(h)
	)
	class(h2) = class(h)
	h2
}

#' High-level functions for hash sets
#' @param h,x A `hash_set` object.
#' @param i,name A single or a vector of keys.
#' @export
#' @rdname high_level_functions_hash_set
#' @return
#' - `hash_set_keys()` returns a vector of all keys. 
#' - `[[` or `$` returns a single logical value. 
#' - `[` returns a vector of logical values.
#' @examples
#' h = hash_set(letters)
#' h$a
#' h[c("a", "b")]
#' h$a = FALSE
#' hash_set_keys(h)
#' h$aaaa = TRUE
#' hash_set_keys(h)
hash_set_keys = function(h) {
	hash_set_get_all_keys(h)
} 


#' @export
#' @rdname high_level_functions_hash_set
"[[.hash_set" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of index in `[[` should only be one.")
	}
	hash_set_exists(x, i)
}

#' @export
#' @rdname high_level_functions_hash_set
"[.hash_set" = function(x, i) {
	hash_set_exists(x, i)
}

#' @export
#' @rdname high_level_functions_hash_set
"$.hash_set" = function(x, name) {
	hash_set_exists(x, name)
}

#' @param value Values.
#' @export
#' @rdname high_level_functions_hash_set
#' @details
#' For the assignment, `value` should be logical. `TRUE` means to insert the corresponding keys to the hash set, 
#' and `FALSE` means to delete the corresponding keys.
"[[<-.hash_set" = function(x, i, value) {
	if(is.null(value)) value = FALSE
	if(length(i) != 1) {
		stop("Length of index in `[[` should only be one.")
	}

	if(is.logical(value)) {
		if(value) {
			hash_set_insert(x, i)
		} else {
			hash_set_delete(x, i)
		}
	} else {
		stop("`value` should be logical.")
	}
	x
}

#' @export
#' @rdname high_level_functions_hash_set
"[<-.hash_set" = function(x, i, value) {
	if(is.null(value)) value = FALSE
	if(is.logical(value)) {
		if(length(value) == 1) {
			if(value) {
				hash_set_insert(x, i)
			} else {
				hash_set_delete(x, i)
			}
		} else {
			if(any(value)) {
				hash_set_insert(x, i[value])
			}
			if(any(!value)) {
				hash_set_delete(x, i[!value])
			}
		}
	} else {
		stop("`value` should be logical.")
	}
	x
}

#' @export
#' @rdname high_level_functions_hash_set
"$<-.hash_set" = function(x, name, value) {
	if(is.null(value)) value = FALSE
	"[[<-.hash_set"(x, name, value)
	x
}


#' @export
#' @rdname high_level_functions_hash_set
length.hash_set = function(x) {
	hash_set_size(x)
}


#' @param ... Other arguments.
#' @export
#' @rdname high_level_functions_hash_set
print.hash_set = function(x, ...) {
	cl = class(x)

	n = hash_set_size(x)
	keys = hash_set_keys(x)

	cl_name = gsub("^hash_set_", "", cl[2])
	cat("A hash set with ", n, " key", ifelse(n > 1, "s", ""), " (", cl_name, ")\n", sep = "")
}



#' @rdname hash_set
#' @param cl One of "integer" and "character".
#' @export
#' @examples
#' hash_set_empty("integer")
#' hash_set_empty("character")
hash_set_empty = function(cl) {
	switch(cl, 
		"integer" = hash_set(integer(0)),
		"character" = hash_set(character(0)),
		"Wrong class"
	)
}


#' Convert to a hash set
#' 
#' @param x An integer vector or a character vector.
#' 
#' @export
#' @return A hash set.
#' @rdname as_hash_set
#' @examples
#' as.hash_set(1:10L)
#' as.hash_set(letters)
as.hash_set = function(x) {
	UseMethod("as.hash_set")
}

#' @export
#' @rdname as_hash_set
as.hash_set.integer = function(x) {
	hash_set(x)
}

#' @export
#' @rdname as_hash_set
as.hash_set.character = function(x) {
	hash_set(x)
}
