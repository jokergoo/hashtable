context("Test `hash_table`")

test_that("Test errors", {
	expect_error(hash_table("a", 1:2))
	expect_error(hash_table(c("a", "b"), 1))
	expect_error(hash_table())
})


test_that("Test integer values", {
	h = hash_table(c("b", "a"), 2:1L)

	expect_equal(h[["a"]], 1L)
	expect_equal(h$a, 1L)
	expect_equal(h[c("a", "b")], 1:2L)
	expect_equal(h[c("b", "a")], 2:1L)
	expect_equal(length(h), 2)

	expect_error(h$a <- 3)
	expect_error(h[["a"]] <- 3)
	expect_error(h$c <- 3)
	expect_error(h[["c"]] <- 3)

	h$a = 3L
	h[["a"]] = 4L
	h$c = 5L

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), c(4L, 2L, 5L)))

	h = hash_table(c("b", "a"), 2:1L)
	expect_equal(hash_values(h, "a"), 1L)
	expect_equal(hash_values(h, "b"), 2L)
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", 2L)
	hash_insert(h, "c", 4L)
	hash_insert(h, c("a", "d"), c(3L, 5L))
	expect_equal(h$d, 5L)

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), 2:1L)
	expect_true(setequal(hash_values(h), 1:2L))	
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = 1L
	expect_false(hash_exists(h, "c"))
	h2$a = 4L
	expect_false(h$a == 4L)
})


test_that("Test numeric values", {
	h = hash_table(c("b", "a"), c(0.2, 0.1))

	expect_equal(h[["a"]], 0.1)
	expect_equal(h$a, 0.1)
	expect_equal(h[c("a", "b")], c(0.1, 0.2))
	expect_equal(h[c("b", "a")], c(0.2, 0.1))
	expect_equal(length(h), 2)

	expect_error(h$a <- 3L)
	expect_error(h[["a"]] <- 3L)
	expect_error(h$c <- 3L)
	expect_error(h[["c"]] <- 3L)

	h$a = 0.3
	h[["a"]] = 0.4
	h$c = 0.5

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), c(0.4, 0.2, 0.5)))

	h = hash_table(c("b", "a"), c(0.2, 0.1))
	expect_equal(hash_values(h, "a"), 0.1)
	expect_equal(hash_values(h, "b"), 0.2)
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1L))
	expect_error(hash_insert(h, "c", 1L))

	hash_insert(h, "a", 0.2)
	hash_insert(h, "c", 0.4)
	hash_insert(h, c("a", "d"), c(0.3, 0.5))
	expect_equal(h$d, 0.5)

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), c(0.2, 0.1))
	expect_true(setequal(hash_values(h), c(0.1, 0.2)))	
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = 0.1
	expect_false(hash_exists(h, "c"))
	h2$a = 0.4
	expect_false(h$a == 0.4)

})



test_that("Test logical values", {
	h = hash_table(c("b", "a"), c(TRUE, FALSE))

	expect_equal(h[["a"]], FALSE)
	expect_equal(h$a, FALSE)
	expect_equal(h[c("a", "b")], c(FALSE, TRUE))
	expect_equal(h[c("b", "a")], c(TRUE, FALSE))
	expect_equal(length(h), 2)

	expect_error(h$a <- 1)
	expect_error(h[["a"]] <- 1)
	expect_error(h$c <- 1)
	expect_error(h[["c"]] <- 1)

	h$a = TRUE
	h[["a"]] = FALSE
	h$c = TRUE

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), c(TRUE, FALSE, TRUE)))

	h = hash_table(c("b", "a"), c(TRUE, FALSE))
	expect_equal(hash_values(h, "a"), FALSE)
	expect_equal(hash_values(h, "b"), TRUE)
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", TRUE)
	hash_insert(h, "c", TRUE)
	hash_insert(h, c("a", "d"), c(TRUE, FALSE))
	expect_equal(h$d, FALSE)

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), c(TRUE, FALSE))
	expect_true(setequal(hash_values(h), c(TRUE, FALSE)))	
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = TRUE
	expect_false(hash_exists(h, "c"))
	h2$a = TRUE
	expect_false(h$a == TRUE)
})



test_that("Test character values", {
	h = hash_table(c("b", "a"), c("two", "one"))

	expect_equal(h[["a"]], "one")
	expect_equal(h$a, "one")
	expect_equal(h[c("a", "b")], c("one", "two"))
	expect_equal(h[c("b", "a")], c("two", "one"))
	expect_equal(length(h), 2)

	expect_error(h$a <- 3)
	expect_error(h[["a"]] <- 3)
	expect_error(h$c <- 3)
	expect_error(h[["c"]] <- 3)

	h$a = "oneone"
	h[["a"]] = "oneone"
	h$c = "three"

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), c("two", "oneone", "three")))

	h = hash_table(c("b", "a"), c("two", "one"))
	expect_equal(hash_values(h, "a"), "one")
	expect_equal(hash_values(h, "b"), "two")
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", "oneone")
	hash_insert(h, "c", "three")
	hash_insert(h, c("a", "d"), c("oneone", "four"))
	expect_equal(h$d, "four")

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), c("two", "one"))
	expect_true(setequal(hash_values(h), c("one", "two")))	
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = "three"
	expect_false(hash_exists(h, "c"))
	h2$a = "www"
	expect_false(h$a == "www")

})


