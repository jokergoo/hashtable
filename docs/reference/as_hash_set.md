# Convert to a hash set

Convert to a hash set

## Usage

``` r
as.hash_set(x)

# S3 method for class 'integer'
as.hash_set(x)

# S3 method for class 'character'
as.hash_set(x)
```

## Arguments

- x:

  An integer vector or a character vector.

## Value

A hash set.

## Examples

``` r
as.hash_set(1:10L)
#> A hash set with 10 keys (integer)
as.hash_set(letters)
#> A hash set with 26 keys (character)
```
