#import "MWLogging.h"

#if !DEBUG
    #import <Crashlytics/Crashlytics.h>
#endif

#ifdef MW_COMPILE_TIME_LOG_LEVEL
    #undef MW_COMPILE_TIME_LOG_LEVEL
#endif

#if DEBUG
    #define MW_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_DEBUG
#else
    #define MW_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_NOTICE
#endif

#if DEBUG
    #define VSLogDebug(...) \
    do \
    { \
        NSString *message = [NSString stringWithFormat:__VA_ARGS__]; \
        MWLogDebug(@"%@ in %s of %s:%u", message, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
    } \
    while(0)
#else
    #define VSLogDebug(...)
#endif

#if DEBUG
    #define VSLogWarning(...) \
    do \
    { \
        NSString *message = [NSString stringWithFormat:__VA_ARGS__]; \
        MWLogWarning(@"%@ in %s of %s:%u", message, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
    } \
    while(0)
#elif ADHOC
    #define VSLogWarning(...) \
    do \
    { \
        NSString *message = [NSString stringWithFormat:__VA_ARGS__]; \
        MWLogWarning(@"%@ in %s of %s:%u", message, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
        CLS_LOG(@"<warning> %@", message); \
    } \
    while(0)
#else
    #define VSLogWarning(...)
#endif

#if ADHOC
    #define VSLogError(...) \
    do \
    { \
        NSString *message = [NSString stringWithFormat:__VA_ARGS__]; \
        MWLogError(@"%@ in %s of %s:%u", message, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
        CLS_LOG(@"<error> %@", message); \
    } \
    while(0)
#else
    #define VSLogError(...) \
    do \
    { \
        NSString *message = [NSString stringWithFormat:__VA_ARGS__]; \
        MWLogError(@"%@ in %s of %s:%u", message, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
    } \
    while(0)
#endif

#if ADHOC
    #define VSAssert(condition, ...) \
    do \
    { \
        if(!(condition)) \
        { \
            NSString *assertMessage = [NSString stringWithFormat:__VA_ARGS__]; \
            VSLogError(@"<assert> %@", assertMessage); \
        } \
    } \
    while(0)
#else
    #define VSAssert(condition, desc, ...) NSAssert(condition, desc, ##__VA_ARGS__)
#endif
