#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cassert>

#define ERROR   0
#define WARNING 1

#define ASSERT_LEVEL WARNING

#if ASSERT_LEVEL == ERROR
#define ASSERT(statement) assert(statement)
#elif ASSERT_LEVEL == WARNING
#define ASSERT(statement) ASSERT_WARN(statement)
#else
#define ASSERT(statement) // Do nothing
#endif  // ASSERT_LEVEL

#define ASSERT_WARN(                                                  \
  if (!(statement)) {                                                 \
    fprintf(stderr, "WARNING: %s : %s : %d assertion `%s` failed.\n", \
            __FILE__, __func__, __LINE__, #statement);                \
  }

#endif // ASSERT_HPP

