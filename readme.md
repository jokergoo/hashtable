# Hash Table and Hash Set

The **hashtable** packages provides three implementations of hash tables and hash maps:

1. using `std::unordered_map` and `std::unordered_set` from C++, in functions `hash_table()` and `hash_set()`,
2. using environment in R, in functions `hash_env_table()` and `hash_env_set()`,
3. using the **fastmatch** package, in functions `hash_fm_table()` and `hash_fm_set()`.

They share the same user interface.

## Install

```r
library(devtools)
install_github("jokergoo/hashtable")
```

## Usage

### Hash table

```
library(hashtable)
h1 = hash_table(letters, 1:26)
h2 = hash_env_table(letters, 1:26)
h3 = hash_fm_table(letters, 1:26)
h1
## A hash table [hash_unordered_map] with 26 key-value (integer) pairs
##   v => 22
##   u => 21
##   z => 26
##   ......
##   b => 2
##   w => 23
##   a => 1
```

### Hash set

```
h1 = hash_set(letters)
h2 = hash_env_set(letters)
h3 = hash_fm_set(letters)
h1
## A hash set [hash_unordered_set] with 26 keys (character)
```

## Benchmark

See https://jokergoo.github.io/hashtable/articles/benchmark.html.


## License

MIT @ Zuguang Gu