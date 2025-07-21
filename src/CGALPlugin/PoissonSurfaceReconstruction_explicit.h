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


#ifdef CGALPLUGIN_POISSONSURFACERECONSTRUCTION_EXPLICIT_CPP
#define CGALPLUGIN_POISSONSURFACERECONSTRUCTION_EXPLICIT
#else
#define CGALPLUGIN_POISSONSURFACERECONSTRUCTION_EXPLICIT extern
#endif


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/poisson_surface_reconstruction.h>
#include <CGAL/property_map.h>

namespace cgal
{

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef std::pair<Point_3, Vector_3> Pwn;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron_3;
typedef Polyhedron_3::Vertex_handle Vertex_handle;
typedef Polyhedron_3::Halfedge_around_facet_circulator HF_circulator;

}

namespace CGAL
{
   CGALPLUGIN_POISSONSURFACERECONSTRUCTION_EXPLICIT template bool poisson_surface_reconstruction_delaunay<std::vector<cgal::Pwn>::iterator,
                                                        First_of_pair_property_map<cgal::Pwn>,
                                                        Second_of_pair_property_map<cgal::Pwn>,
                                                        cgal::Polyhedron_3,
                                                        Manifold_with_boundary_tag>
    (std::vector<cgal::Pwn>::iterator,
     std::vector<cgal::Pwn>::iterator,
     First_of_pair_property_map<cgal::Pwn> ,
     Second_of_pair_property_map<cgal::Pwn>,
     cgal::Polyhedron_3& ,
     double ,
     double  ,
     double ,
     double ,
     Manifold_with_boundary_tag);
}