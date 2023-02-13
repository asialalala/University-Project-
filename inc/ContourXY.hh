#ifndef CONTOUR_HH
#define CONTOUR_HH

#include "Vector.hh"
#include "Typy.hh"

/*!
 * \file
 * \brief Definiuje pojecie obrysu XY
 *
 */


/*!
 * \brief Modeluje pojecie obrysu XY
 */
class ContourXY
{
  
private:
  
  Vector2D  dl;  // Lewy dolny wierzcholek
  
  Vector2D  ur;  // Prawy gorny wierzcholek
  
public:
  
  /*!
   * \brief Konstruktor bezparametryczny
   */
  ContourXY(){dl[0]=dl[1]=ur[0]=ur[1]=0;}

 
  ContourXY(double DL_x, double DL_y, double UR_x, double UR_y);
 

  /*!
   * \brief Konstruktor kopiujacy
   */
  ContourXY(const ContourXY & n) {dl = n.dl; ur = n.ur;}

  /*!
   * \brief Destruktor
   */
  ~ContourXY() {};

  /*!
   * \brief Podglad ur
   *
   * \return ld
   */
  Vector2D DL()const {return dl;}

  /*!
   * \brief Podglad ur
   *
   * \return ur
   */
  Vector2D UR()const {return ur;}
  
  bool collide(const ContourXY & ac) const;

  void compare_change(const Vector3D coord);
};
#endif
