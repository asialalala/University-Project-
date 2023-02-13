#ifndef ROTATIONMATRIX_HH
#define ROTATIONMATRIX_HH
#include <iostream>
#include "matrix.hh"
#include "size.hh"
#include "Typy.hh"

/*!
 * \file
 * \brief Definicja klasy Macierzy obrotu 3x3
 *
 * Plik zawiera definicje struktury RotationMatrix oraz zapowiedzi
 * zapowiedzi metod wypelniajacych te macierz.
 * Macierz jest wypelniana odpowiednio dla rotacji wokol osi x, y lub z
 * o kat theta
 *
 */

/*!
 * \brief Modeluje pojecie macierzy rotacji
 */

class RotationMatrix : public Matrix3D {
private:
  // Matrix3D matrix; //macierz rotacji
public:
  RotationMatrix();
  RotationMatrix(const double tab[SIZE][SIZE]);
  RotationMatrix Rx(double theta); // rotacja wokol osi x
  RotationMatrix Ry(double theta); // rotacja wokol osi y
  RotationMatrix Rz(double theta); // rotacja wokol osi z
  
};


#endif
