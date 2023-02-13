#ifndef ROVER_HH
#define ROVER_HH
#include "ObiektGeom.hh"
#include <cmath>
/*!
 * \file
 * \brief Modeluje pojecie lazika
 *
 * Definicja lazika. Mozna u niego okreslic kat oretacji, predkosc przejazdu 
 * oraz odleglosc do przejechania.
 *
 */

/*!
 * \brief Modeluje pojecie lazika
 */
class Rover
  : public  ObiektGeom
{
private:
  double Angle; // kat orientacji
  double Speed; // predkosc przejazdu
  double Distance; // odleglosc do przejechania
  
public:
  Rover(const char* sNazwaPliku_BrylaWzorcowa,
	     const char* sNazwaObiektu, int KolorI);

  Rover(double angle, double speed, double distance,
	const char* sNazwaPliku_BrylaWzorcowa,
	const char* sNazwaObiektu, int KolorID,
        Vector3D &skale_in,
        Vector3D &placement_i);

  Rover(const char* sNazwaPliku_BrylaWzorcowa,
	const char* sNazwaObiektu, int KolorID,
	Vector3D &skale_in,
	Vector3D &placement_in);

  void Move(const double _distance);

  Vector3D originalPlacement() const;
  
  void Spin(double alpha);

  double ShowAngle() {return Angle;};

  int  Type_of_object () const override {return 1;}
  
};


#endif

  
