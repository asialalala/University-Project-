#pragma once

#include <iostream>
#include <min.hh>


/*!
 * \file
 * \brief Definicja szablonu klasy Vector
 *
 * Klasa vector reprezentuje wektor o trzech skladowych
 *
 * zawiera metody pozwalajace na odwolywanie sie i zamiane
 * poszczegolnych skladowych wektora oraz metody 
 * umozliwiajace operacje dodawania i odejmoawania 
 * dwoch wektorow, a takze mnozenia i dzielenia wektora
 * przez liczbe
 */

/*!
 * \brief Modeluje pojecie wektora
 */
template<typename TYPE, int SIZE>
class Vector {

private:

  TYPE size[SIZE];     //Tablica wektora
  static int all_elements;
  static int active ;

public:

  Vector(); //konstruktor bezparametryczny 

  Vector(TYPE [SIZE]); //konstruktor parametryczny

    ~Vector(); // destruktor

    Vector(const Vector<TYPE,SIZE> &copy); //konstruktor kopiujacy

  Vector<TYPE, SIZE>& operator=(const Vector<TYPE, SIZE>&) = default;
  
  Vector<TYPE,SIZE> operator + (const Vector<TYPE,SIZE> &v)const;
  
  Vector<TYPE,SIZE> operator - (const Vector<TYPE,SIZE> &v)const;
  
  Vector<TYPE,SIZE> operator * (const TYPE &tmp)const; // mnoezenie przez liczbe
  
  TYPE operator * (const Vector<TYPE,SIZE> &tmp)const; // iloczyn skalarny
  
  Vector<TYPE,SIZE> operator / (const TYPE &tmp)const;
  
  const TYPE &operator [] (int index)const; // te nie
  
  TYPE &operator [] (int index); // te mozna zmieniac

  static void elements()
  {
    std::cout << "Liczba aktywnych obiektow Vector: " << active << std::endl;
    std::cout << "Liczba wszystkich obiektow Vector: " << all_elements << std::endl;
  }


};

template<typename TYPE, int SIZE>
int Vector<TYPE,SIZE>::all_elements=0; // liczba wszystkich obiektow
template<typename TYPE, int SIZE>
int Vector<TYPE,SIZE>::active=0 ; // liczba aktywnych obiektow



template<typename TYPE, int SIZE>
std::ostream &operator << (std::ostream &out, Vector<TYPE,SIZE> const &tmp);

template<typename TYPE, int SIZE>
std::istream &operator >> (std::istream &in, Vector<TYPE,SIZE> &tmp);


/*!
 * \brief  Konstruktor klasy Vector.                                            
 * 
 * Wypelnia wektor 0.
 */
template<typename TYPE,int SIZE>
Vector<TYPE,SIZE>::Vector() {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
    }
    
    ++active; 
    ++all_elements;
}


/*!
 *  \brief Konstruktor klasy Vector.                                           
 *
 *  Wypelnia vector podana tablica liczb.
 * 
 *  \param tmp - Jednowymiarowa tablica typu TYPE.              
 */
template<typename TYPE,int SIZE>
Vector<TYPE,SIZE>::Vector(TYPE tmp[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
    
    ++active;
    ++all_elements;
}

/*!
 * Destruktor klacy Vector
 *
 * Zmniejsza ilsoc aktywnych obiektow
 *
 */

template<typename TYPE, int SIZE>
Vector<TYPE,SIZE>::~Vector()
{
 --active;
 }


/*!
 * \brief konstruktor kopiujacy
 */

template<typename TYPE, int SIZE>
Vector<TYPE,SIZE>::Vector(const Vector<TYPE,SIZE> &copy)
{
  *this = copy;
  ++active;
  ++all_elements;
}

/*!
 * \brief przeciazenie operatora przypisania
 * 
 */
/*template<typename TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator=(constVector<TYPE, SIZE>& copy)
{
  for(int i =0; i < SIZE; ++i)
    {
      *this[i] = copy[i];
    }
}
*/
/*!
 * \brief Realizuje dodawanie dwoch wektorow.   
 *                             
 * \param v - drugi skladnik dodawania.                                    
 *
 * \return Sume dwoch skladnikow przekazanych jako wskaznik            
 *      na parametr.                                                          
 */
template<typename TYPE, int SIZE>
Vector<TYPE,SIZE> Vector<TYPE,SIZE>::operator + (const Vector &v)const {
  Vector<TYPE,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] + v[i];
    }
    return result;
}


