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

#include <sofa/testing/BaseSimulationTest.h>
#include <CGALPlugin/Refine2DMesh.h>

#include <sofa/simulation/common/SceneLoaderXML.h>

namespace cgal
{
using sofa::simulation::Node;
using sofa::simulation::SceneLoaderXML;

struct Refine2DMesh_test : public sofa::testing::BaseSimulationTest
{    

    Node::SPtr createSimpleScene()
    {
        std::string vtkLoader = "<MeshVTKLoader name='meshLoader' filename='" + std::string(SOFACGAL_TEST_RESOURCES_DIR) + "mesh/edges.vtk' />";

        std::string sceneStart =
            "<?xml version='1.0'?>"
            "<Node name='root' dt='0.01' gravity='0 -1 0'>"
            "    <RequiredPlugin name='Sofa.Component.IO.Mesh'/>"
            "    <RequiredPlugin name='CGALPlugin'/>";

        std::string sceneEnd =
            "    <Refine2DMesh template='Vec3' name='cgalTool' inputPoints='@meshLoader.position' inputEdges='@meshLoader.edges' "
            "        useInteriorPoints='false' seedPoints='200 50 0' regionPoints='50 50 0' shapeCriteria='0.125' "
            "        sizeCriteria='10' viewSeedPoints='1' viewRegionPoints='1' />"
            "</Node>";

        std::string scene = sceneStart + vtkLoader + sceneEnd;

        Node::SPtr root = SceneLoaderXML::loadFromMemory("test", scene.c_str());

        sofa::simulation::getSimulation()->init(root.get());

        return root;
    }


    void checkCreation()
    {
        EXPECT_MSG_NOEMIT(Error);

        // Check creation
        Node::SPtr root = createSimpleScene();
        ASSERT_NE(root.get(), nullptr);
    }

    void checkValues()
    {
        Node::SPtr root = createSimpleScene();
        ASSERT_NE(root.get(), nullptr);

        // Search for Refine2DMesh
        Refine2DMesh<sofa::defaulttype::Vec3Types>* mesh = nullptr;
        root->getTreeObject(mesh);
        ASSERT_NE(mesh, nullptr);
        
        ASSERT_EQ(mesh->d_newPoints.getValue().size(), 759);
        ASSERT_EQ(mesh->d_newEdges.getValue().size(), 101);
        ASSERT_EQ(mesh->d_newTriangles.getValue().size(), 1415);
    }
};

TEST_F(Refine2DMesh_test, CheckCreation) {
    ASSERT_NO_THROW(this->checkCreation());
}

TEST_F(Refine2DMesh_test, CheckValues) {
    ASSERT_NO_THROW(this->checkValues());
}

}