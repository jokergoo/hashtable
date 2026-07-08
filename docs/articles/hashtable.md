# Hash Table and Hash Set

The **hashtable** packages provides three implementations of hash tables
and hash maps:

1.  using `std::unordered_map` and `std::unordered_set` from C++, in
    functions [`hash_table()`](../reference/hash_table.md) and
    [`hash_set()`](../reference/hash_set.md),
2.  using the **fastmatch** package, in functions
    [`hash_fm_table()`](../reference/hash_fm.md) and
    [`hash_fm_set()`](../reference/hash_fm.md),
3.  using environment, in functions
    [`hash_env_table()`](../reference/hash_env.md) and
    [`hash_env_set()`](../reference/hash_env.md).

They share the same user interface.

## Hash table

Three ways to create hash tables:

``` r

library(hashtable)
h1 = hash_table(letters, 1:26)
h2 = hash_fm_table(letters, 1:26)
h3 = hash_env_table(letters, 1:26)
h1
```

    ## A hash table [hash_unordered_map] with 26 key-value (integer) pairs
    ##   y => 25
    ##   x => 24
    ##   w => 23
    ##   ......
    ##   l => 12
    ##   b => 2
    ##   a => 1

``` r

h2
```

    ## A hash table [hash_fm_table] with 26 key-value (integer) pairs
    ##   a => 1
    ##   b => 2
    ##   c => 3
    ##   ......
    ##   x => 24
    ##   y => 25
    ##   z => 26

``` r

h3
```

    ## A hash table [hash_env_table] with 26 key-value (integer) pairs
    ##   i => 9
    ##   j => 10
    ##   k => 11
    ##   ......
    ##   f => 6
    ##   g => 7
    ##   h => 8

The user interfaces for the two methods are the same. We only
demonstrate using `h1`.

Get all keys:

``` r

hash_keys(h1)
```

    ##  [1] "y" "x" "w" "u" "t" "s" "r" "q" "n" "m" "k" "v" "j" "i" "z" "h" "g" "f" "e"
    ## [20] "d" "p" "o" "c" "l" "b" "a"

Get all values:

``` r

hash_values(h1)
```

    ##  [1] 25 24 23 21 20 19 18 17 14 13 11 22 10  9 26  8  7  6  5  4 16 15  3 12  2
    ## [26]  1

Get a subset of values by specifying keys:

``` r

hash_values(h1, c("a", "b", "c"))
```

    ## [1] 1 2 3

Get a single value using `$`, `[[` or `[`:

``` r

h1$a
```

    ## [1] 1

``` r

h1[["a"]]
```

    ## [1] 1

``` r

h1[c("a", "b")]
```

    ## [1] 1 2

Test whether keys are in the hash table:

``` r

hash_exists(h1, c("a", "b", "foo"))
```

    ## [1]  TRUE  TRUE FALSE

Delete key-value pairs:

``` r

hash_delete(h1, c("a", "b"))
hash_exists(h1, c("a", "b"))
```

    ## [1] FALSE FALSE

Insert new key-value pairs, or modify key-value pairs if they already
exist:

``` r

hash_insert(h1, "c", 100L); h1$c
```

    ## [1] 100

``` r

hash_insert(h1, "c", -1L); h1$c
```

    ## [1] -1

``` r

hash_insert(h1, "foo", 0L); h1$foo
```

    ## [1] 0

Insert or modify key-value pairs using `$<-`, `[[<-` or `[<-`:

``` r

h1$a = 20L; h1$a
```

    ## [1] 20

``` r

h1[["bar"]] = -100L; h1$bar
```

    ## [1] -100

``` r

h1[c("c", "d", "e")] = c(-1L, -2L, -3L); h1[c("c", "d", "e")]
```

    ## [1] -1 -2 -3

In previous examples, values are atomic vectors. It is basically the
same if values are more general list.

``` r

h1 = hash_table(c("a", "b"), list(1L, "text"))
h1
```

    ## A hash table [hash_unordered_map] with 2 key-value (list) pairs
    ##   b => character [1] text
    ##   a => integer [1] 1

``` r

h1$c = 3.14
h1$d = lm(1~1) # an lm object
h1
```

    ## A hash table [hash_unordered_map] with 4 key-value (list) pairs
    ##   d => complex value (lm)
    ##   b => character [1] text
    ##   c => numeric [1] 3.14
    ##   a => integer [1] 1

Convert between hash table and named vector or list:

``` r

h1 = hash_table(c("a", "b"), 1:2)
as.vector(h1)
```

    ## b a 
    ## 2 1

``` r

h1 = hash_table(c("a", "b"), list(1L, "text"))
as.vector(h1)
```

    ## $b
    ## [1] "text"
    ## 
    ## $a
    ## [1] 1

``` r

vec = structure(1:2, names = c("a", "b"))
as.hash_table(vec)
```

    ## A hash table [hash_unordered_map] with 2 key-value (integer) pairs
    ##   b => 2
    ##   a => 1

``` r

lt = structure(list(1L, "text"), names = c("a", "b"))
as.hash_table(lt)
```

    ## A hash table [hash_unordered_map] with 2 key-value (list) pairs
    ##   b => character [1] text
    ##   a => integer [1] 1

## Hash set

Hash sets are hash tables with no value associated. There are also three
ways to create hash sets.

