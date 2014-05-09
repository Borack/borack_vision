#ifndef MODES_HPP
#define MODES_HPP

enum EGraphCut_DataTerm // = Objective
{
    EGraphCut_DataTerm_Minimum_Lumincance = 0
  , EGraphCut_DataTerm_Maximum_Lumincance
  , EGraphCut_DataTerm_Hard_Constraint
};

enum EGraphCut_SmoothnessTerm // = Seam
{
     EGraphCut_SmoothnessTerm_Color= 0
   , EGraphCut_SmoothnessTerm_Gradients
};


#endif // MODES_HPP
