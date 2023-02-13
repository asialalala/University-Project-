#ifndef STAGE_HH
#define STAGE_HH

#include <memory>
#include<iostream>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObiektGeom.hh"
#include "Kolory.hh"
#include "Typy.hh"
#include "Rover.hh"
class Stage
{
private:
  std::shared_ptr<Rover> ActiveRover;
  std::list<std::shared_ptr<ObiektGeom>> StageObjects;
    PzG::LaczeDoGNUPlota  Lacze;
public:
  Stage();
  void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze);
  void  DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze,
			      const ObiektGeom  &rOb);
  void Inicialization();
  void active_rover(int chosen);
  void RoverMove(double distance, double speed);
  void RoverSpin(double alpha, double speed);
  void Info();
};

#endif
