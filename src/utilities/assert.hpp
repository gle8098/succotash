#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cassert>

#define ERROR_LEVEL   0
#define WARNING_LEVEL 1

#define ASSERT_LEVEL WARNING_LEVEL

#if ASSERT_LEVEL == ERROR_LEVEL
#define ASSERT(statement) assert(statement)
#elif ASSERT_LEVEL == WARNING_LEVEL
#define ASSERT(statement) ASSERT_WARN(statement)
#else
#define ASSERT(statement) // Do nothing
#endif  // ASSERT_LEVEL

#define ASSERT_WARN(statement)                                        \
  if (!(statement)) {                                                 \
    fprintf(stderr, "WARNING: %s : %s : %d assertion `%s` failed.\n", \
            __FILE__, __func__, __LINE__, #statement);                \
  }

#define WARNING(message)                                              \
    fprintf(stderr, "WARNING: %s : %s : %d : %s\n",                   \
            __FILE__, __func__, __LINE__, message);

#endif // ASSERT_HPP
