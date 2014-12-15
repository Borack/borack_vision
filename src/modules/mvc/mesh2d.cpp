#include "mesh2d.hpp"

#include <QColor>

Mesh2d::Mesh2d(const MVC::Contour &contours)
   : m_contours(contours)
{
   init();
}

//-----------------------------------------------------------------------------

MVC::Mesh2d::Segments Mesh2d::segments() const
{
   return m_segments;
}

//-----------------------------------------------------------------------------

void Mesh2d::init()
{
   CDT cdt;

   std::vector<Vertex_handle> handles;
   handles.reserve(m_contours.size());


   bool isFirst = true;
   for(const auto &point: m_contours)
   {
      handles.push_back(cdt.insert(Point(point.x,point.y)));
      if(!isFirst)
      {
         cdt.insert_constraint(handles.back()--, handles.back());
      }
      else
      {
         isFirst = false;
      }
   }
   cdt.insert_constraint(handles[0], handles[m_contours.size()-1]);


   int count = 0;
   for (CDT::Finite_edges_iterator eit = cdt.finite_edges_begin();
        eit != cdt.finite_edges_end();
        ++eit)
   {
     if (cdt.is_constrained(*eit))
     {
        ++count;
     }
   }


   std::cout << "The number of resulting constrained edges is  ";
   std::cout <<  count << std::endl;


   std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;
   std::cout << "Meshing the triangulation..." << std::endl;
   CGAL::refine_Delaunay_mesh_2(cdt, Criteria(0.15, 150));
//   CGAL::refine_Delaunay_mesh_2(cdt, Criteria(0.15, 50));
//   CGAL::refine_Delaunay_mesh_2(cdt, Criteria(0.15, 50));
   std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;

   CDT::Finite_edges_iterator eIt;
   for(eIt = cdt.finite_edges_begin(); eIt != cdt.finite_edges_end(); eIt++)
   {
      CDT::Segment seg = cdt.segment(*eIt);
      m_segments.push_back(QLineF(seg.source().x(), seg.source().y(), seg.target().x(), seg.target().y()));
   }
}

//-----------------------------------------------------------------------------
