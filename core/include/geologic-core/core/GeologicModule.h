/**
 * \file	GeologicModule.h
 */

#ifndef GeologicModule_H
#define GeologicModule_H

//#include "geologic-core/core/geologic-core_global.h"
#include "geologic-core/superClasses/Module.h"
#include "geologic-core/core/geologic-launcher/GeologicLauncher.h"
#include "geologic-core/roles/RoleGeo.h"
#include "geologic-core/roles/RoleDynamics.h"
#include <string>
#include <vector>

//GEOLOGICCORESHARED_EXPORT
class  GeologicModule : public Module {

    public:
        //*/ -------------------------------------------------
        static GeologicModule* getInstance();
		GeologicLauncher* getLauncher();
		virtual std::vector<std::string> getSubscribedRoles();

    private:
        //*/ -------------------------------------------------
        GeologicModule();

        //*/ -------------------------------------------------
        GeologicModule(GeologicModule const&) = delete;
        void operator = (GeologicModule const&) = delete;

        //*/ -------------------------------------------------
        static GeologicModule* instance;
        GeologicLauncher* launcher;
};

#endif // GeologicModule_H
