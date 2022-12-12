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

#define CGAL_MESH_3_VERBOSE 0


#include <sofa/core/DataEngine.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/defaulttype/VecTypes.h>

#include <CGAL/version.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>


namespace cgal
{

template <class DataTypes>
class MeshGenerationFromPolyhedron : public sofa::core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(MeshGenerationFromPolyhedron,DataTypes),sofa::core::DataEngine);

    typedef typename DataTypes::Real Real;
    typedef typename DataTypes::Coord Point;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;

    typedef sofa::core::topology::BaseMeshTopology::Triangle Triangle;
    typedef sofa::core::topology::BaseMeshTopology::Quad Quad;
    typedef sofa::core::topology::BaseMeshTopology::Tetra Tetra;

    typedef sofa::core::topology::BaseMeshTopology::SeqTriangles SeqTriangles;
    typedef sofa::core::topology::BaseMeshTopology::SeqQuads SeqQuads;
    typedef sofa::core::topology::BaseMeshTopology::SeqTetrahedra SeqTetrahedra;


public:
    MeshGenerationFromPolyhedron();
    virtual ~MeshGenerationFromPolyhedron() { }

    void init() override;
    void reinit() override;

    void doUpdate() override;

    void draw(const sofa::core::visual::VisualParams* vparams) override;
    
    //Inputs
    sofa::core::objectmodel::Data<VecCoord> f_X0; ///< Rest position coordinates of the degrees of freedom
    sofa::core::objectmodel::Data<SeqTriangles> f_triangles; ///< List of triangles
    sofa::core::objectmodel::Data<SeqQuads> f_quads; ///< List of quads (if no triangles) 

    //Outputs
    sofa::core::objectmodel::Data<VecCoord> f_newX0; ///< New Rest position coordinates from the tetrahedral generation
    sofa::core::objectmodel::Data<SeqTetrahedra> f_tetrahedra; ///< List of tetrahedra

    sofa::core::objectmodel::Data<bool> frozen; ///< true to prohibit recomputations of the mesh

    //Parameters
    sofa::core::objectmodel::Data<double> facetAngle; ///< Lower bound for the angle in degrees of the surface mesh facets
    sofa::core::objectmodel::Data<double> facetSize; ///< Uniform upper bound for the radius of the surface Delaunay balls
    sofa::core::objectmodel::Data<double> facetApproximation; ///< Upper bound for the center-center distances of the surface mesh facets
    sofa::core::objectmodel::Data<double> cellRatio; ///< Upper bound for the radius-edge ratio of the tetrahedra
    sofa::core::objectmodel::Data<double> cellSize; ///< Uniform upper bound for the circumradii of the tetrahedra in the mesh
#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
    sofa::core::objectmodel::Data<double> sharpEdgeAngle; ///< Threshold angle to detect sharp edges in input surface (activated with CGAL 3.8+ if sharpEdgeSize > 0)
    sofa::core::objectmodel::Data<double> sharpEdgeSize; ///< Meshing size for sharp feature edges (activated with CGAL 3.8+ if sharpEdgeSize > 0)
#endif
    sofa::core::objectmodel::Data<bool> odt; ///< activate odt optimization
    sofa::core::objectmodel::Data<bool> lloyd; ///< activate lloyd optimization
    sofa::core::objectmodel::Data<bool> perturb; ///< activate perturb optimization
    sofa::core::objectmodel::Data<bool> exude; ///< activate exude optimization
    sofa::core::objectmodel::Data<int> odt_max_it; ///< odt max iteration number
    sofa::core::objectmodel::Data<int> lloyd_max_it; ///< lloyd max iteration number
    sofa::core::objectmodel::Data<double> perturb_max_time; ///< perturb maxtime
    sofa::core::objectmodel::Data<double> exude_max_time; ///< exude max time
    sofa::core::objectmodel::Data<int> ordering; ///< output points and elements ordering (0 = none, 1 = longest bbox axis)
    sofa::core::objectmodel::Data<bool> constantMeshProcess; ///< deterministic choice of first point used in meshing process (true = constant output / false = variable output)
    sofa::core::objectmodel::Data<unsigned int> meshingSeed; ///< seed used when picking first point in meshing process

    // Display
    sofa::core::objectmodel::Data<bool> drawTetras; ///< display generated tetra mesh
    sofa::core::objectmodel::Data<bool> drawSurface; ///< display input surface mesh

    // A modifier creating a triangle with the incremental builder.
    template <class HDS>
    class AddTriangles : public CGAL::Modifier_base<HDS>
    {
    public:
        const VecCoord& points;
        const SeqTriangles& triangles;
        const SeqQuads& quads;

        AddTriangles(const VecCoord& points, const SeqTriangles& triangles, const SeqQuads& quads)
            : points(points), triangles(triangles), quads(quads) {}

        void operator()( HDS& hds)
        {
            typedef typename HDS::Vertex   Vertex;
            typedef typename Vertex::Point CPoint;
            // Postcondition: `hds' is a valid polyhedral surface.
            CGAL::Polyhedron_incremental_builder_3<HDS> polyhedronBuilder( hds, true);

            if (!triangles.empty() || !quads.empty())
            {
                //we assume that the point iterator gives point in ascendant order (0,.. n+1...)
                //std::map<int, Vertex_handle> s2cVertices;

                //polyhedronBuilder.begin_surface(points.size(), triangles.size()+quads.size());
                polyhedronBuilder.begin_surface(points.size(), triangles.size()+2*quads.size());

                for (typename VecCoord::const_iterator itVertex = points.begin() ; itVertex != points.end() ; ++itVertex)
                {
                    Point p = (*itVertex);
                    polyhedronBuilder.add_vertex( CPoint(p[0], p[1], p[2]));
                }

                for (SeqTriangles::const_iterator itTriangle = triangles.begin() ; itTriangle != triangles.end() ; ++itTriangle)
                {
                    Triangle t = (*itTriangle);

                    polyhedronBuilder.begin_facet();
                    polyhedronBuilder.add_vertex_to_facet( t[0]);
                    polyhedronBuilder.add_vertex_to_facet( t[1]);
                    polyhedronBuilder.add_vertex_to_facet( t[2]);
                    polyhedronBuilder.end_facet();

                }
                for (SeqQuads::const_iterator itQuad = quads.begin() ; itQuad != quads.end() ; ++itQuad)
                {
                    Quad t = (*itQuad);

                    polyhedronBuilder.begin_facet();
                    polyhedronBuilder.add_vertex_to_facet( t[0]);
                    polyhedronBuilder.add_vertex_to_facet( t[1]);
                    polyhedronBuilder.add_vertex_to_facet( t[2]);
                    // polyhedronBuilder.add_vertex_to_facet( t[3]);
                    polyhedronBuilder.end_facet();

                    polyhedronBuilder.begin_facet();
                    polyhedronBuilder.add_vertex_to_facet( t[0]);
                    polyhedronBuilder.add_vertex_to_facet( t[2]);
                    polyhedronBuilder.add_vertex_to_facet( t[3]);
                    polyhedronBuilder.end_facet();

                }
                if ( polyhedronBuilder.check_unconnected_vertices() )
                {
                    std::cout << "Remove unconnected vertices" << std::endl;
                    polyhedronBuilder.remove_unconnected_vertices();
                }

                polyhedronBuilder.end_surface();
            }
        }
    };

};

#if !defined(CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_CPP)
extern template class SOFA_CGALPLUGIN_API MeshGenerationFromPolyhedron<sofa::defaulttype::Vec3Types>;
#endif

} //cgal
