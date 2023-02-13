#include <iostream>
#include <fstream>
#include "ObiektGeom.hh"
#include "Typy.hh"
#include "vector.hh"
#include "size.hh"


using namespace std;

/*!
 * \brief Konstruktor Obiektu Geometrycznego
 *
 * Inicjalizuje Nazwe Pliku, do ktorego wpisywane sa dane o obiekcie
 * oraz nazwe obiektu.
 *
 * \param[in] sNazwaPliku_BrylaWzorcowa - nazwa pliku, a wktorym zapisane sa
 * informacje o obiekcie
 * \param[in] sNazwaObiektu - nazwa obiektu, ktory ma sie wyswietlic
 * \param[in] KolorID - kolor, w jakim wyswietli sie obiekt w gnuplocie 
 *
 */
ObiektGeom::ObiektGeom( const char*  sNazwaPliku_BrylaWzorcowa,
		        const char*  sNazwaObiektu,
		        int          KolorID
		       ):
  _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
}

/*!
 * \brief Konstruktor Obiektu Geometrycznego
 *
 * Inicjalizuje Nazwe Pliku, do ktorego wpisywane sa dane o obiekcie,
 * nazwe obiektu, skale obiektu oraz jego polozenie
 *
 * \param[in] sNazwaPliku_BrylaWzorcowa - nazwa pliku, a wktorym zapisane sa
 * informacje o obiekcie
 * \param[in] sNazwaObiektu - nazwa obiektu, ktory ma sie wyswietlic
 * \param[in] KolorID - kolor, w jakim wyswietli sie obiekt w gnuplocie 
 * \param[in] skale_in - skala, w jakiej ma zostac wyswietlony obiekt
 * \param[in] placement_in - polozenie obiektu na plaszczyznie
 *
 */

ObiektGeom::ObiektGeom (const char* sNazwaPliku_BrylaWzorcowa,
	   const char* sNazwaObiektu, int KolorID,
	   Vector3D skale_in,
	   Vector3D placement_in):
  _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  Skale = skale_in;
  Placement = placement_in;
}

/*!
 * \brief  Otwiercie plikow do z informacjami o obiekcie
 * 
 * Otwiera plik, w ktorym znajduja sie pierwotnie iformacje o obiekcie
 * oraz plik, do ktorego zostana zapisanie iformacje o obiekcie po zmianie.
 *
 * \return true - gdy wszytsko sie powiedzie
 * \return false - gdy wystapi blad otwarcia ktoregos z plikow lub pojawi
 *         sie problem z obliczeniem wieszcholkow
 *
 */
bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
  ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
	 << "    " << _NazwaPliku_BrylaWzorcowa << endl
	 << "    " << _NazwaPliku_BrylaRysowana << endl
	 << endl;
    return false;
  }
  if (this->Przelicz_i_Zapisz_Wierzcholki(StrmWe, StrmWy))
    {
      return false;
    }

  return true;
 
}

/*!
 * \brief Przeliczenie wierzcholkow i zapisanie ich do pliku
 *
 * Czyta ze strumienia wejsciowego informacje o obiekcie.
 * Przelicza wieszkolki zgodnie ze skala i polozeniem obiektu.
 *
 * \param[in] StrmWe - plik, z ktorego czytane sa informacje o obiekcie
 * \param[in] StrmWy - plik, do ktorego zapisane sa informacje o obiekcie
 *                     po przeliczeniu wieszcholkow
 * 
 * \return true - gdy wszystko sie poweidzie
 * \return false - gdy pojawi sie problem przy zapisie
 *
 */

bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki( std::istream& StrmWe,
				   std::ostream& StrmWy) 
{
  Vector3D  Coords;
  int Indeks_Wiersza = 0;
  
  StrmWe >> Coords;
  
  if (StrmWe.fail())return false;

  do {
  Coords[0] = Coords[0]*Skale[0] + Placement[0];
  Coords[1] = Coords[1]*Skale[1] + Placement[1];
  Coords[2] = Coords[2]*Skale[2] + Placement[2];

  Coords = Rotation*(Coords-Placement)+Placement;
  
  StrmWy << Coords << endl;
  ++Indeks_Wiersza;
  
  if (Indeks_Wiersza >= 4) {
    StrmWy << endl;
    Indeks_Wiersza = 0;
  }
  
    StrmWe >> Coords;

    Contour.compare_change(Coords);
  } while (!StrmWe.fail());
  
  if (!StrmWe.eof()) return false;
  
  return Indeks_Wiersza == 0 && !StrmWy.fail();
}

/*!
 *  \brief Wyswtelenei ilosci stworzonych obiektow Vector
 */
void ObiektGeom::Obj_Elements()const
{
  Vector3D::elements();
  
}
