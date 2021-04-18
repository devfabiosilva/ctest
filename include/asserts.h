#include <stdint.h>

uint64_t *get_va_end_signature();
uint64_t *get_vas_end_signature();
#define VA_END_SIGNATURE get_va_end_signature()
#define VAS_END_SIGNATURE get_vas_end_signature()

typedef void (*free_on_error_fn)(void *);
typedef void (*header_on_cb)(void *);

void assert_true(int, const char *, const char *);
void assert_false(int, const char *, const char *);
void assert_equal_int(int, int, const char *, const char *);
void assert_not_equal_int(int, int, const char *, const char *);
void assert_equal_longint(long long int, long long int, const char *, const char *);
void assert_not_equal_longint(long long int, long long int, const char *, const char *);
void assert_equal_double(double, double, double, const char *, const char *);
void assert_not_equal_double(double, double, double, const char *, const char *);
void assert_equal_byte(
   void *,
   void *,
   size_t,
   free_on_error_fn,
   void *,
   const char *,
   const char *
);
void assert_not_equal_byte(
   void *,
   void *,
   size_t,
   free_on_error_fn,
   void *,
   const char *,
   const char *
);
void assert_equal_string(const char *, const char *, const char *, const char *);
void assert_not_equal_string(const char *, const char *, const char *, const char *);
void assert_equal_string_ignore_case(const char *, const char *, const char *, const char *);
void assert_not_equal_string_ignore_case(const char *, const char *, const char *, const char *);
void assert_null(
   void *,
   free_on_error_fn,
   void *,
   const char *,
   const char *
);
void assert_not_null(
   void *,
   free_on_error_fn,
   void *,
   const char *,
   const char *
);
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
void *vargs_setter(int, ...);
void *set_varg(uint32_t, const char *, ...);

#define C_TEST_VARGS_TITLE (uint32_t)(0x002E4992)
#define C_TEST_VARGS_INFO (uint32_t)(0x012E4992)
#define C_TEST_VARGS_WARNING (uint32_t)(0x022E4992)
#define C_TEST_VARGS_ERROR (uint32_t)(0x032E4992)
#define C_TEST_VARGS_SUCCESS (uint32_t)(0x042E4992)

#define CTEST_SETTER(...) vargs_setter(-1, __VA_ARGS__, NULL, VA_END_SIGNATURE)

#define CTEST_TITLE(...) set_varg(C_TEST_VARGS_TITLE, __VA_ARGS__)
#define CTEST_INFO(...) set_varg(C_TEST_VARGS_INFO, __VA_ARGS__)
#define CTEST_WARN(...) set_varg(C_TEST_VARGS_WARNING, __VA_ARGS__)
#define CTEST_ON_ERROR(...) set_varg(C_TEST_VARGS_ERROR, __VA_ARGS__)
#define CTEST_ON_SUCCESS(...) set_varg(C_TEST_VARGS_SUCCESS, __VA_ARGS__)

#ifdef DEBUG_TEST
// TEMPORARY FOR TESTS

 int load_test_vargs_for_test(void **, ...);
 int free_vargs_for_test(void *);
 char *ctest_setter_has_title(void *);
 char *ctest_setter_has_info(void *);
 char *ctest_setter_has_warn(void *);
 char *ctest_setter_has_onerror(void *);
 char *ctest_setter_has_onsuccess(void *);
 void show_message_text();
#endif

