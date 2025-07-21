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


#ifdef CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT_CPP
#define CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT
#else
#define CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT extern
#endif

#define CGAL_MESH_3_VERBOSE 0

#include <CGAL/version.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>


#if CGAL_VERSION_NR <= CGAL_VERSION_NUMBER(4,9,1)
#include <CGAL/AABB_intersections.h>
#endif
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_3/Robust_intersection_traits_3.h>

#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#include <CGAL/Polyhedral_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/refine_mesh_3.h>
#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#endif

// IO
#include <CGAL/IO/Polyhedron_iostream.h>

#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,5,0)
using namespace CGAL::parameters;
#endif

namespace cgal
{
  typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
}

namespace CGAL
{

#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class Mesh_3::Robust_intersection_traits_3<cgal::K>;
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class Mesh_polyhedron_3<Mesh_3::Robust_intersection_traits_3<cgal::K>> ;
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class Polyhedral_mesh_domain_with_features_3<Mesh_3::Robust_intersection_traits_3<cgal::K>, typename Mesh_polyhedron_3<Mesh_3::Robust_intersection_traits_3<cgal::K>>::type>;
#else
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT Mesh_3::Robust_intersection_traits_3<cgal::K>;
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT Polyhedron_3<Mesh_3::Robust_intersection_traits_3<cgal::K>>;
  CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT Polyhedral_mesh_domain_3<Polyhedron_3<Mesh_3::Robust_intersection_traits_3<cgal::K>>, Mesh_3::Robust_intersection_traits_3<cgal::K>>;
#endif
}

namespace cgal
{
  #if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
  typedef typename CGAL::Mesh_3::Robust_intersection_traits_3<K> Geom_traits;
  typedef typename CGAL::Mesh_polyhedron_3<Geom_traits>::type Polyhedron;
  typedef typename Polyhedron::HalfedgeDS HalfedgeDS;
  typedef typename CGAL::Polyhedral_mesh_domain_with_features_3<Geom_traits, Polyhedron> Mesh_domain;
  #else
  typedef typename CGAL::Mesh_3::Robust_intersection_traits_3<K> Geom_traits;
  typedef typename CGAL::Polyhedron_3<Geom_traits> Polyhedron;
  typedef typename Polyhedron::HalfedgeDS HalfedgeDS;
  typedef typename CGAL::Polyhedral_mesh_domain_3<Polyhedron, Geom_traits> Mesh_domain;
  #endif

}

namespace CGAL
{

CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class Polyhedron_incremental_builder_3<cgal::Polyhedron::HalfedgeDS>;


  // Triangulation
CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class CGAL::Mesh_triangulation_3<cgal::Mesh_domain>;
//#if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
//CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class CGAL::Mesh_complex_3_in_triangulation_3<CGAL::Mesh_triangulation_3<cgal::Mesh_domain>::type, cgal::Mesh_domain::Corner_index, cgal::Mesh_domain::Curve_segment_index>;
//#else
//CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT CGAL::Mesh_complex_3_in_triangulation_3<CGAL::Mesh_triangulation_3<cgal::Mesh_domain>::type> C3t3;
//#endif

  // Mesh Criteria
CGALPLUGIN_MESHGENERATIONFROMPOLYHEDRON_EXPLICIT template class CGAL::Mesh_criteria_3<CGAL::Mesh_triangulation_3<cgal::Mesh_domain>::type>;

}

namespace cgal
{
  // Triangulation
  typedef typename CGAL::Mesh_triangulation_3<Mesh_domain>::type Tr;
  #if CGAL_VERSION_NR >= CGAL_VERSION_NUMBER(3,8,0)
  typedef typename CGAL::Mesh_complex_3_in_triangulation_3<Tr, Mesh_domain::Corner_index, Mesh_domain::Curve_segment_index> C3t3;
  #else
  typedef typename CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
  #endif

  // Mesh Criteria
  typedef typename CGAL::Mesh_criteria_3<Tr> Mesh_criteria;

  typedef typename C3t3::Cell_iterator Cell_iterator;

  typedef typename Tr::Finite_vertices_iterator Finite_vertices_iterator;
  typedef typename Tr::Vertex_handle Vertex_handle;
  typedef typename Tr::Point Point_3;

}
