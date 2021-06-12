#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief A simplest lightweight compatible C test suite for low level C and C++ applications
 * @mainpage Overview
 *
 * ## Usage
 *
 * Just add _asserts.h_ and _asserts.c_ source code into your project
 *
 * ```sh
 * make
 * ```
 *
 * to test autoexplaining example
 *
 * To clean test:
 * ```sh
 * make clean
 * ```
 *
 * ## Projects using _ctest_
 *
 * - [myNanoEmbedded](https://github.com/devfabiosilva/myNanoEmbedded)
 * - [JNI tutorial](https://github.com/devfabiosilva/jni_tutorial)
 *
 * ## Credits
 *
 * @author Fábio Pereira da Silva
 * @date Jun 10 2021
 * @version 0.0.1
 * @copyright License MIT <a href="https://github.com/devfabiosilva/ctest/blob/master/README.md">see here</a>
 *
 * ## Contact
 *
 * mailto:fabioegel@gmail.com
 */

/**
 * @def C_TEST_TRUE
 * _TRUE_ value for CTEST
 */
#define C_TEST_TRUE (int)(1==1)

/**
 * @def C_TEST_FALSE
 * _FALSE_ value for CTEST
 */
#define C_TEST_FALSE (int)(1!=1)

#ifndef CTEST_DOC_SKIP
void _c_test_ignore();
void _c_test_ignore_end();
#endif

/**
 * @def C_TEST_BEGIN_IGNORE
 * Begin ignoring tests
 */
#define C_TEST_BEGIN_IGNORE _c_test_ignore();

/**
 * @def C_TEST_END_IGNORE
 * End ignoring tests
 */
#define C_TEST_END_IGNORE _c_test_ignore_end();

#ifndef CTEST_DOC_SKIP
#define END_TITLE "\e[0m"
#define INITIAL_TITLE "\e[1;3m"
#define ERROR_CODE "\e[31;1m"
#define SUCCESS_CODE "\e[32;1m"
#define WARNING_CODE "\e[33;1m"
#define INFO_CODE "\e[34;1m"

void write_title(const char *, const char *);
void write_title_fmt(const char *, const char *, ...);
#endif

#define TITLE_MSG(msg) write_title(msg, INITIAL_TITLE);
#define ERROR_MSG(msg) write_title(msg, ERROR_CODE);
#define SUCCESS_MSG(msg) write_title(msg, SUCCESS_CODE);
#define WARN_MSG(msg) write_title(msg, WARNING_CODE);
#define INFO_MSG(msg) write_title(msg, INFO_CODE);

#define TITLE_MSG_FMT(...) write_title_fmt(INITIAL_TITLE, __VA_ARGS__);
#define ERROR_MSG_FMT(...) write_title_fmt(ERROR_CODE, __VA_ARGS__);
#define WARN_MSG_FMT(...) write_title_fmt(WARNING_CODE, __VA_ARGS__);
#define INFO_MSG_FMT(...) write_title_fmt(INFO_CODE, __VA_ARGS__);
#define SUCCESS_MSG_FMT(...) write_title_fmt(SUCCESS_CODE, __VA_ARGS__);

#ifndef CTEST_DOC_SKIP
uint64_t *get_va_end_signature();
uint64_t *get_vas_end_signature();

#define VA_END_SIGNATURE get_va_end_signature()
#define VAS_END_SIGNATURE get_vas_end_signature()

typedef void (*header_on_cb)(void *);
typedef void (*cb_fn)(void *);

void *set_varg_callback(uint32_t, cb_fn, ...);

void assert_true(int, ...);
void assert_false(int, ...);
void assert_equal_int(int, int, ...);
void assert_not_equal_int(int, int, ...);
void assert_equal_longint(long long int, long long int, ...);
void assert_not_equal_longint(long long int, long long int, ...);
void assert_equal_double(double, double, double, ...);
void assert_not_equal_double(double, double, double, ...);
void assert_equal_byte(
   void *,
   void *,
   size_t,
   ...
);
void assert_not_equal_byte(
   void *,
   void *,
   size_t,
   ...
);
void assert_equal_string(const char *, const char *, ...);
void assert_not_equal_string(const char *, const char *, ...);
void assert_equal_string_ignore_case(const char *, const char *, ...);
void assert_not_equal_string_ignore_case(const char *, const char *, ...);
void assert_null(void *, ...);
void assert_not_null(void *, ...);
#endif

void on_add_test(header_on_cb);
void rm_on_add_test();
void on_begin_test(header_on_cb);
void rm_begin_test();
void on_test(header_on_cb);
void rm_on_test();
void on_end_test(header_on_cb);
void rm_on_end_test();
void on_abort(header_on_cb);
void rm_on_abort();
void end_tests();

#ifndef CTEST_DOC_SKIP
void *vargs_setter(int, ...);
void *set_varg(uint32_t, const char *, ...);

#define C_TEST_TYPE_VARGS_MSG (uint32_t)(0x10000000)
#define C_TEST_TYPE_VARGS_CALLBACK (uint32_t)(0x20000000|C_TEST_TYPE_VARGS_MSG)

#define C_TEST_VARGS_TITLE (uint32_t)(C_TEST_TYPE_VARGS_MSG|0x002E4992)
#define C_TEST_VARGS_INFO (uint32_t)(C_TEST_TYPE_VARGS_MSG|0x012E4992)
#define C_TEST_VARGS_WARNING (uint32_t)(C_TEST_TYPE_VARGS_MSG|0x022E4992)
#define C_TEST_VARGS_ERROR (uint32_t)(C_TEST_TYPE_VARGS_MSG|0x032E4992)
#define C_TEST_VARGS_SUCCESS (uint32_t)(C_TEST_TYPE_VARGS_MSG|0x042E4992)

#define C_TEST_VARGS_ON_SUCCESS_CALLBACK (uint32_t)(C_TEST_TYPE_VARGS_CALLBACK|0x052E4992)
#define C_TEST_VARGS_ON_ERROR_CALLBACK (uint32_t)(C_TEST_TYPE_VARGS_CALLBACK|0x062E4992)
#endif

/**
 * @def CTEST_SETTER(...)
 * @brief Setter for CTEST. This setter allows callback function such _on_error_ and _on_success_ and add custom _message_, _warn_, _error_, _info_ and _title_
 *
 * # Example:
 *
 *```c
 *  const char *message = "This is a text";
 *  ...
 *  C_ASSERT_TRUE(a > b,
 *     CTEST_SETTER(
 *        CTEST_TITLE("This is a title with message %s", message),
 *        CTEST_INFO("This is an INFO title"),
 *        CTEST_WARN("This is a WARN message"),
 *        CTEST_ON_ERROR("This is a message when error occurs"),
 *        CTEST_ON_SUCCESS("This is a message when SUCCESS occurs"),
 *        CTEST_ON_ERROR_CB(cb_func_on_error, "This function is called on error"),
 *        CTEST_ON_SUCCESS_CB(cb_func_on_success, "This function is callend on success")
 *  ))
 *  ...
 *``` 
 */
#define CTEST_SETTER(...) vargs_setter(-1, __VA_ARGS__, NULL, VA_END_SIGNATURE)

/**
 * @def CTEST_TITLE(...)
 * @brief Set a title message to test. It is only used with _CTEST_SETTER_ macro
 *
 * # Example:
 *
 *```c
 * 
 *  ...
 *  C_ASSERT_EQUAL_BYTE(vec1, vec3, sizeof(vec1),
 *     CTEST_SETTER(
 *       CTEST_TITLE("Checking if vec1 at (%p) has equal bytes with vec2 at (%p)", vec1, vec2,
 *     )
 *  )
 *  ...
 *``` 
 */
#define CTEST_TITLE(...) set_varg(C_TEST_VARGS_TITLE, __VA_ARGS__)

/**
 * @def CTEST_INFO(...)
 * @brief Set a info message to test. It is only used with _CTEST_SETTER_ macro
 *
 * # Example:
 *
 *```c
 *
 *  ...
 *  C_ASSERT_EQUAL_BYTE(vec1, vec3, sizeof(vec1),
 *     CTEST_SETTER(
 *       CTEST_INFO("Checking if vec1 at (%p) has equal bytes with vec2 at (%p)", vec1, vec2,
 *     )
 *  )
 *  ...
 *``` 
 */
#define CTEST_INFO(...) set_varg(C_TEST_VARGS_INFO, __VA_ARGS__)

/**
 * @def CTEST_WARN(...)
 * @brief Set a warn message to test. It is only used with _CTEST_SETTER_ macro
 *
 * # Example:
 *
 *```c
 *
 *  ...
 *  C_ASSERT_EQUAL_BYTE(vec1, vec3, sizeof(vec1),
 *     CTEST_SETTER(
 *       CTEST_WARN("Checking if vec1 at (%p) has equal bytes with vec2 at (%p)", vec1, vec2,
 *     )
 *  )
 *  ...
 *``` 
 */
#define CTEST_WARN(...) set_varg(C_TEST_VARGS_WARNING, __VA_ARGS__)
#define CTEST_ON_ERROR(...) set_varg(C_TEST_VARGS_ERROR, __VA_ARGS__)
#define CTEST_ON_SUCCESS(...) set_varg(C_TEST_VARGS_SUCCESS, __VA_ARGS__)
#define CTEST_ON_SUCCESS_CB(...) set_varg_callback(C_TEST_VARGS_ON_SUCCESS_CALLBACK, __VA_ARGS__, NULL, VAS_END_SIGNATURE)
#define CTEST_ON_ERROR_CB(...) set_varg_callback(C_TEST_VARGS_ON_ERROR_CALLBACK, __VA_ARGS__, NULL, VAS_END_SIGNATURE)

/**
 * @def C_ASSERT_FALSE(result, ...)
 * @brief Checks if result is _FALSE_
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_TRUE
 */
#define C_ASSERT_FALSE(...) assert_false(__VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_TRUE(result, ...)
 * @brief Checks if result is _TRUE_
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_FALSE
 */
#define C_ASSERT_TRUE(...) assert_true(__VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_INT(expected, result, ...)
 * @brief Checks if expected and result value are equal
 * @param expected Expected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_INT
 */
#define C_ASSERT_EQUAL_INT(expected, ...) assert_equal_int(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_INT(unexpected, result, ...)
 * @brief Checks if expected and result value are NOT equal
 * @param unexpected Unexpected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_INT
 */
#define C_ASSERT_NOT_EQUAL_INT(unexpected, ...) assert_not_equal_int(unexpected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_LONG_INT(expected, result, ...)
 * @brief Checks if expected and result value are equal
 * @param expected Expected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_LONG_INT
 */
#define C_ASSERT_EQUAL_LONG_INT(expected, ...) assert_equal_longint(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_LONG_INT(unexpected, result, ...)
 * @brief Checks if expected and result value are NOT equal
 * @param unexpected Unexpected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_LONG_INT
 */
#define C_ASSERT_NOT_EQUAL_LONG_INT(expected, ...) assert_not_equal_longint(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_DOUBLE(expected, result, delta, ...)
 * @brief Checks if expected and result value are equal
 * @param expected Unexpected value
 * @param result Result value
 * @param delta Delta double value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_DOUBLE
 */
#define C_ASSERT_EQUAL_DOUBLE(expected, result, ...) assert_equal_double(expected, result, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_DOUBLE(unexpected, result, delta, ...)
 * @brief Checks if expected and result value are NOT equal
 * @param unexpected Expected value
 * @param result Result value
 * @param delta Delta double value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_DOUBLE
 */
#define C_ASSERT_NOT_EQUAL_DOUBLE(expected, result, ...) assert_not_equal_double(expected, result, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_BYTE(expected, result, size, ...)
 * @brief Checks two memory pointers with same size are equals
 * @param expected Expected value
 * @param result Result value
 * @param size Size of _expected_ and _result_ pointers
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_BYTE
 */
#define C_ASSERT_EQUAL_BYTE(expected, result, ...) assert_equal_byte(expected, result, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_BYTE(unexpected, result, size, ...)
 * @brief Checks two memory pointers with same size are not equals
 * @param unexpected Unexpected value
 * @param result Result value
 * @param size Size of _unexpected_ and _result_ pointers
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_BYTE
 */
#define C_ASSERT_NOT_EQUAL_BYTE(unexpected, result, ...) assert_not_equal_byte(unexpected, result, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NULL(result, ...)
 * @brief Checks if pointer is _NULL_
 * @param result Result pointer
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_NULL
 */
#define C_ASSERT_NULL(...) assert_null(__VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_NULL(result, ...)
 * @brief Checks if pointer is not _NULL_
 * @param result Result pointer
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NULL
 */
#define C_ASSERT_NOT_NULL(...) assert_not_null(__VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_STRING(expected, result, ...)
 * @brief Checks if two strings are equal
 * @param expected Expected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_STRING
 */
#define C_ASSERT_EQUAL_STRING(expected, ...) assert_equal_string(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_STRING(unexpected, result, ...)
 * @brief Checks if two strings are not equal
 * @param unexpected Unexpected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_STRING
 */
#define C_ASSERT_NOT_EQUAL_STRING(expected, ...) assert_not_equal_string(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_EQUAL_STRING_IGNORE_CASE(expected, result, ...)
 * @brief Checks if two strings are equal ignoring case
 * @param Expected Expected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE
 */
#define C_ASSERT_EQUAL_STRING_IGNORE_CASE(expected, ...) assert_equal_string_ignore_case(expected, __VA_ARGS__, VAS_END_SIGNATURE);

/**
 * @def C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE(unexpected, result, ...)
 * @brief Checks if two strings are NOT equal ignoring case
 * @param unexpected Unexpected value
 * @param result Result value
 * @param ... Optional. See CTEST_SETTER() for details
 *
 * @see C_ASSERT_EQUAL_STRING_IGNORE_CASE
 */
#define C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE(expected, ...) assert_not_equal_string_ignore_case(expected, __VA_ARGS__, VAS_END_SIGNATURE);
#ifndef CTEST_DOC_SKIP
#ifdef DEBUG_TEST
// TEMPORARY FOR TESTS

 int load_test_vargs_for_test(void **, ...);
 int load_test_vargs_for_test_v2(void **, ...);
 int free_vargs_for_test(void *);
 char *ctest_setter_has_title(void *);
 char *ctest_setter_has_info(void *);
 char *ctest_setter_has_warn(void *);
 char *ctest_setter_has_onerror(void *);
 char *ctest_setter_has_onsuccess(void *);
 void show_message_text();
#endif
#endif

#ifdef __cplusplus
}
#endif


