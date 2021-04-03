typedef void (*free_on_error_fn)(void *);
void assert_true(int, const char *, const char *);
void assert_false(int, const char *, const char *);
void assert_equal_int(int, int, const char *, const char *);
void assert_equal_longint(long long int, long long int, const char *, const char *);
void assert_equal_double(double, double, const char *, const char *);
void assert_equal_byte(
   void *,
   void *,
   size_t,
   free_on_error_fn,
   void *,
   const char *,
   const char *
);
void begin_tests();
void end_tests();

