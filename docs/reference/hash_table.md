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
#>  [1] "y" "w" "v" "x" "u" "t" "s" "r" "p" "q" "o" "n" "m" "z" "l" "k" "i" "h" "g"
#> [20] "f" "e" "j" "d" "c" "b" "a"
hash_values(h)
#>  [1] 25 23 22 24 21 20 19 18 16 17 15 14 13 26 12 11  9  8  7  6  5 10  4  3  2
#> [26]  1
hash_exists(h, c("a", "b", "foo"))
#> [1]  TRUE  TRUE FALSE
hash_delete(h, letters[1:20]); h
#> A hash table [hash_unordered_map] with 6 key-value (integer) pairs
#>   y => 25
#>   w => 23
#>   v => 22
#>   x => 24
#>   u => 21
#>   z => 26
hash_insert(h, "foo", 100L) 

h = hash_table(letters, 1:26)
h$a
#> [1] 1
h[["a"]]
#> [1] 1
h[c("a", "b")]
#> [1] 1 2

as.vector(h)
#>  y  w  v  x  u  t  s  r  p  q  o  n  m  z  l  k  i  h  g  f  e  j  d  c  b  a 
#> 25 23 22 24 21 20 19 18 16 17 15 14 13 26 12 11  9  8  7  6  5 10  4  3  2  1 
as.list(h)
#> $y
#> [1] 25
#> 
#> $w
#> [1] 23
#> 
#> $v
#> [1] 22
#> 
#> $x
#> [1] 24
#> 
#> $u
#> [1] 21
#> 
#> $t
#> [1] 20
#> 
#> $s
#> [1] 19
#> 
#> $r
#> [1] 18
#> 
#> $p
#> [1] 16
#> 
#> $q
#> [1] 17
#> 
#> $o
#> [1] 15
#> 
#> $n
#> [1] 14
#> 
#> $m
#> [1] 13
#> 
#> $z
#> [1] 26
#> 
#> $l
#> [1] 12
#> 
#> $k
#> [1] 11
#> 
#> $i
#> [1] 9
#> 
#> $h
#> [1] 8
#> 
#> $g
#> [1] 7
#> 
#> $f
#> [1] 6
#> 
#> $e
#> [1] 5
#> 
#> $j
#> [1] 10
#> 
#> $d
#> [1] 4
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
