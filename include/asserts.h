#include <stdint.h>

uint64_t *get_va_end_signature();
#define VA_END_SIGNATURE (uint64_t *)get_va_end_signature()
//df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119
typedef void (*free_on_error_fn)(void *);
typedef void (*header_on_cb)(void *);

typedef struct c_test_vargs_msg_t {
   uint32_t sig;
   int msg_sz;
   char *msg;
} C_TEST_VARGS_MSG;

typedef struct c_test_vargs_msg_header_t {
   uint32_t sig;
   uint32_t sig_chk;
   C_TEST_VARGS_MSG **vargs_msgs;
} C_TEST_VARGS_MSG_HEADER;

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
C_TEST_VARGS_MSG_HEADER *vargs_setter(int, ...);
C_TEST_VARGS_MSG *set_varg(uint32_t, const char *, ...);

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