/*!
 * \brief Realizuje odejmowanie dwoch wektorow.                                 
 *
 * \param[in]     v - drugi skladnik odejmowania.         
 *                        
 * \return     Roznice dwoch skladnikow przekazanych jako wskaznik              
 *      na parametr.                                                          
 */
template<typename TYPE, int SIZE>
Vector<TYPE,SIZE> Vector<TYPE,SIZE>::operator - (const Vector &v)const {
  Vector<TYPE,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] - v[i];
    }
    return result;
}


/*!
 * \brief Realizuje mnozenie wektora przez liczbe typu TYPE.  
 *             
 *  \param[in]    tmp - drugi skladnik mnozenia (liczba typu TYPE).       
 *          
 *  \return    Iloczyn dwoch skladnikow przekazanych jako wskaznik    
 *      na parametr.                                                          
 */
template<typename TYPE, int SIZE>
Vector<TYPE,SIZE> Vector<TYPE,SIZE>::operator * (const TYPE &tmp)const {
  Vector<TYPE,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] * tmp;
    }
    return result;
}

/*!
 * \brief  Realizuje mnozenie wektora przez wektor    
 *                          
 * \param[in]     v - drugi skladnik mnozenia (wektor).      
 *                       
 * \return     Iloczyn dwoch skladnikow przekazanych jako wskaznik              
 *      na parametr.                                                          
 */
template<typename TYPE, int SIZE>
TYPE Vector<TYPE,SIZE>::operator * (const Vector &v)const {
    TYPE result;
    result = 0;
    for (int i = 0; i < SIZE; ++i) {
        result += size[i]*v[i];
    }
    return result;
}




/*!
 * \brief  Realizuje dzielenie wektora przez liczbe typu TYPE.   
 *               
 * \param[in]       tmp - mianownik dzielenia.      
 *                                
 * \return     Iloraz dwoch skladnikow przekazanych jako wskaznik               
 *       na parametr. Wyrzuca blad, gdy tmp jest 0                                                          
 */
template<typename TYPE, int SIZE>
Vector<TYPE,SIZE> Vector<TYPE,SIZE>::operator / (const TYPE &tmp)const {
  TYPE no = tmp;;
  if(tmp < 0.0){
    no = no * (-1);
  }
  if(no < MIN) // sprawdzenie czy liczba jest zerem
    throw std::runtime_error("Nie wolno dzielic przez 0.");
  Vector<TYPE,SIZE> result;
    
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] / tmp;
    }

    return result;
}


/*!
 * \brief Funktor wektora.   
 *                                                   
 * \param[in]     index - index wektora.     
 *                                       
 * \return     Wartosc wektora w danym miejscu tablicy jako stala.               */
template<typename TYPE, int SIZE>
const TYPE &Vector<TYPE,SIZE>::operator [] (int index) const {
    if (index < 0 || index >= SIZE) {
	throw std::runtime_error("Error: Wektor jest poza zasiegiem");
    } 
    return size[index];
}


/*!
 * \brief  Funktor wektora.            
 *                                         
 * \param[in]      index - index wektora.       
 *            
 * \return      Wartosc wektora w danym miejscu tablicy.                        
 */
template<typename TYPE, int SIZE>
TYPE &Vector<TYPE,SIZE>::operator[](int index)
{
   if (index < 0 || index >= SIZE) {
	throw std::runtime_error("Error: Wektor jest poza zasiegiem");
    } 
   return const_cast<TYPE &>(const_cast<const Vector *>(this)->operator[](index)); 
}//Wytlumaczenie funkcji, czytac od prawego dolu _
//robi go stalum wskaznikiem na double
//---rzutuje ten staly wskaznik na wektor na wskaznik na double
//----robi go stalym wskaznikiem
//------rzutuje wartosc wektora na wskaznik na wektor


/*!
 * \brief  Przeciazenie operatora <<   
 *                                         
 * \param[in]      out - strumien wejsciowy,                                        
 * \param[in]     tmp - wektor.          
 *                                           
 * \return strumien wyjsciowy
 */
template<typename TYPE, int SIZE>
std::ostream &operator << (std::ostream &out, Vector<TYPE,SIZE> const &tmp) {
    for (int i = 0; i < SIZE; ++i) {

        out << tmp[i] << " ";
    }
    return out;
}


/*!
 * \brief Przeciazenie operatora >>   
 *                                          
 * \param[in]      in - strumien wyjsciowy,                                         
 * \param[in]      tmp - wektor.         
 *                                           
 * \return strumien wejsciowy
 */
template<typename TYPE, int SIZE>
std::istream &operator >> (std::istream &in, Vector<TYPE,SIZE> &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}
