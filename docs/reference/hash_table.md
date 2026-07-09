# Hash table implemented by std::unordered_map

Hash table implemented by std::unordered_map

## Usage

``` r
hash_table(keys, values)

# S4 method for class 'hash_unordered_map'
hash_values(h, keys = NULL)

# S4 method for class 'hash_unordered_map'
hash_exists(h, keys)

# S4 method for class 'hash_unordered_map'
hash_insert(h, keys, values)

# S4 method for class 'hash_unordered_map'
hash_delete(h, keys)

# S4 method for class 'hash_unordered_map'
hash_size(h)

# S3 method for class 'hash_unordered_map'
length(x)

# S4 method for class 'hash_unordered_map'
hash_keys(h)

# S4 method for class 'hash_unordered_map'
hash_copy(h)

# S3 method for class 'hash_unordered_map'
x[[i]]

# S3 method for class 'hash_unordered_map'
x[i]

# S3 method for class 'hash_unordered_map'
x$name

# S3 method for class 'hash_unordered_map'
x[[i]] <- value

# S3 method for class 'hash_unordered_map'
x[i] <- value

# S3 method for class 'hash_unordered_map'
x$name <- value

# S4 method for class 'hash_unordered_map'
show(object)

as.hash_table(x)

# Default S3 method
as.hash_table(x)

# S3 method for class 'hash_unordered_map'
as.vector(x, mode = "any")

# S3 method for class 'hash_unordered_map'
as.list(x, ...)
```

## Arguments

- keys:

  A character vector. Keys should have no duplicates.

- values:

  An atomic vector or a list.

- h, x, object:

  A `hash_unordered_map` object returned by `hash_table()`.

- i, name, value:

  Keys and values.

- mode, ...:

  Please ignore.

## Value

`hash_table()`, [`hash_insert()`](generic.md),
[`hash_delete()`](generic.md), [`hash_copy()`](generic.md) returns a
`hash_unordered_map` object. [`hash_exists()`](generic.md) returns a
logical vector. [`hash_size()`](generic.md) returns an integer.
[`hash_keys()`](generic.md) returns a character vector.
[`hash_values()`](generic.md) returns a vector of a list which has the
same format as in the constructor function.

## Details

[`hash_values()`](generic.md) and `[` methods preserve the original
format of `values`, which means, if `values` was specified as an atomic
vector, the two functions also returns atomic vectors.

## Examples

``` r
hash_table(c("a", "b"), 1:2L)
#> A hash table [hash_unordered_map] with 2 key-value (integer) pairs
#>   b => 2
#>   a => 1
hash_table(c("a", "b"), c(TRUE, FALSE))
#> A hash table [hash_unordered_map] with 2 key-value (logical) pairs
#>   b => FALSE
#>   a => TRUE
hash_table(c("a", "b"), c(0.1, 0.2))
#> A hash table [hash_unordered_map] with 2 key-value (numeric) pairs
#>   b => 0.2
#>   a => 0.1
hash_table(c("a", "b"), c("one", "two"))
#> A hash table [hash_unordered_map] with 2 key-value (character) pairs
#>   b => two
#>   a => one
hash_table(c("a", "b"), as.Date(c("2025-01-01", "2025-02-01")))
#> A hash table [hash_unordered_map] with 2 key-value (Date) pairs
#>   b => 2025-02-01
#>   a => 2025-01-01
hash_table(c("a", "b"), as.POSIXct(c("2025-01-01 00:00:01", "2025-02-01 00:00:01")))
#> A hash table [hash_unordered_map] with 2 key-value (POSIXct) pairs
#>   b => 2025-02-01 00:00:01
#>   a => 2025-01-01 00:00:01
hash_table(c("a", "b"), list(1:10, letters))
#> A hash table [hash_unordered_map] with 2 key-value (list) pairs
#>   b => character [1:26] a b c d e f g h i j k l m n o p q r s t u v w x y z
#>   a => integer [1:10] 1 2 3 4 5 6 7 8 9 10

h = hash_table(letters, 1:26)
hash_keys(h)
#>  [1] "y" "x" "w" "v" "t" "s" "q" "p" "o" "m" "n" "k" "j" "z" "h" "g" "u" "f" "e"
#> [20] "r" "l" "d" "i" "c" "b" "a"
hash_values(h)
#>  [1] 25 24 23 22 20 19 17 16 15 13 14 11 10 26  8  7 21  6  5 18 12  4  9  3  2
#> [26]  1
hash_exists(h, c("a", "b", "foo"))
#> [1]  TRUE  TRUE FALSE
hash_delete(h, letters[1:20]); h
#> A hash table [hash_unordered_map] with 6 key-value (integer) pairs
#>   y => 25
#>   x => 24
#>   w => 23
#>   v => 22
#>   z => 26
#>   u => 21
hash_insert(h, "foo", 100L) 

h = hash_table(letters, 1:26)
h$a
#> [1] 1
h[["a"]]
#> [1] 1
h[c("a", "b")]
#> [1] 1 2

as.vector(h)
#>  y  x  w  v  t  s  q  p  o  m  n  k  j  z  h  g  u  f  e  r  l  d  i  c  b  a 
#> 25 24 23 22 20 19 17 16 15 13 14 11 10 26  8  7 21  6  5 18 12  4  9  3  2  1 
as.list(h)
#> $y
#> [1] 25
#> 
#> $x
#> [1] 24
#> 
#> $w
#> [1] 23
#> 
#> $v
#> [1] 22
#> 
#> $t
#> [1] 20
#> 
#> $s
#> [1] 19
#> 
#> $q
#> [1] 17
#> 
#> $p
#> [1] 16
#> 
#> $o
#> [1] 15
#> 
#> $m
#> [1] 13
#> 
#> $n
#> [1] 14
#> 
#> $k
#> [1] 11
#> 
#> $j
#> [1] 10
#> 
#> $z
#> [1] 26
#> 
#> $h
#> [1] 8
#> 
#> $g
#> [1] 7
#> 
#> $u
#> [1] 21
#> 
#> $f
#> [1] 6
#> 
#> $e
#> [1] 5
#> 
#> $r
#> [1] 18
#> 
#> $l
#> [1] 12
#> 
#> $d
#> [1] 4
#> 
#> $i
#> [1] 9
#> 
#> $c
#> [1] 3
#> 
#> $b
#> [1] 2
#> 
#> $a
#> [1] 1
#> 
```
