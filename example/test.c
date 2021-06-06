#include <stdio.h>
#include <math.h>
#include <asserts.h>
#include <string.h>
#include <stdint.h>

void cb_func_on_success(void *ctx)
{
   printf("\nSuccess ctx %p\n", ctx);

   if (ctx)
      printf("\nCTX VALUE %s\n", (char *)ctx);
}

void cb_func_on_error(void *ctx)
{
   printf("\nError ctx %p\n", ctx);

   if (ctx)
      printf("\nCTX VALUE %s\n", (char *)ctx);
}

int main(int argc, char **argv)
{
   const double delta=1E-15;

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
//TODO FINISH IMPLEMENT EXAMPLE
   C_ASSERT_FALSE(1, CTEST_SETTER(CTEST_INFO("This is an INFO title"), CTEST_ON_ERROR_CB(cb_func_on_error, "jgg"), CTEST_ON_SUCCESS_CB(cb_func_on_success, "hhj")))

   C_ASSERT_FALSE(0)

   C_ASSERT_TRUE(1, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", 5),
      CTEST_INFO("This is an INFO title"),
      CTEST_WARN("This is a WARN message"),
      CTEST_ON_ERROR("This is a message when error occurs"),
      CTEST_ON_SUCCESS("This is a message when SUCCESS occurs")
   ))

   C_ASSERT_EQUAL_INT(-1, -1)

   C_ASSERT_NOT_EQUAL_INT(11,12)

   C_ASSERT_EQUAL_LONG_INT(3, 3)
   C_ASSERT_NOT_EQUAL_LONG_INT(1, 0xf1)

   C_ASSERT_EQUAL_DOUBLE(2., 2.3-0.3, delta)

   C_ASSERT_NOT_EQUAL_DOUBLE(5.6, 2.3-0.3, delta)

   C_ASSERT_EQUAL_BYTE(vec1, vec2, sizeof(vec1))

   C_ASSERT_NOT_EQUAL_BYTE(vec1, vec3, sizeof(vec1), CTEST_SETTER(CTEST_INFO("Testando esse vetor"), CTEST_WARN("ALERTA: Ele deve ser diferente!!!")))

   C_ASSERT_NULL(NULL)

   C_ASSERT_NOT_NULL(vec3)

   C_ASSERT_EQUAL_STRING(name1, name2)

   C_ASSERT_EQUAL_STRING_IGNORE_CASE(name3, name2)

   C_ASSERT_NOT_EQUAL_STRING(name1, name3)

   C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE(name3, "Albert Einstein")

   end_tests();

   return 0;
}

