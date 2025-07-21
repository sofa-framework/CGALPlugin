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

#include <sofa/core/DataEngine.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/defaulttype/VecTypes.h>

#include <image/CImgData.h>

#include <CGALPlugin/MeshGenerationFromImage_explicit.h>


namespace cgal
{

using sofa::type::vector;
using cimg_library::CImg;

template <class DataTypes, class _ImageTypes>
class MeshGenerationFromImage : public sofa::core::DataEngine
{

public:
    typedef sofa::core::DataEngine Inherited;
    SOFA_CLASS(SOFA_TEMPLATE2(MeshGenerationFromImage,DataTypes,_ImageTypes),Inherited);

    typedef typename sofa::defaulttype::Vec3dTypes::Real Real;
    typedef typename sofa::defaulttype::Vec3dTypes::Coord Point;
    typedef typename sofa::defaulttype::Vec3dTypes::Coord Coord;
    typedef typename sofa::defaulttype::Vec3dTypes::VecCoord VecCoord;
    typedef sofa::type::Vec3 Vec3;

    typedef sofa::core::topology::BaseMeshTopology::Tetra Tetra;
    typedef sofa::core::topology::BaseMeshTopology::SeqTetrahedra SeqTetrahedra;



    // image data
    typedef _ImageTypes ImageTypes;
    typedef typename ImageTypes::T T;
    typedef typename ImageTypes::imCoord imCoord;
    typedef sofa::helper::WriteAccessor<sofa::core::objectmodel::Data< ImageTypes > > waImage;
    typedef sofa::helper::ReadAccessor<sofa::core::objectmodel::Data< ImageTypes > > raImage;

    // transform data
    typedef SReal t_Real;
    typedef sofa::defaulttype::ImageLPTransform<t_Real> TransformType;
    typedef sofa::helper::WriteAccessor<sofa::core::objectmodel::Data< TransformType > > waTransform;
    typedef sofa::helper::ReadAccessor<sofa::core::objectmodel::Data< TransformType > > raTransform;


    typedef std::vector<Point3> Polyline;
    typedef std::list<Polyline> Polylines;

public:
    MeshGenerationFromImage();
    virtual ~MeshGenerationFromImage() { }

    void init() override;
    void reinit() override;

    void doUpdate() override;

    void draw(const sofa::core::visual::VisualParams* vparams) override;

    //Inputs    
    sofa::core::objectmodel::DataFileName d_filename; ///< Image file
    sofa::core::objectmodel::Data< ImageTypes > d_image; ///< image input
    sofa::core::objectmodel::Data< TransformType > d_transform; ///< 12-param vector for trans, rot, scale, ...
    sofa::core::objectmodel::Data<VecCoord> d_features; ///< features (1D) that will be preserved in the mesh

    //Outputs
    sofa::core::objectmodel::Data<VecCoord> d_newX0; ///< New Rest position coordinates from the tetrahedral generation
    sofa::core::objectmodel::Data<SeqTetrahedra> d_tetrahedra; ///< List of tetrahedra
    sofa::core::objectmodel::Data<sofa::type::vector<int> > d_tetraDomain; ///< domain of each tetrahedron
    sofa::core::objectmodel::Data<sofa::type::vector<double> > d_outputCellData; ///< Output cell data
    sofa::core::objectmodel::Data<bool> d_frozen; ///< true to prohibit recomputations of the mesh

    //Parameters
    sofa::core::objectmodel::Data<double> d_edgeSize; ///< Edge size criterium (needed for polyline features
    sofa::core::objectmodel::Data<double> d_facetAngle; ///< Lower bound for the angle in degrees of the surface mesh facets
    sofa::core::objectmodel::Data<double> d_facetSize; ///< Uniform upper bound for the radius of the surface Delaunay balls
    sofa::core::objectmodel::Data<double> d_facetApproximation; ///< Upper bound for the center-center distances of the surface mesh facets
    sofa::core::objectmodel::Data<double> d_cellRatio; ///< Upper bound for the radius-edge ratio of the tetrahedra
    sofa::core::objectmodel::Data<double> d_cellSize; ///< Uniform upper bound for the circumradii of the tetrahedra in the mesh
    sofa::core::objectmodel::Data< sofa::type::vector<int> > d_label; ///< label to be resized to a specific cellSize
    sofa::core::objectmodel::Data< sofa::type::vector<double> > d_labelCellSize; ///< Uniform upper bound for the circumradii of the tetrahedra in the mesh by label
    sofa::core::objectmodel::Data< sofa::type::vector<double> > d_labelCellData; ///< 1D cell data by label
    sofa::core::objectmodel::Data<bool> d_odt; ///< activate odt optimization
    sofa::core::objectmodel::Data<bool> d_lloyd; ///< activate lloyd optimization
    sofa::core::objectmodel::Data<bool> d_perturb; ///< activate perturb optimization
    sofa::core::objectmodel::Data<bool> d_exude; ///< activate exude optimization
    sofa::core::objectmodel::Data<int> d_odtMaxIt; ///< odt max iteration number
    sofa::core::objectmodel::Data<int> d_lloydMaxIt; ///< lloyd max iteration number
    sofa::core::objectmodel::Data<double> d_perturbMaxTime; ///< perturb maxtime
    sofa::core::objectmodel::Data<double> d_exudeMaxTime; ///< exude max time
    sofa::core::objectmodel::Data<int> d_ordering; ///< Output points and elements ordering (0 = none, 1 = longest bbox axis)

    // Display
    sofa::core::objectmodel::Data<bool> d_drawTetras; ///< display generated tetra mesh

    sofa::type::vector<int> m_tetraDomainLabels;

};

#if  !defined(CGALPLUGIN_MESHGENERATIONFROMIMAGE_CPP)
extern template class SOFA_CGALPLUGIN_API MeshGenerationFromImage<sofa::defaulttype::Vec3Types, sofa::defaulttype::ImageUC>;
#endif

} //cgal
