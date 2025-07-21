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


#ifdef CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT_CPP
#define CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT
#else
#define CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT extern
#endif

#include <image/CImgData.h>

#include <CGAL/version.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(4,13,0)
#include <CGAL/Labeled_mesh_domain_3.h>
#else
#include <CGAL/Labeled_image_mesh_domain_3.h>
#endif

#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_domain_with_polyline_features_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/refine_mesh_3.h>
#include <CGAL/Image_3.h>
#include <CGAL/Weighted_point_3.h>


namespace cgal
{
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef typename cgal::K::Point_3 Point3;
typedef std::vector<Point3> Polyline;
typedef std::list<Polyline> Polylines;

}

namespace CGAL {
// Domain
// (we use exact intersection computation with Robust_intersection_traits_3)
#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(4, 13, 0)
CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class Mesh_domain_with_polyline_features_3<Labeled_mesh_domain_3<typename cgal::K>>;
#else
CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class Mesh_domain_with_polyline_features_3<Labeled_image_mesh_domain_3<Image_3, K>>;
#endif

}

namespace cgal
{
#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(4, 13, 0)
typedef CGAL::Mesh_domain_with_polyline_features_3<CGAL::Labeled_mesh_domain_3<typename cgal::K>> Mesh_domain;
#else
typedef CGAL::Mesh_domain_with_polyline_features_3<CGAL::Labeled_image_mesh_domain_3<CGAL::Image_3, K>> Mesh_domain;
#endif
}

namespace CGAL
{
// Triangulation
CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class Mesh_triangulation_3<typename cgal::Mesh_domain>;
//This is not compiling because it seems like there is a real issue in the API where a zero-argument constructor is missing. Yet, without explicit instantiation, the code is actually working....
//CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class CGAL::Mesh_complex_3_in_triangulation_3<CGAL::Mesh_triangulation_3<typename cgal::Mesh_domain>::type, typename cgal::Mesh_domain::Corner_index, typename cgal::Mesh_domain::Curve_segment_index>;
CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class Mesh_criteria_3<Mesh_triangulation_3<typename cgal::Mesh_domain>::type>;
CGALPLUGIN_MESHGENERATIONFROMIMAGE_EXPLICIT template class Mesh_constant_domain_field_3<cgal::Mesh_domain::R, cgal::Mesh_domain::Index>;
}

namespace cgal
{
// Triangulation
typedef typename CGAL::Mesh_triangulation_3<Mesh_domain>::type Tr;
typedef typename CGAL::Mesh_complex_3_in_triangulation_3<CGAL::Mesh_triangulation_3<Mesh_domain>::type, Mesh_domain::Corner_index, Mesh_domain::Curve_segment_index> C3t3;

// Mesh Criteria
typedef typename CGAL::Mesh_criteria_3<CGAL::Mesh_triangulation_3<Mesh_domain>::type> Mesh_criteria;
typedef typename Mesh_criteria::Facet_criteria Facet_criteria;
typedef typename Mesh_criteria::Cell_criteria Cell_criteria;

typedef typename C3t3::Facet_iterator Facet_iterator;
typedef typename C3t3::Cell_iterator Cell_iterator;

typedef typename Tr::Finite_vertices_iterator Finite_vertices_iterator;
typedef typename Tr::Vertex_handle Vertex_handle;
typedef typename Tr::Point Point_3;
typedef CGAL::Mesh_constant_domain_field_3<Mesh_domain::R, Mesh_domain::Index> Sizing_field;

#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,5,0)
using namespace CGAL::parameters;
#endif


}