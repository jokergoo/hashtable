# Generic functions

Generic functions

## Details

There are the following generic functions:

- `hash_exists(h, keys)`: tests whether keys exist.

- `hash_keys(h)`: returns a vector of keys.

- `hash_values(h, keys = NULL)`: returns a vector of values.

- `hash_size(h)`: returns the size of the hash table or hash set.

- `hash_insert(h, keys, ...)`: inserts new keys or modify values for
  existing keys.

- `hash_delete(h, keys)`: deletes keys.

- `hash_copy(h)`: makes a copy of the hash table or hash set.

They can be used on the hash object created by
[`hash_table()`](hash_table.md), [`hash_set()`](hash_set.md),
[`hash_env_table()`](hash_env.md), [`hash_env_set()`](hash_env.md),
[`hash_fm_table()`](hash_fm.md) and [`hash_fm_set()`](hash_fm.md).
