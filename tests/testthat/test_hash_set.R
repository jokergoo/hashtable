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
	expect_equal(length(h), 22)
	expect_equal(h[c("b", "c", "d")], c(FALSE, FALSE, FALSE))

	h$z = NULL
	expect_equal(length(h), 21)
	expect_equal(h$z, FALSE)

	expect_error(h$a <- 1)
	h$a = TRUE
	expect_equal(h$a, TRUE)


	h = hash_set(letters)
	expect_true(setequal(hash_keys(h), letters))
	expect_true(hash_exists(h, "a"))

	hash_insert(h, "aa")
	expect_true(hash_exists(h, "aa"))

	hash_delete(h, "aa")
	expect_false(hash_exists(h, "aa"))

	h = hash_set(letters)
	h2 = hash_copy(h)
	expect_equal(length(h2), length(h))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))

})

test_that("Test as functions", {
	h = as.hash_set(letters)
	expect_true(setequal(hash_keys(h), letters))
	expect_true(setequal(as.vector(h), letters))
})
