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
#pragma once

#include <sofa/defaulttype/VecTypes.h>
#include <sofa/core/DataEngine.h>
#include <sofa/core/topology/BaseMeshTopology.h>

namespace cgal
{

template <class DataTypes>
class CylinderMesh : public sofa::core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(CylinderMesh,DataTypes),sofa::core::DataEngine);

    typedef typename DataTypes::Real Real;
    typedef typename DataTypes::Coord Point;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;
    typedef sofa::type::fixed_array<int, 3> Index;
    //    typedef sofa::type::vector<Real> VecReal;

//        typedef sofa::core::topology::BaseMeshTopology::PointID PointID;
    //    typedef sofa::core::topology::BaseMeshTopology::Edge Edge;
    //    typedef sofa::core::topology::BaseMeshTopology::Triangle Triangle;
    //    typedef sofa::core::topology::BaseMeshTopology::Quad Quad;
    typedef sofa::core::topology::BaseMeshTopology::Tetra Tetra;
    typedef sofa::core::topology::BaseMeshTopology::Hexa Hexa;


    //    typedef sofa::core::topology::BaseMeshTopology::SeqEdges SeqEdges;
    //    typedef sofa::core::topology::BaseMeshTopology::SeqTriangles SeqTriangles;
    //    typedef sofa::core::topology::BaseMeshTopology::SeqQuads SeqQuads;
    typedef sofa::core::topology::BaseMeshTopology::SeqTetrahedra SeqTetrahedra;
    typedef sofa::core::topology::BaseMeshTopology::SeqHexahedra SeqHexahedra;


public:
    CylinderMesh();
    virtual ~CylinderMesh() { };

    void init() override;
    void reinit() override;

    void doUpdate() override;
    void scale();
    void orientate();
    void draw(const sofa::core::visual::VisualParams*) override;

    //Inputs
    sofa::core::objectmodel::Data<double> m_diameter; ///< Diameter
    sofa::core::objectmodel::Data<double> m_length; ///< Length
    sofa::core::objectmodel::Data<int> m_number; ///< Number of intervals
    sofa::core::objectmodel::Data<bool> m_bScale; ///< Scale or not
    sofa::core::objectmodel::Data<bool> m_viewPoints; ///< Display Points
    sofa::core::objectmodel::Data<bool> m_viewTetras; ///< Display Tetrahedra

    //Outputs
    sofa::core::objectmodel::Data<VecCoord> m_points; ///< Points
    sofa::core::objectmodel::Data<SeqTetrahedra> m_tetras; ///< Tetrahedra

    //Parameters
    Real m_interval;
    int m_nbVertices, m_nbCenters, m_nbBDCenters;
    size_t m_nbTetras;
    int n, m, a;
    Real d, l, t;
    std::map<Index, int> m_ptID;


};

#if !defined(CGALPLUGIN_CYLINDERMESH_CPP)
extern template class SOFA_CGALPLUGIN_API CylinderMesh<sofa::defaulttype::Vec3Types>;
#endif

} //cgal
