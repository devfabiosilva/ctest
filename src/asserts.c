//Fri abr 02 20:42:11 -03 2021
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <asserts.h>
#include <time.h>
#include <math.h>

static void print_assert_equal_int(void *);
static void print_assert_equal_long_int(void *);
static void print_assert_equal_byte(void *);
static void print_assert_not_equal_int(void *);
static void print_assert_double(void *);
static void print_assert_not_equal_long_int(void *);
static void print_assert_not_equal_byte(void *);
static void print_assert_equal_string(void *);
static void print_assert_not_equal_string(void *);
static void print_assert_equal_string_ignore_case(void *);
static void print_assert_not_equal_string_ignore_case(void *);
static void print_assert_nullable(void *ctx);

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

typedef void (*header_on_cb)(void *);

typedef struct c_test_header {
   uint32_t signature;

   size_t
   tests,
   next;

   uint64_t
   initial_timestamp,
   final_timestamp;

   header_on_cb
   on_add_test_fn,
   on_begin_test_fn,
   on_end_test_fn,
   on_abort_fn;

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

   int
   is_not_equal;

   double
   expected,
   result,
   delta;
} C_TEST_TYPE_DOUBLE;

typedef struct c_test_type_byte_t {
   C_TEST_TYPE_HEADER header;

   void
   *expected,
   *result,
   *free_on_error_ctx;

   size_t size;

   free_on_error_fn
   free_on_error_cb;
} C_TEST_TYPE_BYTE;

typedef struct c_test_type_string_t {
   C_TEST_TYPE_HEADER header;

   const char
   *expected,
   *result;
} C_TEST_TYPE_STRING;

typedef struct c_test_type_nullable_t {
   C_TEST_TYPE_HEADER header;

   int
   should_be_null;

   void
   *pointer,
   *free_on_error_ctx;

   free_on_error_fn
   free_on_error_cb;
} C_TEST_TYPE_NULLABLE;

#define ASSERT_EQ_INT_FN "assert_equal_int"
#define ASSERT_TRUE_FN "assert_true"
#define ASSERT_FALSE_FN "assert_false"
#define ASSERT_EQUAL_LONG_INT "assert_equal_longint"
#define ASSERT_EQUAL_DOUBLE "assert_equal_double"
#define ASSERT_EQUAL_BYTE "assert_equal_byte"
#define ASSERT_NOT_EQUAL_INT_FN "assert_not_equal"
#define ASSERT_NOT_EQUAL_LONG_INT "assert_not_equal_longint"
#define ASSERT_NOT_EQUAL_DOUBLE "assert_not_equal_double"
#define ASSERT_NOT_EQUAL_BYTE "assert_not_equal_byte"
#define ASSERT_EQUAL_STRING "assert_equal_string"
#define ASSERT_NOT_EQUAL_STRING "assert_not_equal_string"
#define ASSERT_EQUAL_STRING_IGNORE_CASE "assert_equal_string_ignore_case"
#define ASSERT_NOT_EQUAL_STRING_IGNORE_CASE "assert_not_equal_string_ignore_case"
#define ASSERT_NULL "assert_null"
#define ASSERT_NOT_NULL "assert_not_null"
static C_TEST_FN_DESCRIPTION _tst_fn_desc[] = {
   {0, ASSERT_EQ_INT_FN, sizeof(C_TEST_TYPE_INT), print_assert_equal_int},
   {1, ASSERT_TRUE_FN, sizeof(C_TEST_TYPE_BOOL), print_assert_equal_int},
   {2, ASSERT_FALSE_FN, sizeof(C_TEST_TYPE_BOOL), print_assert_equal_int},
   {3, ASSERT_EQUAL_LONG_INT, sizeof(C_TEST_TYPE_LONG_INT), print_assert_equal_long_int},
   {4, ASSERT_EQUAL_DOUBLE, sizeof(C_TEST_TYPE_DOUBLE), print_assert_double},
   {5, ASSERT_EQUAL_BYTE, sizeof(C_TEST_TYPE_BYTE), print_assert_equal_byte},
   {6, ASSERT_NOT_EQUAL_INT_FN, sizeof(C_TEST_TYPE_INT), print_assert_not_equal_int},
   {7, ASSERT_NOT_EQUAL_LONG_INT, sizeof(C_TEST_TYPE_LONG_INT), print_assert_not_equal_long_int},
   {8, ASSERT_NOT_EQUAL_DOUBLE, sizeof(C_TEST_TYPE_DOUBLE), print_assert_double},
   {9, ASSERT_NOT_EQUAL_BYTE, sizeof(C_TEST_TYPE_BYTE), print_assert_not_equal_byte},
   {10, ASSERT_EQUAL_STRING, sizeof(C_TEST_TYPE_STRING), print_assert_equal_string},
   {11, ASSERT_NOT_EQUAL_STRING, sizeof(C_TEST_TYPE_STRING), print_assert_not_equal_string},
   {12, ASSERT_EQUAL_STRING_IGNORE_CASE, sizeof(C_TEST_TYPE_STRING), print_assert_equal_string_ignore_case},
   {13, ASSERT_NOT_EQUAL_STRING_IGNORE_CASE, sizeof(C_TEST_TYPE_STRING), print_assert_not_equal_string_ignore_case},
   {14, ASSERT_NULL, sizeof(C_TEST_TYPE_NULLABLE), print_assert_nullable},
   {15, ASSERT_NOT_NULL, sizeof(C_TEST_TYPE_NULLABLE), print_assert_nullable}
};
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT _tst_fn_desc[0]
#define C_TEST_FN_DESCRIPTION_ASSERT_TRUE _tst_fn_desc[1]
#define C_TEST_FN_DESCRIPTION_ASSERT_FALSE _tst_fn_desc[2]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_LONG_INT _tst_fn_desc[3]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_DOUBLE _tst_fn_desc[4]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_BYTE _tst_fn_desc[5]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_INT _tst_fn_desc[6]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_LONG_INT _tst_fn_desc[7]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_DOUBLE _tst_fn_desc[8]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_BYTE _tst_fn_desc[9]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_STRING _tst_fn_desc[10]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_STRING _tst_fn_desc[11]
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_STRING_IGNORE_CASE _tst_fn_desc[12]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_STRING_IGNORE_CASE _tst_fn_desc[13]
#define C_TEST_FN_DESCRIPTION_ASSERT_NULL _tst_fn_desc[14]
#define C_TEST_FN_DESCRIPTION_ASSERT_NOT_NULL _tst_fn_desc[15]

