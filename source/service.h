#ifndef __SERVICECLASS_H
#define __SERVICECLASS_H

#include "params.h"
#include "sh_drunnercfg.h"
#include "cresult.h"

class drunnerCompose;

cResult service_restore(const params & prms, const sh_drunnercfg & settings, const std::string & servicename, const std::string & backupfile);
void validateImage(const params & prms, const sh_drunnercfg & settings, std::string imagename);



class servicepaths
{
public:
   servicepaths(const sh_drunnercfg & settings, const std::string & servicename);

   std::string getPath() const;
   std::string getPathdRunner() const;
   std::string getPathTemp() const;
   std::string getPathHostVolume() const;
   std::string getPathHostVolume_servicerunner() const;
   std::string getPathHostVolume_environment() const;
   std::string getPathServiceRunner() const;
   std::string getPathDockerCompose() const;
   std::string getName() const;

protected:
   const std::string mName;
   const sh_drunnercfg & mSettings;
};

class cServiceEnvironment : protected settingsbash
{
   public:
      cServiceEnvironment(const servicepaths & paths);
      void save_environment(std::string key, std::string value);
      int getNumVars() const;
      void getVar(const int position, std::string & key, std::string & value) const;

protected:
   std::string mPath;
};


// class to manage the dService.
class service : public servicepaths
{
public:
   // will load imagename from variables.sh unless overridden with parameter.
   service(const params & prms, const sh_drunnercfg & settings, const std::string & servicename, std::string imagename = "" );

   bool isValid() const;

   cResult servicecmd();

   eResult uninstall();
   eResult obliterate();
   eResult recover();
   int status();
   void update();
   void install();
   void recreate(bool updating);
   void backup(const std::string & backupfile);
   void enter(); // uses execl, so never returns.

   const std::string getImageName() const;
   const params & getParams() const;

   cResult serviceRunnerCommand(const std::vector<std::string> & args) const;
   cServiceEnvironment & getEnvironment();
   const cServiceEnvironment & getEnvironmentConst() const;

private:
   void ensureDirectoriesExist() const;
   void createVolumes(const drunnerCompose * const drc);
   void createLaunchScript();
   std::string getUserID(std::string imagename) const;
   void logmsg(eLogLevel level, std::string s) const;

   static std::string loadImageName(const params & prms, const sh_drunnercfg & settings, const std::string & servicename, std::string imagename);

   const std::string mImageName;
   const params & mParams;
   cServiceEnvironment mEnvironment;
};



#endif

