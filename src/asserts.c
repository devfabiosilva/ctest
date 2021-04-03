//Fri abr 02 20:42:11 -03 2021
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <asserts.h>

static void print_assert_equal_int(void *);
static void print_assert_equal_long_int(void *);
static void print_assert_equal_double(void *);
static void print_assert_equal_byte(void *);
/*
static void debug_hex_dump(unsigned char *data, size_t data_size)
{
   for (;data_size--;)
      printf("%02X ", (unsigned char)*(data++));
}
*/
#define END_TITLE "\e[0m"
#define INITIAL_TITLE "\e[1;3m"
#define ERROR_CODE "\e[31;1m"
#define SUCCESS_CODE "\e[32;1m"

#define C_TEST_TRUE (int)(1==1)
#define C_TEST_FALSE (int)(1!=1)

#define C_TEST_HEADER_SIGNATURE (uint32_t)(0x0012E4992)

void *_c_test_ptr=NULL;

typedef struct c_test_header {
   uint32_t signature;
   size_t tests;
   uint64_t initial_timestamp;
} C_TEST_HEADER;

typedef struct c_test_fn_description {
   uint32_t type;
   const char *fn_name;
   size_t blk_size;
   void (*cb)(void *);
} C_TEST_FN_DESCRIPTION;

typedef C_TEST_FN_DESCRIPTION C_TEST_FN_META;

typedef struct c_test_type_header_t {
   C_TEST_FN_DESCRIPTION desc;

   const char
   *on_error,
   *on_success,
   *on_warning;

} C_TEST_TYPE_HEADER;

typedef struct c_test_type_int_t {
   C_TEST_TYPE_HEADER header;

   int
   expected,
   result;
} C_TEST_TYPE_INT, C_TEST_TYPE_BOOL;

typedef struct c_test_type_long_int_t {
   C_TEST_TYPE_HEADER header;

   long long int
   expected,
   result;
} C_TEST_TYPE_LONG_INT;

typedef struct c_test_type_double_t {
   C_TEST_TYPE_HEADER header;

   double
   expected,
   result;
} C_TEST_TYPE_DOUBLE;

typedef struct c_test_type_byte_t {
   C_TEST_TYPE_HEADER header;

   void
   *expected,
   *result,
   *free_on_error_ctx;

   size_t size;

   free_on_error_fn free_on_error_cb;
} C_TEST_TYPE_BYTE;

#define ASSERT_EQ_INT_FN "assert_equal_int"
#define ASSERT_TRUE_FN "assert_true"
#define ASSERT_FALSE_FN "assert_false"
#define ASSERT_EQUAL_LONG_INT "assert_equal_longint"
#define ASSERT_EQUAL_DOUBLE "assert_equal_double"
#define ASSERT_EQUAL_BYTE "assert_equal_byte"
static C_TEST_FN_DESCRIPTION _tst_fn_desc[] = {
   {0, ASSERT_EQ_INT_FN, sizeof(C_TEST_TYPE_INT), print_assert_equal_int},
   {1, ASSERT_TRUE_FN, sizeof(C_TEST_TYPE_BOOL), print_assert_equal_int},
   {2, ASSERT_FALSE_FN, sizeof(C_TEST_TYPE_BOOL), print_assert_equal_int},
   {3, ASSERT_EQUAL_LONG_INT, sizeof(C_TEST_TYPE_LONG_INT), print_assert_equal_long_int},
   {4, ASSERT_EQUAL_DOUBLE, sizeof(C_TEST_TYPE_DOUBLE), print_assert_equal_double},
   {5, ASSERT_EQUAL_BYTE, sizeof(C_TEST_TYPE_BYTE), print_assert_equal_byte}
};
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT _tst_fn_desc[0]
#define C_TEST_FN_DESCRIPTION_ASSERT_TRUE _tst_fn_desc[1]
#define C_TEST_FN_DESCRIPTION_ASSERT_FALSE _tst_fn_desc[2]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_LONG_INT _tst_fn_desc[3]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_DOUBLE _tst_fn_desc[4]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_BYTE _tst_fn_desc[5]

typedef union c_test_fn {
   C_TEST_FN_META meta;
   C_TEST_TYPE_INT tst_eq_int;
   C_TEST_TYPE_BOOL tst_eq_bool;
   C_TEST_TYPE_LONG_INT tst_eq_longint;
   C_TEST_TYPE_DOUBLE tst_eq_double;
   C_TEST_TYPE_BYTE tst_eq_byte;
} C_TEST_FN;

void end_tests()
{
   if (_c_test_ptr) {
      memset(_c_test_ptr+sizeof(C_TEST_HEADER), 0, (((C_TEST_HEADER *)_c_test_ptr)->tests)*sizeof(C_TEST_FN));
      memset(_c_test_ptr, 0, sizeof(C_TEST_HEADER));
      free(_c_test_ptr);
      _c_test_ptr=NULL;
   }
}

void abort_tests()
{
   end_tests();
   exit(1);
}