typedef union c_test_fn {
   C_TEST_FN_META meta;
   C_TEST_TYPE_INT tst_eq_int;
   C_TEST_TYPE_BOOL tst_eq_bool;
   C_TEST_TYPE_LONG_INT tst_eq_longint;
   C_TEST_TYPE_DOUBLE tst_eq_double;
   C_TEST_TYPE_BYTE tst_eq_byte;
   C_TEST_TYPE_STRING tst_eq_string;
   C_TEST_TYPE_NULLABLE tst_eq_null;
} C_TEST_FN;

#define PRINTF_FINAL_FMT printf("%.*s", err, msg);
static void write_title(const char *message, const char *template)
{
   int err;
   char *msg;

   if (!message) {
      printf("Missing message");
      abort_tests();
   }

   if ((err=asprintf(&msg, "%s%s%s\n", template, message, END_TITLE))<0) {
      printf("Message error");
      abort_tests();
   }

   PRINTF_FINAL_FMT

   free(msg);
}

static void write_title_fmt(const char *template, const char *fmt, ...)
{
   int err;
   char *msg_fmt, *msg;
   va_list args;

   if (!fmt) {
      printf("Missing format at \"write_title_fmt\"");
      abort_tests();
   }

   va_start(args, fmt);
   err=vasprintf(&msg_fmt, fmt, args);
   va_end(args);

   if (err<0) {
      printf("Message format error at \"write_title_fmt\"");
      free(msg_fmt);
      abort_tests();
   }

   err=asprintf(&msg, "%s%.*s%s\n", template, err, msg_fmt, END_TITLE);

   free(msg_fmt);

   if (err<0) {
      printf("Final message error at \"write_title_fmt\"");
      abort_tests();
   }

   PRINTF_FINAL_FMT

   free(msg);
}

#define TITLE_MSG(msg) write_title(msg, INITIAL_TITLE);
#define ERROR_MSG(msg) write_title(msg, ERROR_CODE);
#define SUCCESS_MSG(msg) write_title(msg, SUCCESS_CODE);

