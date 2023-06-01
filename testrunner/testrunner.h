#pragma once


#include <emblib_stm32/core.h>
#include <cstdio>
#include <cstring>


namespace emb {

void run_tests();


class test_runner {
private:
    static inline int _asserts_in_test = 0;
	static inline int _asserts = 0;
	static inline int _asserts_failed_in_test = 0;
	static inline int _asserts_failed = 0;
	static inline int _tests = 0;
	static inline int _tests_failed = 0;
	static inline int _tests_passed = 0;
    static inline int _tests_skipped = 0;
public:
	static inline void (*print)(const char* str) = [](const char* str) {
		fatal_error("emb::test_runner print function not defined");
	};

	static inline void (*print_nextline)() = []() {
		fatal_error("emb::test_runner print_nextline function not defined");
	};

	template <typename T, typename U>
	static void assert_equal(const T& t, const U& u, const char* hint) {
        ++_asserts_in_test;
		++_asserts;
		if (!(t == u)) {
			++_asserts_failed_in_test;
			++_asserts_failed;
			print(hint);
			print_nextline();
		}
	}

	static void assert_true(bool b, const char* hint) {
		assert_equal(b, true, hint);
	}


	template <class TestFunc>
	static void run_test(TestFunc test_func, const char* test_name) {
		++_tests;
        _asserts_in_test = 0;
		_asserts_failed_in_test = 0;
		test_func();
        if (_asserts_in_test == 0) {
            ++_tests_skipped;
            print("[  SKIP  ] ");
            print(test_name);
            print_nextline();
        } else if (_asserts_failed_in_test == 0) {
			++_tests_passed;
			print("[ PASSED ] ");
			print(test_name);
			print_nextline();
		} else {
			++_tests_failed;
			print("[ FAILED ] ");
			print(test_name);
			print_nextline();
		}
	}

	static void print_result() {
		print_nextline();
		char str[64] = {0};
		snprintf(str, 63, "Asserts: %d failed, %d passed", _asserts_failed, _asserts - _asserts_failed);
		print(str);
		print_nextline();

		memset(str, 0, 64);
		snprintf(str, 63, "Tests:   %d failed, %d passed, %d skipped", _tests_failed, _tests_passed, _tests_skipped);
		print(str);
		print_nextline();

		if (_tests_failed == 0) {
			print("OK");
			print_nextline();
		} else {
			print("FAIL");
			print_nextline();
		}
	}

	static bool passed() {
		if (_tests_failed == 0) {
			return true;
		}
		return false;
	}
};

} // namespace emb


#define EMB_RUN_TEST(func) emb::test_runner::run_test(func, #func)


#ifdef UNIT_TESTS_ENABLED
#define EMB_ASSERT_EQUAL(x, y) \
{ \
	const char* hint = "[  WARN  ] Assertion failed: " #x " != " #y ", file: " __FILE__ ", line: " EMB_STRINGIZE(__LINE__); \
	emb::test_runner::assert_equal(x, y, hint); \
}
#else
#define EMB_ASSERT_EQUAL(x, y) ((void)0)
#endif


#ifdef UNIT_TESTS_ENABLED
#define EMB_ASSERT_TRUE(x) \
{ \
	const char* hint = "[  WARN  ] Assertion failed: " #x " is false, file: " __FILE__ ", line: " EMB_STRINGIZE(__LINE__); \
	emb::test_runner::assert_true(x, hint); \
}
#else
#define EMB_ASSERT_TRUE(x) ((void)0)
#endif

