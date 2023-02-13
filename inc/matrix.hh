#pragma once

#include "vector.hh"
#include "min.hh"
#include <cmath>
#include <iostream>
#include <cstdlib>

/*!
 * \file
 * \brief Definicja szablonu klasy Matrix
 * 
 * zawiera metody umozliwiajace odwolanie sie do poszczegolnych 
 * elementow macierzy lub ich zamiane oraz metody umozliwiajace
 * dokonania operacji mnozenia przez wektori dodawania macierzy
 */

/*!
 * \brief Modeluje pojecie macierzy
 */

template<typename TYPE, int SIZE>
class Matrix {

protected:
  Vector<TYPE,SIZE> value[SIZE];               // Wartosci macierzy
  
  int changes;
  
public:
  Matrix(TYPE[SIZE][SIZE]);            // Konstruktor klasy
  Matrix();                               // Konstruktor klasy
  
  Vector<TYPE,SIZE> operator * (const Vector<TYPE,SIZE> &tmp)const;           // Operator mnożenia przez wektor
  
  Matrix<TYPE,SIZE> operator + (const Matrix<TYPE,SIZE> &tmp)const;
  
  TYPE  &operator () (int row, int column);
  
  const TYPE &operator () (int row, int column) const;
  
  Matrix<TYPE,SIZE> &diagonalisation(); // zmienia na trojkatna

  bool find_and_change(int column);  // zamienia kolumny

  Matrix<TYPE,SIZE> reset(int column); //zmienia na trojkatna

  Matrix<TYPE,SIZE> transposition(); // moze zmieniac

  Matrix<TYPE,SIZE> column_change(int column, const Vector<TYPE,SIZE> &vector); //moze zmieniac

  TYPE Gauss(int column, Vector<TYPE,SIZE> vector) const;

  TYPE Gauss() const;

  TYPE Frobenius()const;
};
template<typename TYPE, int SIZE>
std::istream &operator>>(std::istream &in, Matrix<TYPE,SIZE> &mat);
template<typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &out, Matrix<TYPE,SIZE> const &mat);

/*!
 * \brief Konstruktor klasy Matrix.    
 *
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE>::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}


/*!
 *  \brief Konstruktor parametryczny klasy Matrix.            
 *
 *  \param[in] tmp -  tablica o wymiarach SIZE z elementami typu double.  
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE>::Matrix(TYPE tmp[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
	  (value[i])[j] = tmp[i][j];
        }
    }
}


/*!
 * \brief Realizuje mnozenie macierzy przez wektor.
 *
 * \param[in]     tmp - wektor, czyli drugi skladnik mnozenia. 
 *
 * \return     Iloczyn dwoch skladnikow przekazanych jako wektor.       
 */
template<typename TYPE, int SIZE>
Vector<TYPE,SIZE> Matrix<TYPE,SIZE>::operator * (const Vector<TYPE,SIZE> &tmp)const {
    Vector<TYPE,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}


/*!
 *  \brief Funktor macierzy                                                     
 *
 *  \param[in]    row - numer wiersza.                                              
 *  \param[in]    column - numer kolumny.                                           
 *
 *  \return    Wartosc macierzy w danym miejscu tablicy.                        
 */
