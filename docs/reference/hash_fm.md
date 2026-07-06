# Hash table and hash set implemented by fastmatch

Hash table and hash set implemented by fastmatch

## Usage

``` r
hash_fm_table(keys, values)

hash_fm_set(keys)

# S4 method for class 'hash_fm'
hash_exists(h, keys)

# S4 method for class 'hash_fm'
hash_delete(h, keys)

# S4 method for class 'hash_fm'
hash_size(h)

# S3 method for class 'hash_fm'
length(x)

# S4 method for class 'hash_fm'
hash_keys(h)

# S4 method for class 'hash_fm_table'
hash_values(h, keys = NULL)

# S4 method for class 'hash_fm_set'
hash_values(h, keys = NULL)

# S4 method for class 'hash_fm_table'
hash_insert(h, keys, values)

# S4 method for class 'hash_fm_set'
hash_insert(h, keys, values)

# S4 method for class 'hash_fm'
hash_copy(h)

# S3 method for class 'hash_fm'
x[[i]]

# S3 method for class 'hash_fm'
x[[i]] <- value

# S3 method for class 'hash_fm'
x[i]

# S3 method for class 'hash_fm'
x[i] <- value

# S3 method for class 'hash_fm'
x$name

# S3 method for class 'hash_fm'
x$i <- value

as.hash_fm(x)

# Default S3 method
as.hash_fm(x)

# S3 method for class 'hash_fm_set'
as.vector(x, mode = "any")

# S3 method for class 'hash_fm_table'
as.vector(x, mode = "any")

# S4 method for class 'hash_fm_table'
show(object)

# S4 method for class 'hash_fm_set'
show(object)
```

## Arguments

- keys:

  A character vector.

- values:

  An atomic vector or a list.

- h, x, object:

  A `hash_fm_table` object returned by `hash_fm_table()` or a
  `hash_fm_set` object returned by `hash_fm_set()`.

- i, name, value:

  Keys and values.

- mode:

  Please ignore.

## Details

Once the hash table or the hash set is created, it is not allowed to
modify.

## Examples

``` r
h = hash_fm_table(letters, 1:26)
hash_keys(h)
#>  [1] "a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s"
#> [20] "t" "u" "v" "w" "x" "y" "z"
hash_values(h)
#>  [1]  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
#> [26] 26
h$a
#> [1] 1
try(h$a <- 2L)

h = hash_env_set(letters)
hash_exists(h, "a")
#> [1] TRUE
```
