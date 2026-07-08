setGeneric('hash_exists', function(h, keys) standardGeneric('hash_exists'))
setGeneric('hash_keys', function(h) standardGeneric('hash_keys'))
setGeneric('hash_values', function(h, keys = NULL) standardGeneric('hash_values'))
setGeneric('hash_size', function(h) standardGeneric('hash_size'))
setGeneric('hash_insert', function(h, keys, ...) standardGeneric('hash_insert'))
setGeneric('hash_delete', function(h, keys) standardGeneric('hash_delete'))
setGeneric('hash_copy', function(h) standardGeneric('hash_copy'))

#' Generic functions
#' 
#' @name generic
#' @rdname generic
#' @aliases hash_copy
#' @aliases hash_delete
#' @aliases hash_exists
#' @aliases hash_insert
#' @aliases hash_keys
#' @aliases hash_size
#' @aliases hash_values
#' 
#' @details
#' There are the following generic functions:
#' - `hash_exists(h, keys)`: tests whether keys exist.
#' - `hash_keys(h)`: returns a vector of keys.
#' - `hash_values(h, keys = NULL)`: returns a vector of values.
#' - `hash_size(h)`: returns the size of the hash table or hash set.
#' - `hash_insert(h, keys, ...)`: inserts new keys or modify values for existing keys.
#' - `hash_delete(h, keys)`: deletes keys.
#' - `hash_copy(h)`: makes a copy of the hash table or hash set.
#' 
#' They can be used on the hash object created by [`hash_table()`], [`hash_set()`], [`hash_fm_table()`], [`hash_fm_set()`], [`hash_env_table()`], [`hash_env_set()`].
NULL
