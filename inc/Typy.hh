#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "vector.hh"
#include "matrix.hh"
/*!
 * \brief Definiuje typy
 *
 * Definiuje instancje nazwy szablonu wektora Vector 
 * z typem TYPE double i SIZE rozmiarem 3
 * oraz instancje szablonu macierzy matrix
 * z typem TYPE doble i SIZE rozmiarem 3
 *
 */

typedef Vector<double,3> Vector3D;
typedef Matrix<double,3> Matrix3D;
typedef Vector<double,2> Vector2D;

#endif
