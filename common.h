#define LOG_ENABLE (0)

#define LOG(FORMAT, ...) \
do { \
    if (LOG_ENABLE) \
        printf ("%s:%d [%s] "FORMAT, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
} while (0)

#define LOG_RED(_FMT_, ...) \
    do { \
        printf ("\e[0;31m" _FMT_ "\e[0m", ##__VA_ARGS__); \
    } while (0)

#define RET_ON_NULL(_PTR_, _RET_) \
do { \
    if (_PTR_ == NULL) \
        return _RET_; \
} while (0)

#define FREE(_PTR_) \
do { \
    if (_PTR_ != NULL) \
    { \
        free (_PTR_); \
        _PTR_ = NULL; \
    } \
} while (0)
