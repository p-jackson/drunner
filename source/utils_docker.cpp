
#include "logmsg.h"
#include "utils.h"
#include "utils_docker.h"

namespace utils_docker
{

   void pullImage(const params & p, const sh_drunnercfg & s, const std::string & image)
   {
      if (p.isDevelopmentMode())
      {
         logmsg(kLDEBUG, "In developer mode - not pulling " + image, p);
         return;
      }

      if (!s.getPullImages())
      {
         logmsg(kLDEBUG, "Pulling images disabled in global options.", p);
         return;
      }

      if (utils::imageisbranch(image))
      {
         logmsg(kLDEBUG, image+" is not on the master branch, so assuming dev environment and not pulling.", p);
         return;
      }

      logmsg(kLINFO, "Pulling Docker image " + image + ".\n This may take some time...", p);
      eResult rslt = utils::pullimage(image);

      switch (rslt) 
      {
      case kRError:
         logmsg(kLERROR, "Couldn't pull " + image, p);
         break;
      case kRNoChange:
         logmsg(kLDEBUG, "No change to Docker image (it's already up to date).", p);
         break;
      default:
         logmsg(kLINFO, "Successfully pulled " + image, p);
      }
   }


} // namespace