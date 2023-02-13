#include "Rover.hh"
#include <cmath>
/*!
 * \brief Konstruktor bezparametryczny lazika
 *
 * Wypelnia wszystkie atrybuty obiektu Rover zerami,
 * jako obiektowi przypisuje podana nazwe, kolor i czyta
 * iformacje z pliku
 * 
 * \patam[in] sNazwaPliku_BrylaWzorcowa - nazwa pliku,a  zktorego sa pobierane
 *            informacje o obiekcie geometrycznym
 * \param[in] sNazwaObiektu - nazwa obiektu
 * \param[in] KolorID - kolor obiektu
 *
 */

Rover::Rover(const char* sNazwaPliku_BrylaWzorcowa,
	     const char* sNazwaObiektu, int KolorID):
             ObiektGeom(sNazwaPliku_BrylaWzorcowa,
			sNazwaObiektu, KolorID)
{
  Angle = Speed = Distance = 0;
}

/*!
 * \brief Konstruktor bezparametryczny lazika
 *
 * Wypelnia wszystkie atrybuty obiektu Rover 
 * wartosciami, ktore zostaly podane jako parametr, 
 * a jako obiekt przypisuje mu polozenie oraz skale,
 * nadaje nazwe, kolor i zczytuje informacje o obiekcie z pliku
 *
 * \param[in] angle - kat orientacji lazika
 * \param[in] speed - predkosc przejazdu lazika
 * \param[in] distance - odleglosc, ktora ma przejechac lazik
 * \patam[in] sNazwaPliku_BrylaWzorcowa - nazwa pliku,a  zktorego sa pobierane
 *            informacje o obiekcie geometrycznym
 * \param[in] sNazwaObiektu - nazwa obiektu
 * \param[in] KolorID - kolor obiektu
 * \param[in] skale_in - skala obiektu
 * \param[in] placement_in - polozenie obiektu
 *
 */

Rover::Rover(double angle, double speed, double distance,
	     const char* sNazwaPliku_BrylaWzorcowa,
	     const char* sNazwaObiektu, int KolorID,
	     Vector3D &skale_in,
	     Vector3D &placement_in):
             ObiektGeom(sNazwaPliku_BrylaWzorcowa,
			sNazwaObiektu, KolorID, skale_in, placement_in)
{
  Angle = angle;
  Speed = speed;
  Distance = distance;
}

/*!
 * \brief Konstruktor bezparametryczny lazika
 *
 * Wypelnia wszystkie atrybuty obiektu Rover zerami,
 * jako obiektowi przypisuje podana nazwe, kolor i czyta
 * iformacje z pliku. Ustawia takze wskazane polozenie
 * i skale
 * 
 * \patam[in] sNazwaPliku_BrylaWzorcowa - nazwa pliku,a  zktorego sa pobierane
 *            informacje o obiekcie geometrycznym
 * \param[in] sNazwaObiektu - nazwa obiektu
 * \param[in] KolorID - kolor obiektu
 * \param[in] skale_in - skala obiektu
 * \param[in] placement_in - polozenie obiektu
 *
 */

Rover::Rover(const char* sNazwaPliku_BrylaWzorcowa,
	     const char* sNazwaObiektu, int KolorID,
	     Vector3D &skale_in,
	     Vector3D &placement_in):
             ObiektGeom(sNazwaPliku_BrylaWzorcowa,
			sNazwaObiektu, KolorID, skale_in, placement_in)
{
  Angle = Speed = Distance = 0;
}


/*! 
 * \brief Zmienia polozenie lazika
 *
 * Przemieszcza lazik o wskazana odleglosc zgodnie z ruchem 
 * lazika, to znaczy wzdlu jego lokalnej osi X
 *
 * \param[in] tmp - nowe polozenie wktora
 *
 * \param[in] original - pierwotne polozenie lazika
 * \return Lazika
 *
 */

void Rover::Move(const double _distance)
{
  
  Placement[0] = Placement[0] + _distance*cos(Angle);
  Placement[1] = Placement[1] + _distance*sin(Angle);
}


/*!
 * \brief Pozwala uzyska informacje o polozeniu
 *
 * \return wartosc polozenie
 *
 */
Vector3D Rover::originalPlacement()const
{
  return Placement;
}

/*!
 * \brief Realizuje obrot lazika
 *
 * Obraca lazik o wskazany kat i zapamietuje wskazany kat.
 *
 * \param[in] alpha - kat o jaki ma sie obrocic lazik
 */
void Rover::Spin(double alpha)
{
  
  
  alpha = (M_PI*alpha)/180;
  Angle = Angle + alpha;
  Rotation = Rotation.Rz(Angle);
   
}
