# Low-level functions for hash sets

Low-level functions for hash sets

## Usage

``` r
hash_set_exists(h, keys)

hash_set_insert(h, keys)

hash_set_delete(h, keys)

hash_set_size(h)

hash_set_get_all_keys(h)

hash_set_clear(h)

hash_set_copy(h)
```

## Arguments

- h:

  A `hash_set` object.

- keys:

  A single or a vector of keys.

## Value

- `hash_set_exists()` returns a logical vector.

- `hash_set_insert()`/`hash_set_delete()`/`hash_set_clear()` directly
  modifies the input object `h`.

- `hash_set_size()` returns a single integer.

- `hash_set_get_all_keys()` returns a vector of all keys.

- `hash_set_copy()` returns a new `hash_table` object.

## Examples

``` r
h = hash_set(letters)
hash_set_exists(h, "a")
#> [1] TRUE
hash_set_exists(h, "aa")
#> [1] FALSE
hash_set_insert(h, "aa")
hash_set_exists(h, "aa")
#> [1] TRUE
hash_set_delete(h, "aa")
```
