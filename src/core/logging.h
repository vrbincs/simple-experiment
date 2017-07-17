#ifndef ENGINE2D_LOGGING_H
   #define ENGINE2D_LOGGING_H

#include <iostream>
#define LOGGER_INFO(msg) std::cout << msg << std::endl;
#define LOGGER_ERROR(msg) LOGGER_INFO(msg)
#define LOGGER_WARN(msg) LOGGER_INFO(msg)
#define LOGGER_TRACE(msg) 

#endif // ENGINE2D_LOGGING_H
