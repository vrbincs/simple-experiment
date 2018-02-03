#include <map>
#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>

#include "logging.h"

class CStreamWrap
{
public:
   CStreamWrap(std::ostream *stream_t)
      : stream(stream_t),
        refCount(0)
   {
   }
   
   virtual ~CStreamWrap(){}
   
   std::ostream *stream;
   int refCount;
};

class COFStreamWrap : public CStreamWrap
{
public:
   COFStreamWrap(std::ofstream *stream_t)
      : CStreamWrap(stream_t)
   {
   }
   
   ~COFStreamWrap()
   {
      dynamic_cast<std::ofstream *>(stream)->close();
      delete stream;
   }
   
   static CStreamWrap *create(std::ofstream *stream)
   {
      return new COFStreamWrap(stream);
   }
};

typedef std::shared_ptr<CStreamWrap> CStreamWrapPtr;

static CStreamWrapPtr stdoutWrap(new CStreamWrap(&std::cout));
static std::map<std::string, CStreamWrapPtr> getModulesFromSettings();
static std::map<std::string, CStreamWrapPtr> l_moduleFileMap = getModulesFromSettings();

static CStreamWrapPtr setModuleFilePriv(const char *module,
                                        const char *filename,
                                        std::map<std::string, CStreamWrapPtr> &);



Logger::Logger(const char *module)
   : m_module(module),
     m_streamInfo(NULL)
{
   auto mod_it = l_moduleFileMap.find(module);
   
   if(mod_it != l_moduleFileMap.end())
   {
      mod_it->second->refCount++;
      m_streamInfo = mod_it->second;
   }
   else
   {
      m_streamInfo = stdoutWrap;
   }
}

Logger::~Logger()
{
   auto mod_it = l_moduleFileMap.find(m_module);
   
   if(mod_it != l_moduleFileMap.end())
   {
      mod_it->second->refCount--;
      
      if(mod_it->second->refCount <= 0)
      {
         l_moduleFileMap.erase(mod_it);
      }
   }
}

void Logger::setModuleFile(Logger *logger,
                           const char *module,
                           const char *filename)
{
   logger->m_streamInfo = setModuleFilePriv(module, filename, l_moduleFileMap);
}

Logger &Logger::log(const char *line, int number)
{
   *this << "[" << line << ":" << number << "]: ";
   return *this;
}

CStreamWrapPtr setModuleFilePriv(const char *module,
                                 const char *filename,
                                 std::map<std::string, CStreamWrapPtr> &modMap)
{
   auto mod_it = modMap.find(module);
   
   // Open new file, if the module has not been registered yet
   if(mod_it == modMap.end())
   {
      std::unique_ptr<std::ofstream> filestream_ptr(new std::ofstream(filename, std::ofstream::out | std::ofstream::app));
   
      if(filestream_ptr->is_open())
      {
         CStreamWrapPtr streamInfoPtr(COFStreamWrap::create(filestream_ptr.release()));
         modMap.insert(std::pair<std::string, CStreamWrapPtr>(module, streamInfoPtr));
         
         return streamInfoPtr;
      }
   }
   else
   {
      return mod_it->second;
   }
   
   return stdoutWrap;
}

std::map<std::string, CStreamWrapPtr> getModulesFromSettings()
{
   std::map<std::string, CStreamWrapPtr> modulesMap;
   
   setModuleFilePriv("CEngine2D", "cengine2d.log", modulesMap);
   
   return modulesMap;
}

Logger &Logger::operator<<(const char *string)
{
   *m_streamInfo->stream << string;
   return *this;
}

Logger &Logger::operator<<(const std::string &string)
{
   *m_streamInfo->stream << string;
   return *this;
}

Logger &Logger::operator<<(const char chr)
{
   *m_streamInfo->stream << chr;
   return *this;
}

Logger &Logger::operator<<(const int val)
{
   *m_streamInfo->stream << val;
   return *this;
}

Logger &Logger::operator<<(const unsigned int val)
{
   *m_streamInfo->stream << val;
   return *this;
}

Logger &Logger::operator<<(const double val)
{
   *m_streamInfo->stream << val;
   return *this;
}

Logger &Logger::operator<<(const long long val)
{
   *m_streamInfo->stream << val;
   return *this;
}

Logger &Logger::operator<<(const long unsigned val)
{
   *m_streamInfo->stream << val;
   return *this;
}

Logger &Logger::operator<<(const void *val)
{
   *m_streamInfo->stream << val;
   return *this;
}