``` r

h1 = hash_set(letters)
h2 = hash_fm_set(letters)
h3 = hash_env_set(letters)
h1
```

    ## A hash set [hash_unordered_set] with 26 keys

Get all keys:

``` r

hash_keys(h1)
```

    ##  [1] "y" "x" "w" "u" "t" "s" "r" "q" "n" "m" "k" "v" "j" "i" "z" "h" "g" "f" "e"
    ## [20] "d" "p" "o" "c" "l" "b" "a"

Hash set has no value associated, so calling `hash_value()` throws an
error.

``` r

hash_values(h1)
```

    ## Error in `hash_values()`:
    ## ! hash_unordered_set has no values.

Test whether keys are in the hash set:

``` r

hash_exists(h1, c("a", "foo"))
```

    ## [1]  TRUE FALSE

Add new keys:

``` r

hash_insert(h1, "foo")
hash_exists(h1, "foo")
```

    ## [1] TRUE

Delete keys:

``` r

hash_delete(h1, "foo")
hash_exists(h1, "foo")
```

    ## [1] FALSE

Hash sets are basically used to test whether keys exist, so we let `$`,
`[[` and `[` to return `TRUE` or `FALSE` to represent whether keys
exist.

``` r

h1$a
```

    ## [1] TRUE

``` r

h1[["a"]]
```

    ## [1] TRUE

``` r

h1$foo
```

    ## [1] FALSE

``` r

h1[c("a", "b", "foo")]
```

    ## [1]  TRUE  TRUE FALSE

If assigning `TRUE`, new keys are added to the hash set (if they do not
exist), and if assigning `FALSE`, corresponding keys are deleted.

``` r

h1$a = FALSE
hash_exists(h1, "a")
```

    ## [1] FALSE

``` r

h1$foo = TRUE
hash_exists(h1, "foo")
```

    ## [1] TRUE

Convert between vectors (where elements are unique) and hash sets:

``` r

as.vector(h1)
```

    ##  [1] "foo" "y"   "x"   "w"   "u"   "t"   "s"   "r"   "q"   "n"   "m"   "k"  
    ## [13] "v"   "j"   "i"   "z"   "h"   "g"   "f"   "e"   "d"   "p"   "o"   "c"  
    ## [25] "l"   "b"

``` r

as.hash_set(letters)
```

    ## A hash set [hash_unordered_set] with 26 keys

## hash_fm_table and hash_fm_set

Although sharing the same user interface, the hash table created by
[`hash_fm_table()`](../reference/hash_fm.md) allows to modify the values
if corresponding keys already exist.

``` r

h = hash_fm_table(letters, 1:26)
h$a = 100L
```

But it does not allow to delete or create key-value pairs.

``` r

h$foo = 1L  # insert new key foo
```

    ## Error in `.local()`:
    ## ! hash_fm_table is not allowed to insert new keys.

``` r

hash_delete(h, "a")
```

    ## Error in `hash_delete()`:
    ## ! hash_fm is not allowed to modify.

The hash set created by [`hash_fm_set()`](../reference/hash_fm.md) does
not allow to delete or create keys.

``` r

h = hash_fm_set(letters)
h$a = FALSE
```

    ## Error in `hash_delete()`:
    ## ! hash_fm is not allowed to modify.

``` r

h$foo = TRUE
```

    ## Error in `.local()`:
    ## ! hash_fm_set is not allowed to modify.

## Session info

``` r

sessionInfo()
```

    ## R version 4.6.0 (2026-04-24)
    ## Platform: aarch64-apple-darwin23
    ## Running under: macOS Tahoe 26.5.1
    ## 
    ## Matrix products: default
    ## BLAS:   /Library/Frameworks/R.framework/Versions/4.6/Resources/lib/libRblas.0.dylib 
    ## LAPACK: /Library/Frameworks/R.framework/Versions/4.6/Resources/lib/libRlapack.dylib;  LAPACK version 3.12.1
    ## 
    ## locale:
    ## [1] en_GB.UTF-8/en_GB.UTF-8/en_GB.UTF-8/C/en_GB.UTF-8/en_GB.UTF-8
    ## 
    ## time zone: Asia/Shanghai
    ## tzcode source: internal
    ## 
    ## attached base packages:
    ## [1] stats     graphics  grDevices utils     datasets  methods   base     
    ## 
    ## other attached packages:
    ## [1] hashtable_1.0.0
    ## 
    ## loaded via a namespace (and not attached):
    ##  [1] vctrs_0.7.3       cli_3.6.6         knitr_1.51        rlang_1.2.0      
    ##  [5] xfun_0.59         otel_0.2.0        textshaping_1.0.5 jsonlite_2.0.0   
    ##  [9] glue_1.8.1        htmltools_0.5.9   ragg_1.5.2        sass_0.4.10      
    ## [13] rmarkdown_2.31    evaluate_1.0.5    jquerylib_0.1.4   fastmap_1.2.0    
    ## [17] yaml_2.3.12       lifecycle_1.0.5   compiler_4.6.0    fs_2.1.0         
    ## [21] htmlwidgets_1.6.4 Rcpp_1.1.1-1.1    fastmatch_1.1-8   systemfonts_1.3.2
    ## [25] digest_0.6.39     R6_2.6.1          pillar_1.11.1     bslib_0.11.0     
    ## [29] tools_4.6.0       pkgdown_2.2.0     cachem_1.1.0      desc_1.4.3