void begin_tests()
{
   C_TEST_FN *p, *q;
   size_t i;

   if (!_c_test_ptr) {
      printf("\nError: No test found. You need to add test\nExiting...\n");
      exit(1);
   }

   p=((C_TEST_FN *)(_c_test_ptr+sizeof(C_TEST_HEADER)));

   for (i=0;i<((C_TEST_HEADER *)_c_test_ptr)->tests;) {
      q=&p[i++];
      (q)->meta.cb(q);
   }

}

static void write_title(const char *message, const char *template)
{
   char *msg;

   if (!message) {
      printf("Missing message");
      abort_tests();
   }

   if (asprintf(&msg, "%s%s%s\n", template, message, END_TITLE)<0) {
      printf("Message error");
      abort_tests();
   }

   printf("%s", msg);

   free(msg);
}

#define TITLE_MSG(msg) write_title(msg, INITIAL_TITLE);
#define ERROR_MSG(msg) write_title(msg, ERROR_CODE);
#define SUCCESS_MSG(msg) write_title(msg, SUCCESS_CODE);

static void print_assert_equal_int(void *ctx)
{
   C_TEST_TYPE_INT *type=(C_TEST_TYPE_INT *)ctx;

   if (type->expected==type->result) {
      SUCCESS_MSG(type->header.on_success)
      return;
   }

   ERROR_MSG(type->header.on_error)
   abort_tests();
}

static void print_assert_equal_long_int(void *ctx)
{
   C_TEST_TYPE_LONG_INT *type=(C_TEST_TYPE_LONG_INT *)ctx;

   if (type->expected==type->result) {
      SUCCESS_MSG(type->header.on_success)
      return;
   }

   ERROR_MSG(type->header.on_error)
   abort_tests();
}

static void print_assert_equal_double(void *ctx)
{
   C_TEST_TYPE_DOUBLE *type=(C_TEST_TYPE_DOUBLE *)ctx;

   if (type->expected==type->result) {
      SUCCESS_MSG(type->header.on_success)
      return;
   }

   ERROR_MSG(type->header.on_error)
   abort_tests();
}

static void print_assert_equal_byte(void *ctx)
{
   C_TEST_TYPE_BYTE *type=(C_TEST_TYPE_BYTE *)ctx;

   if (memcmp(type->expected, type->result, type->size)) {
      ERROR_MSG(type->header.on_error)

      if (type->free_on_error_cb)
         type->free_on_error_cb(type->free_on_error_ctx);

      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success)
}

static void add_test(void *ctx)
{
   void *p;
   size_t sz_tmp;

   if (_c_test_ptr) {

      sz_tmp=(((C_TEST_HEADER *)_c_test_ptr)->tests)*sizeof(C_TEST_FN)+sizeof(C_TEST_HEADER);

      if (!(p=realloc(_c_test_ptr, sz_tmp+sizeof(C_TEST_FN)))) {
         printf("\nFatal: Error when realloc test pointer @ %p\n", _c_test_ptr);
         free(_c_test_ptr);
         exit(1);
      }

      goto add_test_EXIT1;
   }

   if (!(p=malloc((sz_tmp=sizeof(C_TEST_HEADER))+sizeof(C_TEST_FN)))) {
      printf("\nFatal: Error when initialize pointer @ NULL");
      exit(1);
   }

   ((C_TEST_HEADER *)p)->signature=C_TEST_HEADER_SIGNATURE;
   ((C_TEST_HEADER *)p)->tests=0U;
   ((C_TEST_HEADER *)p)->initial_timestamp=0UL;

add_test_EXIT1:
   ((C_TEST_HEADER *)p)->tests++;
   memcpy((_c_test_ptr=p)+sz_tmp, ctx, ((C_TEST_TYPE_HEADER *)ctx)->desc.blk_size);
}

#define ASSERT_PRELOAD \
   type.header.on_error=on_error_msg;\
   type.header.on_success=on_success;\
   type.expected=expected;\
   type.result=result;

static void assert_equal_bool(
   int expected,
   int result,
   const char *on_error_msg,
   const char *on_success
)
{
   static C_TEST_TYPE_BOOL type;

   (result==C_TEST_TRUE)?(type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_TRUE):(type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_FALSE);
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_false(int value, const char *on_error_msg, const char *on_success) { assert_equal_bool(value, C_TEST_FALSE, on_error_msg, on_success); }

void assert_true(int value, const char *on_error_msg, const char *on_success) { assert_equal_bool(value, C_TEST_TRUE, on_error_msg, on_success); }

void assert_equal_int(int expected, int result, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_INT type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT;
   ASSERT_PRELOAD
   add_test((void *)&type);

}

void assert_equal_longint(long long int expected, long long int result, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_LONG_INT type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_EQ_LONG_INT;
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_equal_double(double expected, double result, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_DOUBLE type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_EQ_DOUBLE;
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_equal_byte(
   void *expected,
   void *result,
   size_t size,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   static C_TEST_TYPE_BYTE type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_EQ_BYTE;
   ASSERT_PRELOAD
   type.size=size;
   type.free_on_error_cb=free_on_error_cb;
   type.free_on_error_ctx=free_on_error_ctx;
   add_test((void *)&type);
}

