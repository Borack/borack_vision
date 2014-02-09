#include "mesh2d.hpp"

Mesh2d::Mesh2d(const MVC::Contour &contours)
   : m_contours(contours)
{
   init();
}

void Mesh2d::init()
{
   CDT cdt;

   Vertex_handle before;
   for(int i = 0; i< m_contours.size(); i++)
   {
      cv::Point p = m_contours[i];
      Vertex_handle current = cdt.insert(Point(p.x,p.y));
      if(i>0)
      {
         cdt.insert_constraint(before, current);
      }
      before = current;
   }

//   Vertex_handle va = cdt.insert(Point(-4,0));
//   Vertex_handle vb = cdt.insert(Point(0,-1));
//   Vertex_handle vc = cdt.insert(Point(4,0));
//   Vertex_handle vd = cdt.insert(Point(0,1));
//   cdt.insert(Point(2, 0.6));

//   cdt.insert_constraint(va, vb);
//   cdt.insert_constraint(vb, vc);
//   cdt.insert_constraint(vc, vd);
//   cdt.insert_constraint(vd, va);


   std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;
   std::cout << "Meshing the triangulation..." << std::endl;
   CGAL::refine_Delaunay_mesh_2(cdt, Criteria(/*0.125, 0.5*/));
   std::cout << "Number of vertices: " << cdt.number_of_vertices() << std::endl;
}
