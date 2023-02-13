#include <iostream>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObiektGeom.hh"
#include "Kolory.hh"
#include "Typy.hh"
#include "Rover.hh"
#include "RotationMatrix.hh"
#include "Stage.hh"
#include "cmath"
#include "ContourXY.hh"

using namespace std;

/*!
* \brief Pozwala uzytkownikowi wybrac odleglosc przejazdu
*
* \return dlugosc przejazdu
*/
double  Ride()
{
  double distance;
  cout << "Prosze podac odleglosc przejazdu (w jednostkach sceny).\n";
  cin >> distance;
    if(cin.fail())
    {
     cin.ignore(100,'\n');
      std::runtime_error("Nie udalo sie wczytac odleglosci.\n");
    }
  return distance;
  
}

/*!
* \brief Pozwala uzytkownikowi wybrac predkosc przejazdu
*
* \return predkosc przejazdu
*/
double  Speed()
{
  double speed;
  cout << "Prosze podac predkosc.\n";
  cin >> speed;
    if(cin.fail())
    {
      cin.ignore(100,'\n');
      std::runtime_error("Nie udalo sie wczytac predkosci.\n");
    }
  return speed;
  
}

/*!
* \brief Pozwala uzytkownikowi wybrac kat obrotu
*
* \return kat obrotu
*/
double Rot()
{
  double rot;
  cout << "Prosze podac kat(w stopniach).\n";
  cin >> rot;
  if(cin.fail())
    {
      cin.ignore(100,'\n');
      std::runtime_error("Nie udalo sie wczytac kata.\n");
    }
  return rot;
}

/*!
* \brief Pozwala uzytkownikowi wybrac aktywny lazik
*
* \return numer lazika na liscie
*/
int Activation()
{
  cout << "Mozliwe wybory:\n";
  cout << "1. FSR\n";
  cout << "2. Perseverance\n";
  cout << "3. Curiosity\n";
  cout << endl;
  int activation;

  cout << "Prosze wybrac lazik." << endl;
  cin >> activation;
  if(cin.fail())
    {
      cin.ignore(100,'\n');
      std::runtime_error("Nie udalo sie wczytac wybranego lazika.\n");
    }
  if(activation != 1 && activation != 2 && activation != 3)
    {
      std::runtime_error("Podano nieprawidlowy numer aktywacji lazika.\n");
    }
  return activation;
}



/*
 * \brief Lazik robi 8
 */
void eight(Stage & Surface)
{
  int n = 10; 
  int R = 5;
  double distance = 0;
  double angle = ((n-2)*180)/(2*n);
  distance = R*sqrt(2 - 2*cos((180-2*angle)*M_PI/180));
  angle = 90 - angle;

  for(int i = 1; i <= 2*n; ++i)
    {
      Surface.RoverSpin(angle, 5);
      Surface.RoverMove(distance, 5);
    }

  angle = - angle;

  for(int i = 1; i <= 2*n; ++i)
    {
      Surface.RoverSpin(angle, 5);
      Surface.RoverMove(distance, 5);
    }
}


/* 
 * \breif Menu uzytkownika
 */
int main()
{

  /*Stage SurfaceOfMars;
  int a; // do wybierania opcji
  double distance = 0, speed = 0, angle = 0; // do ruchu
  int chosen = 0 ; // do aktywacji lazika
  SurfaceOfMars.Inicialization();

  
  cout << endl << "Start programu gnuplot" << endl << endl;

  cout << "Jako uzytkownik problamu moziesz wybrac lazik, a nastepnie" <<
    "poruszac sie nim po powieszchni Marsa." <<  endl;

  cout << "  " << endl;
  cout << "  " << endl;
  cout << "  " << endl;

  

  
  SurfaceOfMars.active_rover(1); // aktywacja jednego z lazikow


  
  

  do{

    SurfaceOfMars.Info();
	
    cout << "Mozliwosci do wykonania\n";
    cout << "1. Jazda lazikiem na wprost.\n";
    cout << "2. Obrot lazika o zadany kat.\n";
    cout << "3. Wybor lazika.\n";
    cout << "4. Koniec programu.\n";
    cout << "5. Zrob osemke.\n";

    
    cin >> a;
    if(cin.fail())
      {
	cin.ignore(100,'\n');
	std::runtime_error("Nie udalosie wczytac opcji.\n");
      }

    
    switch(a)
      {
      case 1:
	
	distance = Ride();
	speed = Speed();
	SurfaceOfMars.RoverMove(distance, speed);
	break;
	
      case 2:
	angle= Rot();
	speed = Speed();
	SurfaceOfMars.RoverSpin(angle, speed);
	break;
      
      case 3:
	chosen = Activation();
	SurfaceOfMars.active_rover(chosen);
	break;
      
      case 4:
	exit(0);
	break;

      case 5:
	eight(SurfaceOfMars);
	break;
	
      default:
	cout << endl;
	cout << "Nie ma takiej mozliwosci, prosze wybrac ponownie.\n";
	cout << endl;
	cout << endl;
	
      }
  }
  while(a!=4);
  */


  Stage SurfaceOfMars;
  SurfaceOfMars.Inicialization();


  SurfaceOfMars.Info();
  ContourXY cc(2,4,4,6);
  ContourXY aa(4,4,6,6);
  if(cc.collide(aa))
    {
      cout << "Kolizja!!!\n";
    }
  
}
