
setClass("hash_unordered_set",
	slots = c(ptr = "ANY",
		      value_class = "character"))


#' Hash set implemented by std::unordered_set
#' 
#' @export
#' @param keys Normally a character vector, but `hash_set()` also allows to use an integer vector as keys.
#' @rdname hash_set
#' @examples
#' h = hash_set(letters)
#' hash_exists(h, c("a", "b", "foo"))
#' hash_insert(h, "foo")
#' hash_delete(h, "foo")
#' h$a
#' h$foo
#' 
#' as.hash_set(letters)
hash_set = function(keys) {
	if(is.null(keys)) {
		stop("`keys` cannot be NULL.")
	}
	if(any(duplicated(keys))) {
		stop("Keys should not be duplicated.")
	}
	h = new("hash_unordered_set")
	cl = class(keys)[1]
	h@ptr = switch(cl, 
		"integer"   = hash_set_create_int(keys),
		"character" = hash_set_create_string(keys),
		stop("Data type of `keys` ('", cl, "') is not supported.")
	)
	h@value_class = cl
	h
}

#' @export
#' @rdname hash_set
#' @param h,x,object A `hash_unordered_set` object returned by `hash_set()`.
setMethod("hash_exists", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_set_exists_int(h@ptr, keys),
		"character" = hash_set_exists_string(h@ptr, keys),
		stop("Wrong data type.")
	)
})

#' @export
#' @rdname hash_set
setMethod("hash_insert", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cl = h@value_class

	clv = class(keys)[1]
	if(clv != cl) {
		stop("Data type of `keys` (", clv, ") is not compatible with the hash set (", cl, ").")
	}

	switch(cl, 
		"integer"   = hash_set_insert_int(h@ptr, keys),
		"character" = hash_set_insert_string(h@ptr, keys)
	)

	invisible(h)
})

#' @export
#' @rdname hash_set
setMethod("hash_delete", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_set_delete_int(h@ptr, keys),
		"character" = hash_set_delete_string(h@ptr, keys),
		stop("Wrong data type.")
	)
	invisible(h)
})

#' @export
#' @rdname hash_set
setMethod("hash_size", signature = "hash_unordered_set",
	definition = function(h) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_set_size_int(h@ptr),
		"character" = hash_set_size_string(h@ptr),
		stop("Wrong data type.")
	)
})

#' @export
#' @rdname hash_set
setMethod("hash_copy", signature = "hash_unordered_set",
	definition = function(h) {
	cl = h@value_class
	h2 = new("hash_unordered_set")
	h2@value_class = cl

	h2@ptr = switch(cl, 
		"integer"   = hash_set_copy_int(h@ptr),
		"character" = hash_set_copy_string(h@ptr),
		stop("Wrong data type.")
	)

	h2
})

#' @export
#' @rdname hash_set
setMethod("hash_keys", signature = "hash_unordered_set",
	definition = function(h) {
	cl = h@value_class
	switch(cl, 
		"integer"   = hash_set_get_all_keys_int(h@ptr),
		"character" = hash_set_get_all_keys_string(h@ptr),
		stop("Wrong data type.")
	)
})

#' @export
#' @rdname hash_set
setMethod("hash_values", signature = "hash_unordered_set",
	definition = function(h, keys = NULL) {
	stop("hash_unordered_set has no values.")
})


#' @export
#' @rdname hash_set
"[[.hash_unordered_set" = function(x, i) {
	if(length(i) != 1) {
		stop("Length of index should only be one.")
	}
	hash_exists(x, i)
}

#' @rdname hash_set
#' @export
#' @param i,name,value Keys and values.
"[.hash_unordered_set" = function(x, i) {
	hash_exists(x, i)
}

#' @rdname hash_set
#' @export
"$.hash_unordered_set" = function(x, name) {
	x[[name]]
}

#' @rdname hash_set
#' @export
"[[<-.hash_unordered_set" = function(x, i, value) {
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

#' @rdname hash_set
#' @export
"[<-.hash_unordered_set" = function(x, i, value) {
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

#' @rdname hash_set
#' @export
"$<-.hash_unordered_set" = function(x, name, value) {
	x[[name]] = value
	x
}


#' @rdname hash_set
#' @export
length.hash_unordered_set = function(x) {
	hash_size(x)
}


#' @rdname hash_set
#' @export
setMethod("show", signature = "hash_unordered_set",
	definition = function(object) {
	n = hash_size(object)
	cl_name = object@value_class
	cat("A hash set [hash_unordered_set] with ", n, " key", ifelse(n > 1, "s", ""), " (", cl_name, ")\n", sep = "")
})

#' @rdname hash_set
#' @export
as.hash_set = function(x) {
	UseMethod("as.hash_set")
}

#' @rdname hash_set
#' @export
as.hash_set.default = function(x) {
	hash_set(x)
}

#' @rdname hash_set
#' @export
#' @param mode Please ignore.
as.vector.hash_unordered_set = function(x, mode = "any") {
	hash_keys(x)
}
