#include <iostream>
#include "Vector.hh"
#include "Typy.hh"
#include "ContourXY.hh"


 /*!
   * \brief Konstruktor parametryczny
   *
   * Inicjalizuje kalse ContourXY, gdy wartosci lewego dolnego wierzcholka 
   * sa wieksze od wierzcholka prawego lewego, program wyrzuci blad.
   *
   */

ContourXY::ContourXY(double DL_x, double DL_y, double UR_x, double UR_y)
 {
   if(DL_x >= UR_x || DL_y >= UR_y)
     std::runtime_error("To nie sa dobrze podane wartosci wierzcholkow obszaruXY.\n");
   dl[0]=DL_x; dl[1]=DL_y; ur[0]=UR_x; ur[1]=UR_y;
 }

/*!
 * \brief Sprawdzenei czy nastapi pokrycie sie obszarow XY
 *
 * \param[in] ac - another coords, wierzcholki obrysu do porownania
 *
 * \return false, gdy obszary sie nie pokrywaja
 * \return true, gdy obszary sie pokrywaja
 *
 */
bool ContourXY::collide(const ContourXY & ac) const
{
  if(((dl[0] >= ac.dl[0]) && (dl[0]<=ac.ur[0])) &&
     ((dl[1] >= ac.dl[1]) && (dl[1]<=ac.ur[1])))
    {return true;}
  if(((ur[0] >= ac.dl[0]) && (ur[0]<=ac.ur[0])) &&
     ((ur[1] >= ac.dl[1]) && (ur[1]<=ac.ur[1])))
    {return true;}
  return false;
}


/*!
 * \brief Funkcja inicjalizuje 
 *
 * Funkcja porownuje ze soba wieszcholki, jesli noweo podany wierzcholej
 * jest bardziej wysuniety na prawo do gory przypisuje go ur, 
 * jesli jest wysuniety bardziej na dol na lewo niz poprzedni przypisuje
 * go do ld
 *
 */
void ContourXY::compare_change(const Vector3D coord)
  {
    std::cout << "TUTAJ WIERZCHOLEK " << coord << std::endl;
	  
    if(coord[0] > ur[0] && coord[1] > ur[1])
      {
      ur[0] = coord[0];
      ur[1] = coord[1];
      }
    if(coord[0] < dl[0] && coord[1] < dl[1])
      {
	dl[0] = coord[0];
	dl[1] = coord[1];
      }
  }
