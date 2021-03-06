#ifndef __UTILS_DOCKER_H
#define __UTILS_DOCKER_H

#include <string>
#include "params.h"
#include "sh_drunnercfg.h"

namespace utils_docker
{
   void pullImage(const params & p, const sh_drunnercfg & s, const std::string & image);
}

#endif