test_that("Test Date values", {
	h = hash_table(c("b", "a"), as.Date(c("2025-02-01", "2025-01-01")))

	expect_equal(h[["a"]], as.Date("2025-01-01"))
	expect_equal(h$a, as.Date("2025-01-01"))
	expect_equal(h[c("a", "b")], as.Date(c("2025-01-01", "2025-02-01")))
	expect_equal(h[c("b", "a")], as.Date(c("2025-02-01", "2025-01-01")))
	expect_equal(length(h), 2)

	expect_error(h$a <- 3)
	expect_error(h[["a"]] <- 3)
	expect_error(h$c <- 3)
	expect_error(h[["c"]] <- 3)

	h$a = as.Date("2025-03-01")
	h[["a"]] = as.Date("2025-04-01")
	h$c = as.Date("2025-05-01")

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), as.Date(c("2025-02-01", "2025-04-01", "2025-05-01"))))

	h = hash_table(c("b", "a"), as.Date(c("2025-02-01", "2025-01-01")))
	expect_equal(hash_values(h, "a"), as.Date("2025-01-01"))
	expect_equal(hash_values(h, "b"), as.Date("2025-02-01"))
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", as.Date("2025-03-01"))
	hash_insert(h, "c", as.Date("2025-04-01"))
	hash_insert(h, c("a", "d"), as.Date(c("2025-05-01", "2025-06-01")))
	expect_equal(h$d, as.Date("2025-06-01"))

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), as.Date(c("2025-02-01", "2025-01-01")))
	expect_true(setequal(hash_values(h), as.Date(c("2025-02-01", "2025-01-01"))))
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = as.Date("2025-03-01")
	expect_false(hash_exists(h, "c"))
	h2$a = as.Date("2025-04-01")
	expect_false(h$a == as.Date("2025-04-01"))
})


test_that("Test character values", {
	h = hash_table(c("b", "a"), c("two", "one"))

	expect_equal(h[["a"]], "one")
	expect_equal(h$a, "one")
	expect_equal(h[c("a", "b")], c("one", "two"))
	expect_equal(h[c("b", "a")], c("two", "one"))
	expect_equal(length(h), 2)

	expect_error(h$a <- 3)
	expect_error(h[["a"]] <- 3)
	expect_error(h$c <- 3)
	expect_error(h[["c"]] <- 3)

	h$a = "oneone"
	h[["a"]] = "oneone"
	h$c = "three"

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), c("two", "oneone", "three")))

	h = hash_table(c("b", "a"), c("two", "one"))
	expect_equal(hash_values(h, "a"), "one")
	expect_equal(hash_values(h, "b"), "two")
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", "oneone")
	hash_insert(h, "c", "three")
	hash_insert(h, c("a", "d"), c("oneone", "four"))
	expect_equal(h$d, "four")

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), c("two", "one"))
	expect_true(setequal(hash_values(h), c("one", "two")))	
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = "three"
	expect_false(hash_exists(h, "c"))
	h2$a = "www"
	expect_false(h$a == "www")
})


test_that("Test POSIXct values", {
	h = hash_table(c("b", "a"), as.POSIXct(c("2025-02-01 00:00:01", "2025-01-01 00:00:01")))

	expect_equal(h[["a"]], as.POSIXct("2025-01-01 00:00:01"))
	expect_equal(h$a, as.POSIXct("2025-01-01 00:00:01"))
	expect_equal(h[c("a", "b")], as.POSIXct(c("2025-01-01 00:00:01", "2025-02-01 00:00:01")))
	expect_equal(h[c("b", "a")], as.POSIXct(c("2025-02-01 00:00:01", "2025-01-01 00:00:01")))
	expect_equal(length(h), 2)

	expect_error(h$a <- 3)
	expect_error(h[["a"]] <- 3)
	expect_error(h$c <- 3)
	expect_error(h[["c"]] <- 3)

	h$a = as.POSIXct("2025-03-01 00:00:01")
	h[["a"]] = as.POSIXct("2025-04-01 00:00:01")
	h$c = as.POSIXct("2025-05-01 00:00:01")

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))
	expect_true(setequal(hash_values(h), as.POSIXct(c("2025-02-01 00:00:01", "2025-04-01 00:00:01", "2025-05-01 00:00:01"))))

	h = hash_table(c("b", "a"), as.POSIXct(c("2025-02-01 00:00:01", "2025-01-01 00:00:01")))
	expect_equal(hash_values(h, "a"), as.POSIXct("2025-01-01 00:00:01"))
	expect_equal(hash_values(h, "b"), as.POSIXct("2025-02-01 00:00:01"))
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	expect_error(hash_insert(h, "a", 1))
	expect_error(hash_insert(h, "c", 1))

	hash_insert(h, "a", as.POSIXct("2025-03-01 00:00:01"))
	hash_insert(h, "c", as.POSIXct("2025-04-01 00:00:01"))
	hash_insert(h, c("a", "d"), as.POSIXct(c("2025-05-01 00:00:01", "2025-06-01 00:00:01")))
	expect_equal(h$d, as.POSIXct("2025-06-01 00:00:01"))

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), as.POSIXct(c("2025-02-01 00:00:01", "2025-01-01 00:00:01")))
	expect_true(setequal(hash_values(h), as.POSIXct(c("2025-02-01 00:00:01", "2025-01-01 00:00:01"))))
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = as.POSIXct("2025-03-01 00:00:01")
	expect_false(hash_exists(h, "c"))
	h2$a = as.POSIXct("2025-04-01 00:00:01")
	expect_false(h$a == as.POSIXct("2025-04-01 00:00:01"))

})



