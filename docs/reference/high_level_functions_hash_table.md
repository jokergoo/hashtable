# High-level functions for hash tables

High-level functions for hash tables

## Usage

``` r
hash_table_keys(h)

hash_table_values(h)

# S3 method for class 'hash_table'
x[[i]]

# S3 method for class 'hash_table'
x[i]

# S3 method for class 'hash_table'
x$name

# S3 method for class 'hash_table'
x[[i]] <- value

# S3 method for class 'hash_table'
x[i] <- value

# S3 method for class 'hash_table'
x$name <- value

# S3 method for class 'hash_table'
length(x)

# S3 method for class 'hash_table'
print(x, ...)
```

## Arguments

- h, x:

  A `hash_table` object.

- i, name:

  A single or a vector of character keys.

- value:

  The corresponding values.

- ...:

  Other arguments.

## Value

- `hash_table_keys()` returns a vector of all keys.

- `hash_table_values()` returns a vector of all values.

- `[[` or `$` returns a single value.

- `[` returns a vector of values.

## Details

For `[` and `[<-` methods, multiple keys are allowed.

For the assignment, when the values in the hash table are not R object,
if the assigned value is `NULL`, the corresponding key-value pair is
deleted.

## Examples

``` r
h = hash_table(c("a", "b"), 1:2L)
hash_table_keys(h)
#> [1] "b" "a"
hash_table_values(h)
#> [1] 2 1
h[["a"]]
#> [1] 1
h$a
#> [1] 1
h[c("a", "b")]
#> [1] 1 2
h[["a"]] = 10L
h[["a"]]
#> [1] 10
h$a = 100L
h$a
#> [1] 100
length(h)
#> [1] 2
h = hash_table(c("a", "b"), 1:2L)
h$a = NULL
h
#> A hash table with 1 key-value (integer) pair
#>   b => 2
```
