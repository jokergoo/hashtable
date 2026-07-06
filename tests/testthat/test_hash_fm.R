context("Test `hash_fm`")

test_that("Test constructor", {
	expect_error(hash_fm_table("a", 1:2))
	expect_error(hash_fm_table(c("a","a"), 1:2))
	expect_error(hash_fm_table(letters))
	expect_error(hash_fm_table())
	expect_error(hash_fm_set())
})


h = hash_fm_table(letters, as.list(1:26))
test_that("Test utility functions, hash_fm_table, list", {
	expect_equal(hash_size(h), 26)
	expect_equal(hash_exists(h, "a"), TRUE)
	expect_equal(hash_exists(h, letters), rep(TRUE, 26))
	expect_equal(hash_values(h, "a"), list(1))
	expect_equal(hash_values(h, letters), as.list(1:26))
	expect_equal(hash_values(h, c("a", "a")), list(1, 1))
	
	hash_insert(h, "a", list(10))
	expect_equal(hash_values(h, "a"), list(10))
	expect_error(hash_insert(h, "foo", 1))
	expect_error(hash_insert(h, "a", "text"))
})

h = hash_fm_set(letters)
test_that("Test utility functions, hash_fm_set", {
	expect_equal(hash_size(h), 26)
	expect_equal(hash_exists(h, "a"), TRUE)
	expect_equal(hash_exists(h, letters), rep(TRUE, 26))
	expect_true(hash_values(h, "a"))
	expect_false(hash_values(h, "foo"))

	expect_error(hash_insert(h, "a", 1))
})


test_that("Test as functions", {
	x = 1:26
	names(x) = letters
	h = as.hash_fm(x)
	expect_true(inherits(h, "hash_fm_table"))
	expect_equal(hash_size(h), 26)
	expect_equal(hash_exists(h, "a"), TRUE)
	expect_equal(hash_exists(h, letters), rep(TRUE, 26))
	expect_equal(hash_values(h, "a"), 1)

	x = letters
	h = as.hash_fm(x)
	expect_true(inherits(h, "hash_fm_set"))
	expect_equal(hash_size(h), 26)
	expect_equal(hash_exists(h, "a"), TRUE)
	expect_equal(hash_exists(h, letters), rep(TRUE, 26))
	expect_true(hash_values(h, "a"))

	x = as.list(1:26)
	names(x) = letters
	h = as.hash_fm(x)
	expect_true(inherits(h, "hash_fm_table"))
	expect_equal(hash_size(h), 26)
	expect_equal(hash_exists(h, "a"), TRUE)
	expect_equal(hash_exists(h, letters), rep(TRUE, 26))
	expect_equal(hash_values(h, "a"), list(1))

	x = as.list(1:26)
	expect_error(as.hash_fm(x))
})

test_that("Test subset functions", {
	h = hash_fm_table(letters, 1:26)

	expect_equal(h["a"], 1)
	expect_equal(h[c("a", "b")], 1:2)
	expect_equal(h[["a"]], 1)
	expect_error(h[[c("a", "b")]])
	expect_equal(h$a, 1)

	h$a = 100L
	expect_equal(h["a"], 100L)
	h[c("a", "b")] = c(10L, 20L)
	expect_equal(h[c("a", "b")], c(10L, 20L))

	h = hash_fm_set(letters)
	expect_true(h["a"])
	expect_true(h[["a"]])
	expect_true(h$a)
	expect_error(h["a"] <- 1)

	h = hash_fm_table(letters, as.list(1:26))
	expect_equal(h["a"], list(1))
	expect_equal(h[c("a", "b")], list(1, 2))
	expect_equal(h[["a"]], 1)
	expect_error(h[[c("a", "b")]])
	expect_equal(h$a, 1)

	expect_error(h["a"] <- 1)
	h["a"] = list(10)
	expect_equal(h$a, 10)
	h$a = 100
	expect_equal(h$a, 100)
})
