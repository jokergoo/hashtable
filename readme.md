# Hash tables and hash sets

This package implements hash table and hash set using `std::unordered_map` and `std::unordered_set` from Cpp.

## Install

```r
library(devtools)
install_github("jokergoo/hashtable")
```

## Usage

```
> keys = c("a", "b")
> values = 1:2
> h = hash_table(keys, values)
> h
A hash table with 2 key-value (integer) pairs
  b => 2
  a => 1
```

```
> h = hash_set(letters)
> h
A hash set with 26 keys (character)
```

## License

MIT @ Zuguang Gu