#define TITLE_MSG_FMT(...) write_title_fmt(INITIAL_TITLE, __VA_ARGS__);

void end_tests()
{
   if (_c_test_ptr) {
      if (((C_TEST_HEADER *)_c_test_ptr)->tests)
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
   size_t i, total;
   time_t t;

   if (!_c_test_ptr) {
      printf("\nError: No test found. You need to add test\nExiting...\n");
      exit(1);
   }

   p=((C_TEST_FN *)(_c_test_ptr+sizeof(C_TEST_HEADER)));
   total=((C_TEST_HEADER *)_c_test_ptr)->tests;
   ((C_TEST_HEADER *)_c_test_ptr)->initial_timestamp=(uint64_t)(t=time(NULL));

   TITLE_MSG_FMT("*** BEGIN TESTS ***\nAt: %s", ctime(&t))

   for (i=((C_TEST_HEADER *)_c_test_ptr)->next;i<total;) {
      q=&p[i++];
      TITLE_MSG_FMT("Testing \"%s\" ...", q->meta.fn_name);
      q->meta.cb(q);
      TITLE_MSG_FMT("progress: (%d%)", (i*100)/total);
   }

   ((C_TEST_HEADER *)_c_test_ptr)->next=i;

   ((C_TEST_HEADER *)_c_test_ptr)->final_timestamp=(uint64_t)(t=time(NULL));

   TITLE_MSG_FMT("*** END TESTS ***\nAt: %s", ctime(&t))
   TITLE_MSG_FMT("Total time: %llu\n", (uint64_t)t-((C_TEST_HEADER *)_c_test_ptr)->initial_timestamp)
}

#define C_TEST_INITIAL_ADD \
   ((C_TEST_HEADER *)p)->signature=C_TEST_HEADER_SIGNATURE;\
   ((C_TEST_HEADER *)p)->tests=0U;\
   ((C_TEST_HEADER *)p)->next=0U;\
   ((C_TEST_HEADER *)p)->initial_timestamp=0UL;\
   ((C_TEST_HEADER *)p)->final_timestamp=0UL;

#define C_TEST_ON_ADD_FN(fn) ((C_TEST_HEADER *)p)->on_add_test_fn=fn;
#define C_TEST_ON_BEGIN_FN(fn) ((C_TEST_HEADER *)p)->on_begin_test_fn=fn;
#define C_TEST_ON_END_FN(fn) ((C_TEST_HEADER *)p)->on_end_test_fn=fn;
#define C_TEST_ON_ABORT_FN(fn) ((C_TEST_HEADER *)p)->on_abort_fn=fn;

#define C_TEST_INITIAL_ADD_FN_ALL_NULL \
   C_TEST_ON_ADD_FN(NULL) \
   C_TEST_ON_BEGIN_FN(NULL) \
   C_TEST_ON_END_FN(NULL) \
   C_TEST_ON_ABORT_FN(NULL)

void on_add_test(header_on_cb fn)
{
   #define p _c_test_ptr

   if (!fn) {
      ERROR_MSG("Fatal: on_add_test missing callback function")
      abort_tests();
   }

   if (!p)
      if (!(p=malloc(sizeof(C_TEST_HEADER)))) {
         ERROR_MSG("Fatal: on_add_test missing callback function")
         abort_tests();
      }

   C_TEST_INITIAL_ADD
   C_TEST_ON_ADD_FN(fn)
   C_TEST_ON_BEGIN_FN(NULL)
   C_TEST_ON_END_FN(NULL)
   C_TEST_ON_ABORT_FN(NULL)

   #undef p
}

void rm_on_add_test()
{
   #define p _c_test_ptr

   if (p)
      C_TEST_ON_ADD_FN(NULL)

   #undef p
}

static void print_assert_int(void *ctx, int is_not_equal)
{
   C_TEST_TYPE_INT *type=(C_TEST_TYPE_INT *)ctx;

   if (is_not_equal) {
      if (type->expected!=type->result)
         goto print_assert_int_EXIT;
   } else if (type->expected==type->result) {
print_assert_int_EXIT:
      SUCCESS_MSG(type->header.on_success)
      return;
   }

   ERROR_MSG(type->header.on_error)
   abort_tests();
}

static void print_assert_equal_int(void *ctx) { print_assert_int(ctx, 0); }

static void print_assert_not_equal_int(void *ctx) { print_assert_int(ctx, 1); }

static void print_assert_longint(void *ctx, int is_not_equal)
{
   C_TEST_TYPE_LONG_INT *type=(C_TEST_TYPE_LONG_INT *)ctx;

   if (is_not_equal) {
      if (type->expected!=type->result)
         goto print_assert_longint_EXIT1;
   } else if (type->expected==type->result) {
print_assert_longint_EXIT1:
      SUCCESS_MSG(type->header.on_success)
      return;
   }

   ERROR_MSG(type->header.on_error)
   abort_tests();
}

static void print_assert_equal_long_int(void *ctx) { print_assert_longint(ctx, 0); }

static void print_assert_not_equal_long_int(void *ctx) { print_assert_longint(ctx, 1); }

static void print_assert_double(void *ctx)
{
   C_TEST_TYPE_DOUBLE *type=(C_TEST_TYPE_DOUBLE *)ctx;
   int error=0;

   if (fabs(type->expected-type->result)>fabs(type->delta))
      error=1;

   if (type->is_not_equal)
      error=!error;

   if (error) {
      ERROR_MSG(type->header.on_error)
      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success)
}

static void print_assert_byte(void *ctx, int is_not_equal)
{
   C_TEST_TYPE_BYTE *type=(C_TEST_TYPE_BYTE *)ctx;
   int tst=memcmp(type->expected, type->result, type->size);

   if (is_not_equal)
      (tst)?(tst=0):(tst=-1);

   if (tst) {
      ERROR_MSG(type->header.on_error)

      if (type->free_on_error_cb)
         type->free_on_error_cb(type->free_on_error_ctx);

      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success)
}

static void print_assert_equal_byte(void *ctx) { print_assert_byte(ctx, 0); }

static void print_assert_not_equal_byte(void *ctx) { print_assert_byte(ctx, 1); }

static void print_assert_string(void *ctx, int is_not_equal, int is_ignore_case)
{
   C_TEST_TYPE_STRING *type=(C_TEST_TYPE_STRING *)ctx;
   int tst=(is_ignore_case)?(strcasecmp(type->expected, type->result)):(strcmp(type->expected, type->result));

   if (is_not_equal)
      (tst)?(tst=0):(tst=-1);

   if (tst) {
      ERROR_MSG(type->header.on_error)
      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success)
}

static void print_assert_equal_string(void *ctx) { print_assert_string(ctx, 0, 0); }

static void print_assert_not_equal_string(void *ctx) { print_assert_string(ctx, 1, 0); }

static void print_assert_equal_string_ignore_case(void *ctx) { print_assert_string(ctx, 0, 1); }

static void print_assert_not_equal_string_ignore_case(void *ctx) { print_assert_string(ctx, 1, 1); }

static void print_assert_nullable(void *ctx)
{
   C_TEST_TYPE_NULLABLE *type=(C_TEST_TYPE_NULLABLE *)ctx;
   int error=(type->should_be_null)?(type->pointer!=NULL):(type->pointer==NULL);

   if (error) {
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

   TITLE_MSG("Begin adding test ...")

   C_TEST_INITIAL_ADD
   C_TEST_INITIAL_ADD_FN_ALL_NULL

add_test_EXIT1:
   memcpy((_c_test_ptr=p)+sz_tmp, ctx, ((C_TEST_TYPE_HEADER *)ctx)->desc.blk_size);
   TITLE_MSG_FMT("Adding test instance \"%s\" (%d)", ((C_TEST_FN_DESCRIPTION *)ctx)->fn_name, ++((C_TEST_HEADER *)p)->tests)

   if (((C_TEST_HEADER *)p)->on_add_test_fn)
      ((C_TEST_HEADER *)p)->on_add_test_fn(ctx);
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

static void assert_int(int expected, int result, C_TEST_FN_DESCRIPTION *desc, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_INT type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_equal_int(int expected, int result, const char *on_error_msg, const char *on_success)
{
   assert_int(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT, on_error_msg, on_success);
}

void assert_not_equal_int(int expected, int result, const char *on_error_msg, const char *on_success)
{
   assert_int(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_INT, on_error_msg, on_success);
}

static void assert_longint(int expected, int result, C_TEST_FN_DESCRIPTION *desc, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_LONG_INT type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_equal_longint(long long int expected, long long int result, const char *on_error_msg, const char *on_success)
{
   assert_longint(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_LONG_INT, on_error_msg, on_success);
}

void assert_not_equal_longint(long long int expected, long long int result, const char *on_error_msg, const char *on_success)
{
   assert_longint(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_LONG_INT, on_error_msg, on_success);
}

static void assert_double(double expected, double result, double delta, C_TEST_FN_DESCRIPTION *desc, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_DOUBLE type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   ASSERT_PRELOAD
   type.is_not_equal=(desc==&C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_DOUBLE);
   type.delta=delta;
   add_test((void *)&type);
}

void assert_equal_double(double expected, double result, double delta, const char *on_error_msg, const char *on_success)
{
   assert_double(expected, result, delta, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_DOUBLE, on_error_msg, on_success);
}

void assert_not_equal_double(double expected, double result, double delta, const char *on_error_msg, const char *on_success)
{
   assert_double(expected, result, delta, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_DOUBLE, on_error_msg, on_success);
}

static void assert_byte(
   void *expected,
   void *result,
   size_t size,
   C_TEST_FN_DESCRIPTION *desc,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   static C_TEST_TYPE_BYTE type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   ASSERT_PRELOAD
   type.size=size;
   type.free_on_error_cb=free_on_error_cb;
   type.free_on_error_ctx=free_on_error_ctx;
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
   assert_byte(expected, result, size, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_BYTE, free_on_error_cb, free_on_error_ctx, on_error_msg, on_success);
}

void assert_not_equal_byte(
   void *expected,
   void *result,
   size_t size,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   assert_byte(expected, result, size, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_BYTE, free_on_error_cb, free_on_error_ctx, on_error_msg, on_success);
}

static void assert_string(
   const char *expected,
   const char *result,
   C_TEST_FN_DESCRIPTION *desc,
   const char *on_error_msg,
   const char *on_success
)
{
   static C_TEST_TYPE_STRING type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   ASSERT_PRELOAD
   add_test((void *)&type);
}

void assert_equal_string(const char *expected, const char *result, const char *on_error_msg, const char *on_success)
{
   assert_string(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_STRING, on_error_msg, on_success);
}

void assert_not_equal_string(const char *expected, const char *result, const char *on_error_msg, const char *on_success)
{
   assert_string(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_STRING, on_error_msg, on_success);
}

void assert_equal_string_ignore_case(const char *expected, const char *result, const char *on_error_msg, const char *on_success)
{
   assert_string(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_EQ_STRING_IGNORE_CASE, on_error_msg, on_success);
}

void assert_not_equal_string_ignore_case(const char *expected, const char *result, const char *on_error_msg, const char *on_success)
{
   assert_string(expected, result, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_EQ_STRING_IGNORE_CASE, on_error_msg, on_success);
}

static void assert_nullable(
   void *result,
   C_TEST_FN_DESCRIPTION *desc,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   static C_TEST_TYPE_NULLABLE type;

   memcpy(&type.header.desc, desc, sizeof(type.header.desc));
   type.should_be_null=(desc==&C_TEST_FN_DESCRIPTION_ASSERT_NULL);
   type.header.on_error=on_error_msg;
   type.header.on_success=on_success;
   type.pointer=result;
   type.free_on_error_cb=free_on_error_cb;
   type.free_on_error_ctx=free_on_error_ctx;
   add_test((void *)&type);
}

void assert_null(
   void *result,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   assert_nullable(result, &C_TEST_FN_DESCRIPTION_ASSERT_NULL, free_on_error_cb, free_on_error_ctx, on_error_msg, on_success);
}

void assert_not_null(
   void *result,
   free_on_error_fn free_on_error_cb,
   void *free_on_error_ctx,
   const char *on_error_msg,
   const char *on_success
)
{
   assert_nullable(result, &C_TEST_FN_DESCRIPTION_ASSERT_NOT_NULL, free_on_error_cb, free_on_error_ctx, on_error_msg, on_success);
}

