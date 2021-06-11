#include <stdio.h>
#include <asserts.h>
#include <string.h>

void cb_func_on_success(void *ctx)
{
   printf("\nSuccess ctx %p\n", ctx);

   if (ctx)
      printf("\nContext value on success: %s\n", (char *)ctx);
}

void cb_func_on_error(void *ctx)
{
   printf("\nError ctx %p\n", ctx);

   if (ctx)
      printf("\nContext value on error: %s\n", (char *)ctx);
}

int main(int argc, char **argv)
{
   const double delta=1E-15;
   int a, b;

   int
      vec1[]={1, 2, 3, 4},
      vec2[]={1, 2, 3, 4},
      vec3[]={2, 1, 3, 4};

   const char
      *name1="Nikola Tesla",
      *name2="Nikola Tesla",
      *name3="nikola tesla";

   TITLE_MSG("This is a simple Welcome message")
   ERROR_MSG("This is a simple ERROR message")
   SUCCESS_MSG("This is simple SUCCESS message")
   WARN_MSG("This is a simple WARNING message")
   INFO_MSG("This is a simple INFO message")

   TITLE_MSG_FMT("%s was an electrical engineer", name1)
   ERROR_MSG_FMT("Name \"%s\" is at address (%p)", name2, name2)
   INFO_MSG_FMT("Vector \"%s\" is at address (%p)", "vec1", vec1)
   SUCCESS_MSG_FMT("Size of vector \"%s\" is %u", "vec2", sizeof(vec2))
   WARN_MSG_FMT("Vector \"%s\" has %u elements", "vec3", sizeof(vec3)/sizeof(vec3[0]))

   C_ASSERT_EQUAL_INT(-1, -1)
   C_ASSERT_NOT_EQUAL_INT(11, 12)
   C_ASSERT_EQUAL_LONG_INT(3, 3)
   C_ASSERT_NOT_EQUAL_LONG_INT(1, 0xf1)
   C_ASSERT_EQUAL_DOUBLE(2., 2.3-0.3, delta)
   C_ASSERT_NOT_EQUAL_DOUBLE(5.6, 2.3-0.3, delta)
   C_ASSERT_NULL(NULL)
   C_ASSERT_NOT_NULL(vec3)
   C_ASSERT_EQUAL_STRING(name1, name2)
   C_ASSERT_EQUAL_STRING_IGNORE_CASE(name3, name2)
   C_ASSERT_NOT_EQUAL_STRING(name1, name3)
   C_ASSERT_EQUAL_BYTE(vec1, vec2, sizeof(vec1))
   C_ASSERT_FALSE(0)
   C_ASSERT_FALSE(C_TEST_FALSE)
   C_ASSERT_TRUE(C_TEST_TRUE)
   C_ASSERT_TRUE(1)

   C_TEST_BEGIN_IGNORE
   // Tests below is ignored
   C_ASSERT_EQUAL_INT(16, 15)
   C_ASSERT_NOT_EQUAL_INT(22, 22)
   C_ASSERT_EQUAL_LONG_INT(31, 30)
   C_ASSERT_NOT_EQUAL_LONG_INT(1, 1)
   // End test ignore
   C_TEST_END_IGNORE


   a = 2;
   b = 1;

   C_ASSERT_TRUE(a > b,
      CTEST_SETTER(
         CTEST_TITLE("Checking if a = %d is greater than b = %d", a, b)
      )
   )

   C_ASSERT_FALSE(C_TEST_FALSE,
      CTEST_SETTER(
         CTEST_INFO("Using calback function"),
         CTEST_ON_ERROR_CB(cb_func_on_error, "This function is called on error"),
         CTEST_ON_SUCCESS_CB(cb_func_on_success, "This function is callend on success")
      )
   )

   C_ASSERT_TRUE(1, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", 5),
      CTEST_INFO("This is an INFO title"),
      CTEST_WARN("This is a WARN message"),
      CTEST_ON_ERROR("This is a message when error occurs"),
      CTEST_ON_SUCCESS("This is a message when SUCCESS occurs")
   ))

   C_ASSERT_NOT_EQUAL_BYTE(vec1, vec3, sizeof(vec1),
      CTEST_SETTER(
         CTEST_INFO("Testing if \"vec1\" (%p) is different from \"vec3\" (%p) of size %u", vec1, vec3, sizeof(vec1)),
         CTEST_WARN("Warning: This should be different")
      )
   )

   C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE(name3, "Albert Einstein")

   end_tests();

   return 0;
}

