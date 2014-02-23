#ifndef MESH2D_HPP
#define MESH2D_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>

#include <vector>
#include <QPointF>

#include "mvc_types.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Delaunay_mesh_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, Tds> CDT;
typedef CGAL::Delaunay_mesh_size_criteria_2<CDT> Criteria;
typedef CGAL::Delaunay_mesher_2<CDT, Criteria> Meshing_engine;


typedef CDT::Vertex_handle Vertex_handle;
typedef CDT::Point Point;

class Mesh2d
{
public:

   Mesh2d(const MVC::Contour &contours);
   MVC::Mesh2d::Segments segments() const;

private:
   void init();

   const MVC::Contour &m_contours;
   MVC::Mesh2d::Segments m_segments;

};

#endif // MESH2D_HPP
