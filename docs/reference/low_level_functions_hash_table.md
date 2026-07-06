# Low-level functions for hash tables

Low-level functions for hash tables

## Usage

``` r
hash_table_get_values(h, keys)

hash_table_exists(h, keys)

hash_table_set_values(h, keys, values)

hash_table_delete_pairs(h, keys)

hash_table_size(h)

hash_table_get_all_keys(h)

hash_table_get_all_values(h)

hash_table_clear(h)

hash_table_copy(h)
```

## Arguments

- h:

  A `hash_table` object.

- keys:

  A character vector of keys.

- values:

  The corresponding values.

## Value

- `hash_table_get_values()` returns a vector of values.

- `hash_table_exists()` returns a logical vector.

- `hash_table_set_values()`/`hash_table_delete_pairs()`/`hash_table_clear()`
  directly modifies the input object `h`.

- `hash_table_size()` returns a single integer.

- `hash_table_get_all_keys()` returns a vector of all keys.

- `hash_table_get_all_values()` returns a vector of all values.

- `hash_table_copy()` returns a new hash table.

## Examples

``` r
h = hash_table(c("a", "b"), 1:2L)
hash_table_get_values(h, "a")
#> [1] 1
hash_table_exists(h, c("a", "c"))
#> [1]  TRUE FALSE
hash_table_set_values(h, "a", 100L)
hash_table_get_values(h, "a")
#> [1] 100
hash_table_delete_pairs(h, "a")
h
#> A hash table with 1 key-value (integer) pair
#>   b => 2
hash_table_clear(h)
h
#> A hash table with 0 key-value (integer) pair
```