template<typename TYPE, int SIZE>
TYPE &Matrix<TYPE,SIZE>::operator()( int row, int column) {

    if (row < 0 ||  row  >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
     if (column < 0 || column >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
    return (value[row])[column];
}


/*!
 *  \brief Funktor macierzy                                                   
 *
 *  \param[in]    row - numer wiersza.                                          
 *  \param[in]    column - numer kolumny.                                    
 *
 *  \return    Wartosc macierzy w danym miejscu tablicy jako stala.     
 */
template<typename TYPE, int SIZE>
const TYPE &Matrix<TYPE,SIZE>::operator () (int row, int column) const {
  
  if (row < 0 ||  row  >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
     if (column < 0 || column >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
    return (value[row])[column];
}

/*!
 * \brief  Przeciążenie dodawania macierzy                                     
 *
 * \param[in]     tmp - wektor, czyli drugi skladnik dodawania.                
 *
 * \return     Macierz - iloczyn dwóch podanych macierzy.                   
 */
  template<typename TYPE, int SIZE>
  Matrix<TYPE,SIZE> Matrix<TYPE,SIZE>::operator + (const Matrix &tmp)const {
    Matrix<TYPE,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {                   //unsigned aby mozna bylo uzyc tych zmiennych
      for (int j = 0; j < SIZE; ++j) {                 //jako indeksow tablicy
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/*!
 *  \brief Przeciazenie operatora >>                                            
 *
 *  \param[in]    in - strumien wyjsciowy,                                          
 *  \param[in]   mat - macierz.     
 *
 *  \return strumien wejscia                                               
 */
template<typename TYPE, int SIZE>
std::istream &operator>>(std::istream &in, Matrix<TYPE,SIZE> &mat) {
  for (int i = 0; i < SIZE; ++i) {                   //unsigned, zby mozna bylo uzyc tych zmiennych
    for (int j = 0; j < SIZE; ++j) {                 //jako indeksow tablicy
            in >> mat(i, j);
        }
    }
    return in;
}


/*!
 * \brief Przeciazenie operatora <<                                    
 *
 * \param[in]    out - strumien wejsciowy,                                      
 * \param[in]     mat - macierz.   
 *
 * \return strumien wyjscia                                               
 */
template<typename TYPE, int SIZE>
std::ostream &operator<<(std::ostream &out, const Matrix<TYPE,SIZE> &mat) {   //unsigned, aby mozna bylo uzyc tych zmiennych
  
  for (int i = 0; i < SIZE; ++i) {                            //jako indeksow tablicy
        for (int j = 0; j < SIZE; ++j) {
	  out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

/*!
 * \brief Funkcja diagonalizuje macierz - doprowadza do macierzy
 *
 * \return        macierz diagonalna.
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE> &Matrix<TYPE,SIZE>::diagonalisation()
{
  TYPE no;
  this->changes = 1;
  for(int i = 0; i < SIZE; ++i)
    {
      no = value[i][i];
      if(value[i][i] < 0)
	{
	  no = no * (-1);
	}
      if(no < MIN) // jesli wartosc elementu jest 0
	{                                  // zamien kolumny
	  if(!this->find_and_change(i))
	    {
	      return *this; // zwrocenie macierzy, bo i tak bedzie 0
	    }
	  this->changes=-this->changes;    // zarejestrowanie zmiany
	}
      this->reset(i);      //wyzeruj to co z dolu
    }
  if(changes < 0){
    for(int i = 0; i < SIZE; ++i) // przemnozenie pierwszego wiersza przez -1
    {
      value[0][i] = value[0][i] * changes;
    }
  }
  return *this;
}


/*! 
 * \brief Znalezienie i zamiana 
 * 
 *  Funkcja znajduje element niezerowy na dol od wskazanego elementu
 *  macierzy, nastepnie zamienia wiersze zawierajaca znaleziony element
 *  z wskazanej kolumny
 *
 * \param[in]            column -przeszukiwana kolumna
 **
 * \return   1 gdy zostanie znaleziony niezerowy element i dokona sie zamiana
 *        0 gdy nie uda znalezc sie niezerowego elementu
 */
template<typename TYPE, int SIZE>
bool Matrix<TYPE,SIZE>::find_and_change(int column)
{
  TYPE no;
  no = 0;
   if (column < 0 || column >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
  int row = column, base = column;
  ++row;
  for(;row < SIZE; ++row) // konczy sie gdy znajdzie element niezerowy lub przekroczy zakres
    {
      if(value[row][column] < 0)
	;
      else
	no = value[row][column] * (-1);
      if(no < 0) // czy liczba jest mniejsza od 0 (rozna od 0 bo no
	break;                           //jest zawsze ujemne)
    }
  if(this->value[row][column] < MIN) // gdy nie ma niezerowego
    return false;
  else // gdy znajdzie niezerowy
    std::swap(value[row],value[base]); 
  return true;
}
/*!
 * \brief Funkcja zeruje wszystkie elementy w kolumna na dol od wskazanego argumentu
 *
 * \param[in]   column  - zerowana kolumna
 *
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE> Matrix<TYPE,SIZE>::reset(int column)
{
  if (column < 0 || column >= SIZE)
    {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem.\n");
    }
  TYPE a, no;
   int row = column;
  const int base = column; // to ma nie ulec zmianie
  no = value[row][base];
  if(value[row][base] < 0)
    {
      no = value[row][base] * (-1);
    }
  if(no < MIN)
    {
      throw std::runtime_error("Error: nie da sie wyzerowac zerowym elementem.\n");
    }
  ++column;
  for(;column < SIZE;++column)
    {
      a = this->value[column][row]/this->value[base][row];
      this->value[column]=this->value[column]-this->value[base]*a;
    }
  return *this;
}

/*!
 * \brief Funkcja transponuje macierz
 *
 * \return       Przetransponowana macierz
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE> Matrix<TYPE,SIZE>::transposition()
{
  Matrix<TYPE,SIZE> tmp;
  tmp = tmp + *this;
  for(int i = 0 ; i < SIZE ; ++i)
    {
      for(int j = 0 ; j < SIZE ; ++j)
	{
	  tmp(i,j)=value[j][i];
	}
    }
  for(int i = 0; i < SIZE ; ++i)
    {
      for(int j = 0; j <SIZE ; ++j)
	{
	  value[i][j] = tmp(i,j);
	}
    }
  return *this;
}
/*!
 * \brief  zamiana elementow
 *
 * Funkcja zamienia elementy we wskazanej 
 * kolumnie na te z podanego wektora
 *
 * \param[in]        column - kolumna, ktora chce sie zmienic
 * \param[in]       vector - wektor, ktorym ma zostac zastapiona kolumna
 *
 * \return    Macierz o ile column nie przekracza zakresu
 */
template<typename TYPE, int SIZE>
Matrix<TYPE,SIZE> Matrix<TYPE,SIZE>::column_change(int column, const Vector<TYPE,SIZE> &vector)
{
  if (column < 0 || column >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
  for(int i = 0; i < SIZE; ++i)
    {
      value[i][column] = vector[i];
    }
  return *this;
}
/*!
 * \brief Funkcja oblicza wyznacznik macierzy
 *
 * \return  wartosc wyznacznika macierzy 
 */
template<typename TYPE, int SIZE>
TYPE  Matrix<TYPE,SIZE>::Gauss()const
{
  Matrix tmp;
  
  tmp = tmp + *this;
  tmp.diagonalisation(); // diagoanalizacja
  TYPE det;
  det = tmp(0,0);
  for(int i = 1; i < SIZE; ++i)
    {
      det = det * tmp(i,i);
    }
  return det;
}

/*!
 * \brief Funkcja oblicza wyznacznik macierzy
 *
 * \param[in]      column - kolumna, ktora zostanie zamieniona z 
 *
 * \return wyznacznik macierzy
 */
template<typename TYPE, int SIZE>
TYPE  Matrix<TYPE,SIZE>::Gauss(int column, Vector<TYPE,SIZE> vector)const
{
   if (column < 0 || column >= SIZE) {
	throw std::runtime_error("Error: Macierz jest poza zasiegiem");
    } 
  Matrix<TYPE,SIZE> tmp;
  tmp = tmp + *this;
  tmp.column_change(column,vector); // zamiana  
  tmp.diagonalisation(); // diagoanalizacja
  TYPE det;
  det = tmp(0,0);
  for(int i = 1; i < SIZE; ++i)
    {
      det = det * tmp(i,i);
    }
  return det;
}

/*!
 * \brief liczenie normy frobeniusa 
 *
 * Funkcja liczy norme frobeniusa czyli pierwiastek sumy kwadratow
 * wszystkich elementow macierzy
 *
 * \return      Wartosc normy.
 */
template<typename TYPE, int SIZE>
TYPE Matrix<TYPE,SIZE>::Frobenius()const
{
  TYPE a = 0;
  for (int i = 0; i < SIZE; ++i)
    {
      for(int j = 0; j< SIZE; ++j)
	{
	  a += pow(value[i][j],2);
	}
    }
  a = sqrt(a);
  return a;
}




