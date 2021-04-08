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
void begin_tests();
void end_tests();
void abort_tests();

