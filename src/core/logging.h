#ifndef ENGINE2D_LOGGING_H
   #define ENGINE2D_LOGGING_H

#include <iostream>
#include <memory>

class CStreamWrap;
typedef std::shared_ptr<CStreamWrap> CStreamWrapPtr;

class Logger
{
public:
   Logger(const char *module);
   ~Logger();
   
   static void setModuleFile(Logger *logger,
                             const char *module,
                             const char *filename);
   
   Logger &log(const char *line, int number);
   
   Logger &operator<<(const char *string);
   Logger &operator<<(const std::string &string);
   Logger &operator<<(const char chr);
   Logger &operator<<(const int val);
   Logger &operator<<(const unsigned int val);
   Logger &operator<<(const double val);
   Logger &operator<<(const long long val);
   Logger &operator<<(const long unsigned val);
   Logger &operator<<(const void *val);
private:
   const char *m_module;
   CStreamWrapPtr m_streamInfo;
};

#define LOGGING_INIT(module) static Logger logger(module);
#define LOGGING_FILE(module, filename) Logger::setModuleFile(logger, module, filename);

#define LOGGER_INFO(msg) logger.log(__FILE__, __LINE__) << msg << '\n';
#define LOGGER_ERROR(msg) LOGGER_INFO(msg)
#define LOGGER_WARN(msg) LOGGER_INFO(msg)
#define LOGGER_TRACE(msg) LOGGER_INFO(msg)

#endif // ENGINE2D_LOGGING_H
