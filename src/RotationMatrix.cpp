#include <iostream>
#include <cmath>
#include "RotationMatrix.hh"
#include "size.hh"



/*!
 * \brief Parametryczny konstruktor macierzy rotacji
 *
 *  Wypelnia cala macierz podana tablica
 */
RotationMatrix::RotationMatrix(const double tab[SIZE][SIZE])
{
  for(int i=0; i < SIZE; ++i)
    {
      for(int j=0; j<SIZE; ++j)
	{
	  value[i][j] = tab[i][j];
	}
    }
}

/*!
 * \brief Bezparametryczny konstruktor macierzy rotacji
 *
 *  Wypelnia cala macierz 0
 */
RotationMatrix::RotationMatrix()
{
  for(int i=0; i < SIZE; ++i)
    {
      for(int j=0; j<SIZE; ++j)
	{
	  value[i][j] = 0;
	}
    }
  for(int i=0; i < SIZE; ++i)
    {
      value[i][i] = 1;
    }
}

/*!
 * \brief Inicjuje macierz rotacji wokol osi x
 *
 * \param[in] theta - wartosc kata o jaki nalezy dokonac rotacji w radianach
 *
 * \return macierz rotacji
 */

RotationMatrix RotationMatrix::Rx(double theta)
{
  value[0][0] = 1;
  value[0][1] = 0;
  value[0][2] = 0;
  value[1][0] = 0;
  value[1][1] = cos(theta);
  value[1][2] = -sin(theta);
  value[2][0] = 0;
  value[2][1] = sin(theta);
  value[2][2] = cos(theta);

  return *this;
  }

/*!
 * \brief Inicjuje macierz rotacji wokol osi y
 *
 * \param[in] theta - wartosc kata o jaki nalezy dokonac rotacji w radianach
 *
 * \return macierz rotacji
 */

RotationMatrix RotationMatrix::Ry(double theta)
{
  value[0][0] = cos(theta);
  value[0][1] = 0;
  value[0][2] = sin(theta);
  value[1][0] = 0;
  value[1][1] = 1;
  value[1][2] = 0;
  value[2][0] = -sin(theta);
  value[2][1] = 0;
  value[2][2] = cos(theta);

    return *this;
}

/*!
 * \brief Inicjuje macierz rotacji wokol osi z
 *
 * \param[in] theta - wartosc kata o jaki nalezy dokonac rotacji w radianach
 *
 * \return macierz rotacji
 */

RotationMatrix RotationMatrix::Rz(double theta)
{
  value[0][0] = cos(theta);
  value[0][1] = -sin(theta);
  value[0][2] = 0;
  value[1][0] = sin(theta);
  value[1][1] = cos(theta);
  value[1][2] = 0;
  value[2][0] = 0;
  value[2][1] = 0;
  value[2][2] = 1;

  return *this;
}

