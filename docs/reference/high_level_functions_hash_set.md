# High-level functions for hash sets

High-level functions for hash sets

## Usage

``` r
hash_set_keys(h)

# S3 method for class 'hash_set'
x[[i]]

# S3 method for class 'hash_set'
x[i]

# S3 method for class 'hash_set'
x$name

# S3 method for class 'hash_set'
x[[i]] <- value

# S3 method for class 'hash_set'
x[i] <- value

# S3 method for class 'hash_set'
x$name <- value

# S3 method for class 'hash_set'
length(x)

# S3 method for class 'hash_set'
print(x, ...)
```

## Arguments

- h, x:

  A `hash_set` object.

- i, name:

  A single or a vector of keys.

- value:

  Values.

- ...:

  Other arguments.

## Value

- `hash_set_keys()` returns a vector of all keys.

- `[[` or `$` returns a single logical value.

- `[` returns a vector of logical values.

## Details

For the assignment, `value` should be logical. `TRUE` means to insert
the corresponding keys to the hash set, and `FALSE` means to delete the
corresponding keys.

## Examples

``` r
h = hash_set(letters)
h$a
#> [1] TRUE
h[c("a", "b")]
#> [1] TRUE TRUE
h$a = FALSE
hash_set_keys(h)
#>  [1] "v" "u" "z" "t" "s" "r" "q" "p" "n" "m" "o" "l" "x" "k" "j" "h" "y" "g" "f"
#> [20] "d" "e" "c" "i" "b" "w"
h$aaaa = TRUE
hash_set_keys(h)
#>  [1] "v"    "u"    "z"    "t"    "s"    "r"    "q"    "p"    "n"    "m"   
#> [11] "o"    "l"    "x"    "k"    "j"    "h"    "y"    "g"    "f"    "d"   
#> [21] "aaaa" "e"    "c"    "i"    "b"    "w"   
```
