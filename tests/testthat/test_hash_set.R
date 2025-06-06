context("Test `hash_set`")

test_that("Test errors", {
	expect_error(hash_set(c(TRUE, FALSE)))
	expect_error(hash_set(c(0.1, 0.2)))
})


test_that("Test integer values", {
	h = hash_set(letters)

	expect_equal(h["a"], TRUE)
	expect_equal(h$a, TRUE)
	expect_equal(h[["a"]], TRUE)
	expect_equal(h[c("a", "b")], c(TRUE, TRUE))
	expect_equal(h[c("a", "aa")], c(TRUE, FALSE))

	expect_equal(length(h), 26)

	expect_error(h$a <- 1)

	h$a = FALSE
	expect_equal(length(h), 25)
	expect_equal(h$a, FALSE)

	h[c("b", "c", "d")] = FALSE
	expect_equal(length(h), 21)
	expect_equal(h[c("b", "c", "d")], c(FALSE, FALSE, FALSE))

	expect_error(h$a <- 1)
	h$a = TRUE
	expect_equal(h$a, TRUE)


	h = hash_set(letters)
	expect_equal(hash_set_keys(h), letters)
	expect_true(hash_set_exists(h, "a"))

	hash_set_insert(h, "aa")
	expect_true(hash_set_exists(h, "aa"))

	hash_set_delete(h, "aa")
	expect_false(hash_set_exists(h, "aa"))

	h = hash_set(letters)
	h2 = hash_set_copy(h)
	hash_set_clear(h)
	expect_equal(length(h), 0)
	expect_equal(length(h2), 26)
})

test_that("Test delete keys that do not exist", {
	h = hash_set("a")
	h$b = FALSE
})

