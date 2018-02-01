#include <map>
#include <fstream>
#include <memory>

#include "logging.h"

static std::map<std::string, std::ofstream *> getModulesFromSettings();

static std::ostream *setModuleFilePriv(const char *module,
                                       const char *filename,
                                       std::map<std::string, std::ofstream *> &);

static std::map<std::string, std::ofstream *> l_moduleFileMap = getModulesFromSettings();

Logger::Logger(const char *module)
   : m_module(module)
{
   auto mod_it = l_moduleFileMap.find(module);
   
   if(mod_it == l_moduleFileMap.end())
   {
      m_stream = &std::cout;
   }
   else
   {
      m_stream = mod_it->second;
   }
}

void Logger::setModuleFile(Logger *logger,
                           const char *module,
                           const char *filename)
{
   logger->m_stream = setModuleFilePriv(module, filename, l_moduleFileMap);
}

std::ostream &Logger::writer()
{
   return *m_stream;
}

std::ostream *setModuleFilePriv(const char *module,
                                const char *filename,
                                std::map<std::string, std::ofstream *> &modMap)
{
   auto mod_it = modMap.find(module);
   
   if(mod_it != modMap.end())
   {
      // close file and de-allocate the resource
      mod_it->second->close();
      delete mod_it->second;
      
      modMap.erase(mod_it);
   }
   
   std::unique_ptr<std::ofstream> filestream_ptr(new std::ofstream(filename, std::ofstream::out | std::ofstream::app));
   
   if(filestream_ptr->is_open())
   {
      modMap.insert(std::pair<std::string, std::ofstream *>(module, filestream_ptr.release()));
   }
   
   return &std::cout;
}

std::map<std::string, std::ofstream *> getModulesFromSettings()
{
   std::map<std::string, std::ofstream *> modulesMap;
   
   setModuleFilePriv("CEngine2D", "cengine2d.log", modulesMap);
   
   return modulesMap;
}
