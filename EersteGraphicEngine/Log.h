#pragma once

#if defined(EGE_DEBUG)
#   ifndef EGE_DEBUG_LOG_FILE
#	define EGE_DEBUG_LOG_FILE "log/debug.log"
#	endif

#	ifndef EGE_LOG_DEBUG
#	define EGE_LOG_DEBUG(message)																	\
		{																							\
				std::ofstream logFile(EGE_DEBUG_LOG_FILE, std::ios_base::out | std::ios_base::app);	\
																									\
				logFile << "Log: " << __FILE__ << ":" << __LINE__;									\
				logFile << " inside " << __FUNCTION__ << std::endl;									\
				logFile << "Date: " << __DATE__ << std::endl;										\
				logFile << "Time: " << __TIME__ << std::endl;										\
				logFile << "Message: " << message << std::endl;										\
				logFile << "############################################: " << std::endl;			\
		}																					
#	endif
#else 
#	ifndef EGE_DEBUG
#	define EGE_DEBUG(message)
#	endif
#endif