
setClass("hash_unordered_set",
	slots = c(ptr = "ANY"))


#' Hash set implemented by std::unordered_set
#' 
#' @export
#' @param keys A character vector. Keys should have no duplicates.
#' @rdname hash_set
#' @details
#' Hash set has no values associated.
#' 
#' `$`, `[[` and `[` return logical vectors. `$<-`, `[[<-` and `[<-` insert or delete keys.
#' 
#' @return
#' `hash_set()`, `hash_insert()`, `hash_delete()`, `hash_copy()` returns a `hash_unordered_set` object.
#' `hash_exists()` returns a logical vector. `hash_size()` returns an integer. `hash_keys()` returns 
#' a character vector. `hash_values()` throws an error.
#' 
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
	if(!is.character(keys)) {
		stop("`keys` should be a character vector.")
	}

	h = new("hash_unordered_set")
	if(missing(keys)) {
		h@ptr = cpp_hash_set_create(character(0))
	} else {
		h@ptr = cpp_hash_set_create(keys)
	}
	
	h
}

#' @export
#' @rdname hash_set
#' @param h,x,object A `hash_unordered_set` object returned by `hash_set()`.
setMethod("hash_exists", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cpp_hash_set_exists(h@ptr, keys)
})

#' @export
#' @rdname hash_set
setMethod("hash_insert", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cpp_hash_set_insert(h@ptr, keys)
})

#' @export
#' @rdname hash_set
setMethod("hash_delete", signature = "hash_unordered_set",
	definition = function(h, keys) {
	cpp_hash_set_delete(h@ptr, keys)
})

#' @export
#' @rdname hash_set
setMethod("hash_size", signature = "hash_unordered_set",
	definition = function(h) {
	cpp_hash_set_size(h@ptr)
})

#' @export
#' @rdname hash_set
setMethod("hash_copy", signature = "hash_unordered_set",
	definition = function(h) {
	h2 = new("hash_unordered_set")
	h2@ptr = cpp_hash_set_copy(h@ptr)
	h2
})

#' @export
#' @rdname hash_set
setMethod("hash_keys", signature = "hash_unordered_set",
	definition = function(h) {
	cpp_hash_set_all_keys(h@ptr)
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
	hash_exists(x, name)
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
	cat("A hash set [hash_unordered_set] with ", n, " key", ifelse(n > 1, "s", ""), "\n", sep = "")
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
