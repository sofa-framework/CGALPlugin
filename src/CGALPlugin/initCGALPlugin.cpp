/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <CGALPlugin/config.h>
#include <CGALPlugin/MeshGenerationFromPolyhedron.h>

#include <sofa/core/ObjectFactory.h>
#include <sofa/helper/system/PluginManager.h>


namespace cgal
{
    extern void registerCylinderMesh(sofa::core::ObjectFactory* factory);
    extern void registerFrontSurfaceReconstruction(sofa::core::ObjectFactory* factory);
    extern void registerPoissonSurfaceReconstruction(sofa::core::ObjectFactory* factory);
    extern void registerUpsamplePointCloud(sofa::core::ObjectFactory* factory);
    extern void registerBooleanOperations(sofa::core::ObjectFactory* factory);
}

extern void registerMeshGenerationFromPolyhedron(sofa::core::ObjectFactory* factory);

#ifdef SOFA_CGAL_WITH_IMAGE
extern void registerMeshGenerationFromImage(sofa::core::ObjectFactory* factory);
#endif
extern void registerDecimateMesh(sofa::core::ObjectFactory* factory);
extern void registerTriangularConvexHull3D(sofa::core::ObjectFactory* factory);
extern void registerRefine2DMesh(sofa::core::ObjectFactory* factory);


namespace sofa::component
{

//Here are just several convenient functions to help users know what the plugin contains 

extern "C" {
    SOFA_CGALPLUGIN_API void initExternalModule();
    SOFA_CGALPLUGIN_API const char* getModuleName();
    SOFA_CGALPLUGIN_API const char* getModuleVersion();
    SOFA_CGALPLUGIN_API const char* getModuleLicense();
    SOFA_CGALPLUGIN_API const char* getModuleDescription();
    SOFA_CGALPLUGIN_API void registerObjects(sofa::core::ObjectFactory* factory);
}

void initExternalModule()
{
    static bool first = true;
    if (first)
    {
        // make sure that this plugin is registered into the PluginManager
        sofa::helper::system::PluginManager::getInstance().registerPlugin(cgal::MODULE_NAME);

        first = false;
    }
}

const char* getModuleName()
{
    return cgal::MODULE_NAME;
}

const char* getModuleVersion()
{
    return cgal::MODULE_VERSION;
}

const char* getModuleLicense()
{
    return "GPL";
}


const char* getModuleDescription()
{
    return "Use CGAL functionnalities into SOFA";
}

void registerObjects(sofa::core::ObjectFactory* factory)
{
    cgal::registerCylinderMesh(factory);
    cgal::registerFrontSurfaceReconstruction(factory);
    cgal::registerPoissonSurfaceReconstruction(factory);
    cgal::registerUpsamplePointCloud(factory);
    cgal::registerBooleanOperations(factory);
    registerMeshGenerationFromPolyhedron( factory);
#ifdef SOFA_CGAL_WITH_IMAGE
    registerMeshGenerationFromImage( factory);
#endif
    registerDecimateMesh( factory);
    registerTriangularConvexHull3D( factory);
    registerRefine2DMesh( factory);
}

} // namespace sofa::component
