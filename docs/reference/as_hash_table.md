# Convert to a hash table

Convert to a hash table

## Usage

``` r
as.hash_table(x)

# S3 method for class 'integer'
as.hash_table(x)

# S3 method for class 'numeric'
as.hash_table(x)

# S3 method for class 'character'
as.hash_table(x)

# S3 method for class 'logical'
as.hash_table(x)

# S3 method for class 'Date'
as.hash_table(x)

# S3 method for class 'POSIXct'
as.hash_table(x)

# S3 method for class 'list'
as.hash_table(x)
```

## Arguments

- x:

  The input vector-like object with names.

## Value

A hash table.

## Examples

``` r
as.hash_table(c("a" = 1L, "b" = 2L))
#> A hash table with 2 key-value (integer) pairs
#>   b => 2
#>   a => 1
as.hash_table(c("a" = 1, "b" = 2))
#> A hash table with 2 key-value (numeric) pairs
#>   b => 2
#>   a => 1
as.hash_table(c("a" = TRUE, "b" = FALSE))
#> A hash table with 2 key-value (logical) pairs
#>   b => FALSE
#>   a => TRUE
as.hash_table(c("a" = "one", "b" = "two"))
#> A hash table with 2 key-value (character) pairs
#>   b => two
#>   a => one
as.hash_table(c("a" = as.Date("2025-01-01"), 
                "b" = as.Date("2025-02-01")))
#> A hash table with 2 key-value (Date) pairs
#>   b => 2025-02-01
#>   a => 2025-01-01
as.hash_table(c("a" = as.POSIXct("2025-01-01 00:00:01"), 
                "b" = as.POSIXct("2025-02-01 00:00:01")))
#> A hash table with 2 key-value (POSIXct) pairs
#>   b => 2025-02-01 00:00:01
#>   a => 2025-01-01 00:00:01
as.hash_table(list("a" = 1:10, "b" = letters))
#> A hash table with 2 key-value (R object) pairs
#>   b => character [1:26] a b c d e f g h i j k l m n o p q r s t u v w x y z
#>   a => integer [1:10] 1 2 3 4 5 6 7 8 9 10
```
