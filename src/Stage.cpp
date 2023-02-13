#include<iostream>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObiektGeom.hh"
#include "Kolory.hh"
#include "Typy.hh"
#include "Stage.hh"
#include "chrono"
#include "thread"
#include "cstring"
#include "steps.hh"
#include "cmath"


/*! 
 * \breif Konstruktor bezparametryczny sceny
 *
 * Ustawia wskaznik na aktywny lazik na nullptr
 *
 */
Stage::Stage()
{
  std::shared_ptr<Rover> ActiveRover(nullptr);
  StageObjects.push_back(nullptr);
}

/*! 
 * \breif Inicjalizuje scene
 *
 * Ustawia wskaznik na aktywny lazik na nullptr
 *
 */
void Stage::Inicialization()
{
  Inicjalizuj_Lacze(Lacze);
  if (!Inicjalizuj_PowierzchnieMarsa(Lacze)) std::runtime_error("Nie udalo sie zainicjalizowac lacza\n");



  double tabS[3] = {20, 20, 10};
  double tabP1[3] = {20, 0, 0};
  double tabP2[3] = {60, 60, 0};
  double tabP3[3] = {-20, 70, 0};
 
  Vector3D Skala(tabS);
  Vector3D Polozenie1(tabP1);
  Vector3D Polozenie2(tabP2);
  Vector3D Polozenie3(tabP3);

  
  Rover  Ob1("bryly_wzorcowe/szescian3.dat","FSR",
  Kolor_JasnoNiebieski,Skala, Polozenie1);
  
  Rover  Ob2("bryly_wzorcowe/szescian3.dat","Perseverance",
	     Kolor_Czerwony, Skala, Polozenie2);
  Rover  Ob3("bryly_wzorcowe/szescian3.dat","Curiosity",
	     Kolor_Inny, Skala, Polozenie3);


  
  ActiveRover = std::make_shared<Rover>(Ob1);

 
  StageObjects.push_back(std::make_shared<Rover>(Ob1));
  StageObjects.push_back(std::make_shared<Rover>(Ob2));
  StageObjects.push_back(std::make_shared<Rover>(Ob3));
  
  DodajDoListyRysowania(Lacze,Ob1);
  DodajDoListyRysowania(Lacze,Ob2);
  DodajDoListyRysowania(Lacze,Ob3);


  Ob1.Przelicz_i_Zapisz_Wierzcholki(); //1
  Ob2.Przelicz_i_Zapisz_Wierzcholki(); //2
  Ob3.Przelicz_i_Zapisz_Wierzcholki(); //3

  Lacze.Rysuj();
}

/*!
 * \brief Aktywuje lazik
 *
 * wybrany lazik staje sie aktywny
 *
 * \param[in] chosen - numer wybranego lazika
 *
 */
void Stage::active_rover(int chosen)
{
  int i = 0;
  for(std::shared_ptr<ObiektGeom> &elem : StageObjects)
    {
      if(i==chosen)
	{
	ActiveRover = std::dynamic_pointer_cast<Rover>(elem);
	break;
	}
      ++i;
    }
}

/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */
void Stage::Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze)
{
  rLacze.ZmienTrybRys(PzG::TR_3D);
  rLacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
  rLacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
  rLacze.UstawZakresZ(-0, 90);  
  rLacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok

  rLacze.Inicjalizuj();  // Tutaj startuje gnuplot.
}

/*!
 * \brief Dodawania elementu do narysowania w gnuplocie
 *
 * \param[in] rLacze - lacze do gnuplota, umozliwiajace narysowanie obeiktu
 *            w gnuplocie
 * \param[in] ObiektGeom - figura, ktora ma zosatac narysowany
 *
 *
 */
void Stage:: DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom  &rOb)
{
  PzG::InfoPlikuDoRysowania *wInfoPliku;
  
  wInfoPliku = &rLacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
  wInfoPliku->ZmienKolor(rOb.WezKolorID());
}


/*!
 * \brief Wyrysowanie ciaglego przemieszczenia lazika na scenie
 *
 * Wyryrsowuje ruch lazikiem co "mala" odleglosc, aby przypominalo to ciagly
 * ruch lazika, a nie przeskok z jednego miejsca w nastepne
 *
 * \param[in] distance - odleglosc, jaka pokonac ma lazik
 * \param[in] speed - prednkosc z jako ma byc pokonana odleglosc
 */
void Stage::RoverMove(double distance, double speed)
 {

   double Step = step;
   double time = abs(distance/speed);
   if(distance < 0)
     Step = -Step;

   for(double i = 0; abs(i) < abs(distance); i=i+Step)
     {
       ActiveRover->Move(Step);
       ActiveRover->Przelicz_i_Zapisz_Wierzcholki();
       Lacze.Rysuj();
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
       }
    
 }

/*!
 * \brief Wyrysownie ciaglego obrotu lazika na scenie
 *
 * Wyrysowuje obrot lazika co "maly" kat, ale przypominalo to ciagly
 * obrut, a nie przeskok z jednoego miejsca w nastepne
 *
 * \param[in] alpha - kat o jaki ma obrocic sie lazik
 * \param[in] speed - predkosc obrotu 
 *
 */
void Stage::RoverSpin(double alpha, double speed)
 {

   double time = abs(alpha/speed);
   double Rot = rot;
   if(alpha < 0)
     Rot = -rot;
   
   for(double i = 0; abs(i) < abs(alpha); i = i + Rot)
   {
       ActiveRover->Spin(Rot);
       ActiveRover->Przelicz_i_Zapisz_Wierzcholki();
       Lacze.Rysuj();
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
       }
 }

/*!
 * \brief Wypisuje informacje o obecnej scenie
 *
 * Informuje o aktywnym laziku
 * o jego polozeniu i orientacji 
 * kacie orientacji lazika
 * oraz o ilosci utworzonych obiektow Vector3D
 *
 */

void Stage::Info()
{
  std::cout << "Aktywny lazik: " << ActiveRover->WezNazweObiektu() << std::endl;
  std::cout << "Polozenie: " << ActiveRover->ShowPlacement() << std::endl;
  std::cout << "Skala: " << ActiveRover->ShowSkale() << std::endl;
  std::cout << "Kat obrotu: "<< (ActiveRover->ShowAngle())*180/M_PI << std::endl;

  std::cout << "Wierzkolki z obrysu: \n";
  ActiveRover->what_is_a_contour();
  std::cout << std::endl;

  
  ActiveRover->Obj_Elements();
  std::cout << std::endl;
}
