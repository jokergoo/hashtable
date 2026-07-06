# Hash set implemented by std::unordered_set

Hash set implemented by std::unordered_set

## Usage

``` r
hash_set(keys)

# S4 method for class 'hash_unordered_set'
hash_exists(h, keys)

# S4 method for class 'hash_unordered_set'
hash_insert(h, keys)

# S4 method for class 'hash_unordered_set'
hash_delete(h, keys)

# S4 method for class 'hash_unordered_set'
hash_size(h)

# S4 method for class 'hash_unordered_set'
hash_copy(h)

# S4 method for class 'hash_unordered_set'
hash_keys(h)

# S4 method for class 'hash_unordered_set'
hash_values(h, keys = NULL)

# S3 method for class 'hash_unordered_set'
x[[i]]

# S3 method for class 'hash_unordered_set'
x[i]

# S3 method for class 'hash_unordered_set'
x$name

# S3 method for class 'hash_unordered_set'
x[[i]] <- value

# S3 method for class 'hash_unordered_set'
x[i] <- value

# S3 method for class 'hash_unordered_set'
x$name <- value

# S3 method for class 'hash_unordered_set'
length(x)

# S4 method for class 'hash_unordered_set'
show(object)

as.hash_set(x)

# Default S3 method
as.hash_set(x)

# S3 method for class 'hash_unordered_set'
as.vector(x, mode = "any")
```

## Arguments

- keys:

  Normally a character vector, but `hash_set()` also allows to use an
  integer vector as keys.

- h, x, object:

  A `hash_unordered_set` object returned by `hash_set()`.

- i, name, value:

  Keys and values.

- mode:

  Please ignore.

## Examples

``` r
h = hash_set(letters)
hash_exists(h, c("a", "b", "foo"))
#> [1]  TRUE  TRUE FALSE
hash_insert(h, "foo")
hash_delete(h, "foo")
h$a
#> [1] TRUE
h$foo
#> [1] FALSE

as.hash_set(letters)
#> A hash set [hash_unordered_set] with 26 keys (character)
```
