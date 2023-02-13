#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include "Typy.hh"
#include "RotationMatrix.hh"
#include "ContourXY.hh"

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

/*!
 * \file
 * \brief Definiuje pojecie obiektu geometrycznego
 *
 * Plik zawiera definicje klasy obiektu geometrycznego,
 * ktory wyswtelany jest przez lacze do gnuplota.
 */

/*!
 * \brief Modeluje pojecie obiektu geometrycznego.
 */
class ObiektGeom {

protected:
  std::string   _NazwaPliku_BrylaWzorcowa;
  std::string   _NazwaPliku_BrylaRysowana;
  std::string   _NazwaObiektu;
  int           _KolorID;

  RotationMatrix Rotation; // Macierz rotacji
  Vector3D Skale; //skala w jakiej wswietla sie obiekt
  Vector3D Placement; // polozenie obiektu na powieszchni marsa
  ContourXY Contour; 
  
public:
  /*!
   * \brief na potrzeby polimorfizmu
   */
   virtual ~ObiektGeom(){}

  ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa,
	       const char* sNazwaObiektu, int KolorID);

  ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa,
	     const char* sNazwaObiektu, int KolorID,
	     Vector3D skale_in, Vector3D placement_in);

  int WezKolorID() const { return _KolorID; }
  
  const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
  
  const std::string & WezNazwePliku_BrylaRysowana() const
  { return _NazwaPliku_BrylaRysowana; }
  
  bool Przelicz_i_Zapisz_Wierzcholki();
  bool Przelicz_i_Zapisz_Wierzcholki(std::istream& StrmWe,
				     std::ostream& StrmWy);
  void Obj_Elements()const;

  /*!
  *\brief Pokazuje skale
  */
  Vector3D ShowSkale() const {return Skale;}

   /*!
  *\brief Pokazuje polozenie
  */
  Vector3D ShowPlacement() const {return Placement;}

  
  /*!
   * \brief Metoda wirtualna umozliwiajaca rozpoznanie klasy pochodnej
   *
   * \return 0 - gdy ObeiktGeom
   * \return 1 - gdy Rover
   *
   */
  virtual int Type_of_object () const {return 0;}

  /*!
   * \breif Wyswietla wartosci lewego dolnego i prawego gornego
   * wierzcholka skladajacego sie na obrys XY
   *
   */
  void what_is_a_contour(){std::cout << "lewy dolny: " << Contour.DL() << std::endl << "prawy gorny: " << Contour.UR() ;}
  
};


#endif
