#ifndef ENGINE2D_LOGGING_H
   #define ENGINE2D_LOGGING_H

#include <iostream>

class Logger
{
public:
   Logger(const char *module);
   
   static void setModuleFile(Logger *logger,
                             const char *module,
                             const char *filename);
   std::ostream &writer();
private:
   const char *m_module;
   std::ostream *m_stream;
};

#define LOGGING_INIT(module) static Logger logger(module);
#define LOGGING_FILE(module, filename) Logger::setModuleFile(logger, module, filename);

#define LOGGER_INFO(msg) logger.writer() << msg << std::endl;
#define LOGGER_ERROR(msg) LOGGER_INFO(msg)
#define LOGGER_WARN(msg) LOGGER_INFO(msg)
#define LOGGER_TRACE(msg) LOGGER_INFO(msg)

#endif // ENGINE2D_LOGGING_H
