//Fri abr 02 20:42:11 -03 2021
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void print_assert_false(void *);
static void print_assert_true(void *);
static void print_assert_equal_int(void *);

#define ASSERT_EQ_INT_FN "assert_equal_int"
#define ASSERT_TRUE_FN "assert_true"
#define ASSERT_FALSE_FN "assert_false"

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
} C_TEST_TYPE_INT;

typedef struct c_test_type_false_t {
   C_TEST_TYPE_HEADER header;
   int value;
} C_TEST_TYPE_FALSE;

typedef struct c_test_type_true_t {
   C_TEST_TYPE_HEADER header;
   int value;
} C_TEST_TYPE_TRUE;

static C_TEST_FN_DESCRIPTION _tst_fn_desc[] = {
   {1, ASSERT_EQ_INT_FN, sizeof(C_TEST_TYPE_INT), print_assert_equal_int},
   {2, ASSERT_TRUE_FN, sizeof(C_TEST_TYPE_TRUE), print_assert_true},
   {3, ASSERT_FALSE_FN, sizeof(C_TEST_TYPE_FALSE), print_assert_false}
};
#define C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT _tst_fn_desc[0]
#define C_TEST_FN_DESCRIPTION_ASSERT_TRUE _tst_fn_desc[1]
#define C_TEST_FN_DESCRIPTION_ASSERT_FALSE _tst_fn_desc[2]
 
typedef union c_test_fn {
   C_TEST_FN_META meta;
   C_TEST_TYPE_INT tst_eq_int;
   C_TEST_TYPE_TRUE tst_true;
   C_TEST_TYPE_FALSE tst_false;
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

static void print_assert_false(void *ctx)
{

   C_TEST_TYPE_FALSE *type=(C_TEST_TYPE_FALSE *)ctx;

   if (type->value) {
      ERROR_MSG(type->header.on_error);
      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success);
}

static void print_assert_true(void *ctx)
{

   C_TEST_TYPE_TRUE *type=(C_TEST_TYPE_TRUE *)ctx;

   if (!type->value) {
      ERROR_MSG(type->header.on_error);
      abort_tests();
   }

   SUCCESS_MSG(type->header.on_success);
}

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

static void add_test(void *ctx)
{
   void *p;

   if (_c_test_ptr) {

      if (!(p=realloc(_c_test_ptr, sizeof(C_TEST_HEADER)+sizeof(C_TEST_FN)+(((C_TEST_HEADER *)_c_test_ptr)->tests)*sizeof(C_TEST_FN)))) {
         printf("\nFatal: Error when realloc test pointer @ %p\n", _c_test_ptr);
         free(_c_test_ptr);
         exit(1);
      }

      goto add_test_EXIT1;
   }

   if (!(p=malloc(sizeof(C_TEST_HEADER)+sizeof(C_TEST_FN)))) {
      printf("\nFatal: Error when initialize pointer @ NULL");
      exit(1);
   }

   ((C_TEST_HEADER *)p)->signature=C_TEST_HEADER_SIGNATURE;
   ((C_TEST_HEADER *)p)->tests=0U;
   ((C_TEST_HEADER *)p)->initial_timestamp=0UL;

add_test_EXIT1:
   memcpy((_c_test_ptr=p)+sizeof(C_TEST_HEADER)+((((C_TEST_HEADER *)p)->tests++)*sizeof(C_TEST_FN)), ctx, ((C_TEST_TYPE_HEADER *)ctx)->desc.blk_size);
}

#define ASSERT_PRELOAD \
   type.header.on_error=on_error_msg;\
   type.header.on_success=on_success;

void assert_false(int value, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_FALSE type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_FALSE;
   ASSERT_PRELOAD
   type.value=value;
   add_test((void *)&type);
}

void assert_true(int value, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_TRUE type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_TRUE;
   ASSERT_PRELOAD
   type.value=value;
   add_test((void *)&type);
}

void assert_equal_int(int expected, int result, const char *on_error_msg, const char *on_success)
{
   static C_TEST_TYPE_INT type;

   type.header.desc=C_TEST_FN_DESCRIPTION_ASSERT_EQ_INT;
   ASSERT_PRELOAD
   type.expected=expected;
   type.result=result;
   add_test((void *)&type);

}

