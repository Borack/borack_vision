#include "mesh2d.hpp"

#include <QColor>

Mesh2d::Mesh2d(const MVC::Contour &contours)
   : m_contours(contours)
{
   init();
}

MVC::Mesh2d::Segments Mesh2d::segments() const
{
   return m_segments;
}

void Mesh2d::init()
{
   CDT cdt;

   std::vector<Vertex_handle> handles;
   handles.reserve(m_contours.size());

   for(int i = 0; i< m_contours.size(); i++)
   {
      cv::Point p = m_contours[i];

      handles.push_back(cdt.insert(Point(p.x,p.y)));
      if(i > 0)
      {
         cdt.insert_constraint(handles[i-1], handles[i]);
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
   CGAL::refine_Delaunay_mesh_2(cdt, Criteria(0.35, 50));
   std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;

//   CDT::All_vertices_iterator it;
//   m_segments.reserve(cdt.number_of_vertices());
//   for(it = cdt.all_vertices_begin(); it != cdt.all_vertices_end(); it++)
//   {
//      CDT::Vertex vertex(*it);
//      m_segments.push_back(QPointF(vertex.point().x(), vertex.point().y()));

//   }

   CDT::Finite_edges_iterator eIt;
   for(eIt = cdt.finite_edges_begin(); eIt != cdt.finite_edges_end(); eIt++)
   {
//      CDT::Vertex vertex(*it);
      CDT::Segment seg = cdt.segment(*eIt);
      m_segments.push_back(QLineF(seg.source().x(), seg.source().y(), seg.target().x(), seg.target().y()));
//      m_vertices.push_back(QPointF(vertex.point().x(), vertex.point().y()));

   }


}
