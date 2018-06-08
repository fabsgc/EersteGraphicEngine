#pragma once

#if defined(EGE_DEBUG)
#   ifndef EGE_ERROR_LOG_FILE
#       define EGE_ERROR_LOG_FILE "log/Errors.log"
#   endif

#   ifndef EGE_ASSERT_ERROR
#   define EGE_ASSERT_ERROR(condition, error)                                                           \
        {                                                                                               \
            if (!(condition))                                                                           \
            {                                                                                           \
                std::ofstream errorFile(EGE_ERROR_LOG_FILE, std::ios_base::out | std::ios_base::app);   \
                                                                                                        \
                errorFile << "Assertion failed at " << __FILE__ << ":" << __LINE__ << std::endl;        \
                errorFile << "Inside " << __FUNCTION__ << std::endl;                                    \
                errorFile << "Date: " << __DATE__ << std::endl;                                         \
                errorFile << "Time: " << __TIME__ << std::endl;                                         \
                errorFile << "Error: " << error << std::endl;                                           \
                errorFile << "Condition: " << (condition) << std::endl;                                   \
                errorFile << "############################################: " << std::endl;             \
                assert((condition));                                                                      \
            }                                                                                           \
        }                                                                                   
#   endif

#   ifndef EGE_ASSERT_ERROR_SHORT
#   define EGE_ASSERT_ERROR_SHORT(condition)                                                            \
        {                                                                                               \
            if (!(condition))                                                                           \
            {                                                                                           \
                std::ofstream errorFile(EGE_ERROR_LOG_FILE, std::ios_base::out | std::ios_base::app);   \
                                                                                                        \
                errorFile << "Assertion failed at " << __FILE__ << ":" << __LINE__;                     \
                errorFile << " inside " << __FUNCTION__ << std::endl;                                   \
                errorFile << "Date: " << __DATE__ << std::endl;                                         \
                errorFile << "Time: " << __TIME__ << std::endl;                                         \
                errorFile << "Condition: " << (condition);                                                \
                errorFile << "############################################: " << std::endl;             \
                assert((condition));                                                                      \
            }                                                                                           \
        }                                                                                   
#   endif
#else 
#   ifndef EGE_ASSERT_ERROR
#   define EGE_ASSERT_ERROR(condition, error) (condition)
#   endif

#   ifndef EGE_ASSERT_ERROR_SHORT
#   define EGE_ASSERT_ERROR_SHORT(condition) (condition)
#   endif
#endif