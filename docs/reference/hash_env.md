# Hash table and hash set implemented by environment

Hash table and hash set implemented by environment

## Usage

``` r
hash_env_table(keys, values)

hash_env_set(keys)

# S4 method for class 'hash_env'
hash_exists(h, keys)

# S4 method for class 'hash_env'
hash_delete(h, keys)

# S4 method for class 'hash_env_table'
hash_insert(h, keys, values)

# S4 method for class 'hash_env_set'
hash_insert(h, keys)

# S4 method for class 'hash_env'
hash_size(h)

# S3 method for class 'hash_env'
length(x)

# S4 method for class 'hash_env'
hash_keys(h)

# S4 method for class 'hash_env_table'
hash_values(h, keys = NULL)

# S4 method for class 'hash_env_set'
hash_values(h, keys = NULL)

# S4 method for class 'hash_env'
hash_copy(h)

# S3 method for class 'hash_env_table'
x[[i]]

# S3 method for class 'hash_env_set'
x[[i]]

# S3 method for class 'hash_env_table'
x[[i]] <- value

# S3 method for class 'hash_env_table'
x[i]

# S3 method for class 'hash_env_set'
x[i]

# S3 method for class 'hash_env_table'
x[i] <- value

# S3 method for class 'hash_env'
x$name

# S3 method for class 'hash_env_table'
x$i <- value

# S3 method for class 'hash_env_set'
x[[i]] <- value

# S3 method for class 'hash_env_set'
x[i] <- value

# S3 method for class 'hash_env_set'
x$name <- value

as.hash_env(x)

# Default S3 method
as.hash_env(x)

# S3 method for class 'hash_env_set'
as.vector(x, mode = "any")

# S3 method for class 'hash_env_table'
as.vector(x, mode = "any")

# S3 method for class 'hash_env_table'
as.list(x, ...)

# S4 method for class 'hash_env_table'
show(object)

# S4 method for class 'hash_env_set'
show(object)
```

## Arguments

- keys:

  A character vector. Keys should have no duplicates.

- values:

  An atomic vector or a list.

- h, x, object:

  A `hash_env_table` returned by `hash_env_table()` or a `hash_env_set`
  object returned by `hash_env_set()`.

- i, name, value:

  Keys and values.

- mode, ...:

  Please ignore.

## Value

`hash_env_table()` returns a `hash_env_table` object. `hash_env_set()`
returns a `hash_env_set` object. `hash_env_delete()`,
`hash_env_insert()`, `hash_env_copy()` return a `hash_env_table` object
or a `hash_env_set` object. [`hash_exists()`](generic.md) returns a
logical vector. [`hash_size()`](generic.md) returns an integer.
[`hash_keys()`](generic.md) returns a character vector.
[`hash_values()`](generic.md) on the `hash_env_table` object returns a
vector of a list which has the same format as in the constructor
function. [`hash_values()`](generic.md) on the `hash_env_set` object
throws an error.

## Details

[`hash_values()`](generic.md) and `[` methods on the `hash_env_table`
object preserve the original format of `values`, which means, if
`values` was specified as an atomic vector, the two functions also
returns atomic vectors.

## Examples

``` r
h = hash_env_table(letters, 1:26)
hash_keys(h)
#>  [1] "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z" "a"
#> [20] "b" "c" "d" "e" "f" "g" "h"
hash_values(h)
#>  [1]  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26  1  2  3  4  5  6  7
#> [26]  8
h$a
#> [1] 1

h = hash_env_set(letters)
hash_exists(h, "a")
#> [1] TRUE
```