test_that("Test list values", {
	h = hash_table(c("b", "a"), list(1:10, letters))

	expect_equal(h[["a"]], letters)
	expect_equal(h$a, letters)
	expect_equal(h[c("a", "b")], list(letters, 1:10))
	expect_equal(h[c("b", "a")], list(1:10, letters))
	expect_equal(length(h), 2)

	h$a = 3
	h[["a"]] = 4:5
	h$c = "foo"

	expect_true(setequal(hash_keys(h), c("b", "a", "c")))

	h = hash_table(c("b", "a"), list(1:10, letters))
	expect_equal(hash_values(h, "a"), list(letters))
	expect_equal(hash_values(h, "b"), list(1:10))
	expect_true(hash_exists(h, "a"))
	expect_true(all(hash_exists(h, c("a", "b"))))
	expect_false(hash_exists(h, "c"))
	expect_equal(hash_exists(h, c("c", "a")), c(FALSE, TRUE))

	hash_insert(h, "a", list(1:10))
	hash_insert(h, "c", list(letters[1:10]))
	hash_insert(h, c("a", "d"), list(1:4, c(0.1, 0.2)))
	expect_equal(h$d, c(0.1, 0.2))

	hash_delete(h, "a")
	expect_false(hash_exists(h, "a"))
	hash_delete(h, c("b", "c"))
	expect_false(any(hash_exists(h, c("b", "c"))))

	h = hash_table(c("b", "a"), list(1:10, letters))
	expect_true(setequal(hash_keys(h), c("a", "b")))

	h2 = hash_copy(h)
	expect_equal(length(h), length(h2))
	expect_true(setequal(hash_keys(h), hash_keys(h2)))
	h2$c = "foo"
	expect_false(hash_exists(h, "c"))
	h2$a = 1:10
	expect_false(identical(h$a, 1:10))
})


test_that("Test as.hash_table function", {
	h = as.hash_table(c("a" = 1L, "b" = 2L))
	expect_equal(h@value_class, "integer")
	h = as.hash_table(c("a" = 1, "b" = 2))
	expect_equal(h@value_class, "numeric")
	h = as.hash_table(c("a" = TRUE, "b" = FALSE))
	expect_equal(h@value_class, "logical")
	h = as.hash_table(c("a" = "a", "b" = "b"))
	expect_equal(h@value_class, "character")
	h = as.hash_table(c("a" = as.Date("2025-01-01"), "b" = as.Date("2025-02-01")))
	expect_equal(h@value_class, "Date")
	h = as.hash_table(c("a" = as.POSIXct("2025-01-01 00:00:01"), "b" = as.POSIXct("2025-02-01 00:00:01")))
	expect_equal(h@value_class, "POSIXct")
	h = as.hash_table(list("a" = 1:10, "b" = letters))
	expect_equal(h@value_class, "list")
})

test_that("Test as.vector/as.list", {
	h = hash_table(c("a", "b"), 1:2L)
	keys = hash_keys(h)
	expect_equal(as.vector(h), structure(names = c("a", "b"), 1:2L)[keys])
	expect_equal(as.list(h), structure(names = c("a", "b"), as.list(1:2L))[keys])

	h = hash_table(c("a", "b"), as.list(1:2L))
	keys = hash_keys(h)
	expect_equal(as.vector(h), structure(names = c("a", "b"), as.list(1:2L))[keys])
	expect_equal(as.list(h), structure(names = c("a", "b"), as.list(1:2L))[keys])

})

test_that("Test delete keys that do not exist", {
	h = hash_table("a", 1)
	expect_success(hash_delete(h, "b"))
})
