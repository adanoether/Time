/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 04 - Temps
 Fichier     : main.cpp
 Auteur(s)   : Mélodie Ohan, Dylan Canton
 Date        : 30.04.2020

 But         : Procedure de test concernant les outils offerts par la classe "Temps"
               Les points suivants sont contrôlés :
               - Les constructeurs
               - Les getter/setter
               - Les opérateurs d'affectation, de comparaison, d'affichage,
                 d'addition/soustraction et de cast.
               - Le traitement des erreurs à l'aide d'exceptions.

 Remarque(s) : Aucune anomalie constatée durant le déroulement des tests hormis
               lors de l'utilisation de réels.

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Temps.h"

using namespace std;

int main() {

/***********************************************************************************/
  const string T_SUB_SEP     = "-----------------"             ;

  cout << "************************" << endl;
  cout << "*    CONSTRUCTEURS     *" << endl;
  cout << "************************" << endl;
  cout << endl;

  Temps<short> ts1(12,15,20);
  cout << "ts1(12,15,20)      : " << ts1 << endl;

  /**Exception**/
  cout << "ts2(-1,-15,-20)    : ";
  Temps<short> ts2(-1,-15,-20);
  cout << "ts3(1,-15,20)      : ";
  Temps<short> ts3(1,-15,20);
  cout << "ts4(1,15,-20)      : ";
  Temps<short> ts4(1,15,-20);
  Temps<int> ti1(1,62,3);
  cout << "ti1(1,62,3)        : " << ti1 << endl;

  cout << T_SUB_SEP << endl;

  Temps<unsigned long long> tull1(950000);
  cout << "tull1(950000)      : "   << tull1 << endl;
  Temps<int> ti2(5025);
  cout << "ti2(5025)          : "   << ti2   << endl;
  Temps<unsigned long long> tull2(-1);
  cout << "tull2(-1) (borrow) : "   << tull2 << endl;
  //Il effectue un dépassement car unsigned
  cout << "tll1(-1)           : ";
  Temps<long long> tll1(-1);

  cout << T_SUB_SEP << endl;

  Temps<short> ts5(ts1);
  cout << "ts5(ts1)           : " << ts5 << endl;

/***********************************************************************************/
  cout << endl << endl;
  cout << "************************" << endl;
  cout << "*     AFFECTATION      *" << endl;
  cout << "************************" << endl;
  cout << endl;

  cout << "ts1(" << ts1 << ") "
       << "ts2(" << ts2 << ")"    << endl;
  ts2 = ts1;
  cout << "ts2 = ts1" << endl;
  cout << "ts1(" << ts1 << ") "
       << "ts2(" << ts2 << ")"    << endl;

  cout << T_SUB_SEP << endl;

  cout << "tull1(" << tull1 << ") "
       << "tull2(" << tull2 << ")"    << endl;
  tull2 = tull1;
  cout << "tull2 = tull1" << endl;
  cout << "tull1(" << tull1 << ") "
       << "tull2(" << tull2 << ")"    << endl;

/***********************************************************************************/
  cout << endl << endl;
  cout << "************************" << endl;
  cout << "*        GETTER        *" << endl;
  cout << "************************" << endl;
  cout << endl;

  Temps<int> tInt(2,30,0);
  cout << "Temps : " << tInt << endl << endl;

  cout << "Heure   : " << tInt.getHeure()   << endl;
  cout << "Minute  : " << tInt.getMinute()  << endl;
  cout << "Seconde : " << tInt.getSeconde() << endl;

/***********************************************************************************/
  cout << endl << endl;
  cout << "************************" << endl;
  cout << "*        SETTER        *" << endl;
  cout << "************************" << endl;
  cout << endl;

  cout << "Temps (avant modification) : " << tInt << endl << endl;

  cout << "# setHeure  (10)" << endl;
  tInt.setHeure(10);
  cout << "# setMinute (26)" << endl;
  tInt.setMinute(26);
  cout << "# setSeconde(40)" << endl << endl;
  tInt.setSeconde(40);

  cout << "Temps (apres modification) : " << tInt << endl << endl;

  cout << "# setHeure  (-10)" << endl;
  tInt.setHeure(-10);
  cout << "# setMinute (60)"  << endl;
  tInt.setMinute(60);
  cout << "# setSeconde(200)" << endl;
  tInt.setSeconde(200);
  cout << endl;

  cout << "Temps [int] (apres exceptions) : " << tInt << endl;

/***********************************************************************************/
  cout << endl << endl;
  cout << "*************************************" << endl;
  cout << "*      ADDITION / SOUSTRACTION      *" << endl;
  cout << "*************************************" << endl;
  cout << endl;

  /**********Additions (int)**********/
  cout << "# Temps t1 [int] : " << tInt << endl << endl;
  Temps<int> intTmp(3, 12, 30);

  cout << tInt << " + " << intTmp << " = " << tInt + intTmp << endl;
  intTmp.setHeure  (0) ;
  intTmp.setMinute (0) ;
  intTmp.setSeconde(54);
  cout << tInt << " + " << intTmp << " = " << tInt + intTmp << endl;
  intTmp.setHeure  (1) ;
  intTmp.setMinute (46);
  intTmp.setSeconde(2) ;
  cout << tInt << " + " << intTmp << " = " << tInt + intTmp << endl << endl;

  /**********Additions (int) Exception**********/

  intTmp.setHeure  (32000);
  intTmp.setMinute (0)    ;
  intTmp.setSeconde(0)    ;
  cout << tInt << " + " << intTmp << " = ..." << endl;
  tInt + intTmp;
  cout << endl;

  /**********Soustraction (int)**********/
  intTmp.setHeure  (1)   ;
  intTmp.setMinute (46)  ;
  intTmp.setSeconde(2)   ;
  cout << tInt << " - " << intTmp << " = " << tInt - intTmp << endl;
  intTmp.setHeure  (0)   ;
  intTmp.setMinute (0)   ;
  intTmp.setSeconde(54)  ;
  cout << tInt << " - " << intTmp << " = " << tInt - intTmp << endl;
  intTmp.setHeure  (1)   ;
  intTmp.setMinute (22)  ;
  intTmp.setSeconde(59)  ;
  cout << tInt << " - " << intTmp << " = " << tInt - intTmp << endl << endl;

  /**********Soustraction (int) Exceptions**********/
  intTmp.setHeure  (15) ;
  intTmp.setMinute (0)  ;
  intTmp.setSeconde(0)  ;
  cout << tInt << " - " << intTmp << " = ...." << endl;
  tInt - intTmp;

  intTmp.setHeure  (0) ;
  intTmp.setMinute (45);
  intTmp.setSeconde(0) ;

  tInt.setHeure    (0) ;
  tInt.setMinute   (15);
  tInt.setSeconde  (0) ;
  cout << tInt << " - " << intTmp << " = ...." << endl;
  tInt - intTmp;

  intTmp.setHeure  (0) ;
  intTmp.setMinute (0) ;
  intTmp.setSeconde(50);

  tInt.setHeure    (0) ;
  tInt.setMinute   (0) ;
  tInt.setSeconde  (40);
  cout << tInt << " - " << intTmp << " = ...." << endl;
  tInt - intTmp;
  cout << endl << endl;

  /**********Soustraction (unsigned int)**********/
  Temps<unsigned int> uInt(10,26,40);
  cout << "# Temps t2 [unsigned int] : " << uInt << endl << endl;
  Temps<unsigned int> uIntTemp(1, 46, 2);

  cout << uInt << " - " << uIntTemp << " = " << uInt - uIntTemp << endl;
  uIntTemp.setHeure  (0) ;
  uIntTemp.setMinute (0) ;
  uIntTemp.setSeconde(54);
  cout << uInt << " - " << uIntTemp << " = " << uInt - uIntTemp << endl;
  uIntTemp.setHeure  (1) ;
  uIntTemp.setMinute (22);
  uIntTemp.setSeconde(59);
  cout << uInt << " - " << uIntTemp << " = " << uInt - uIntTemp << endl << endl;

  /**********Soustraction (unsigned int) Exceptions**********/
  uIntTemp.setHeure  (15);
  uIntTemp.setMinute (0) ;
  uIntTemp.setSeconde(0) ;
  uInt.setHeure      (10);
  uInt.setMinute     (0) ;
  uInt.setSeconde    (0) ;
  cout << uInt << " - " << uIntTemp << " = ...." << endl;
  uInt - uIntTemp;

  uIntTemp.setHeure  (0) ;
  uIntTemp.setMinute (45);
  uIntTemp.setSeconde(0) ;
  uInt.setHeure      (0) ;
  uInt.setMinute     (15);
  uInt.setSeconde    (0) ;
  cout << uInt << " - " << uIntTemp << " = ...." << endl;
  uInt - uIntTemp;

  uIntTemp.setHeure  (0) ;
  uIntTemp.setMinute (0) ;
  uIntTemp.setSeconde(50);
  uInt.setHeure      (0) ;
  uInt.setMinute     (0) ;
  uInt.setSeconde    (40);
  cout << uInt << " - " << uIntTemp << " = ...." << endl;
  uInt - uIntTemp;

/***********************************************************************************/
  cout << endl << endl;
  cout << "************************" << endl;
  cout << "*      COMPARAISON      *"<< endl;
  cout << "************************" << endl;
  cout << endl;

  cout << boolalpha;

  intTmp.setHeure  (0) ;
  intTmp.setMinute (0) ;
  intTmp.setSeconde(40);
  cout << tInt << " == " << intTmp << " ? " << (tInt == intTmp) << endl;
  cout << tInt << " != " << intTmp << " ? " << (tInt != intTmp) << endl << endl;

  intTmp.setHeure  (1) ;
  intTmp.setMinute (23);
  intTmp.setSeconde(15);
  cout << tInt << " == " << intTmp << " ? " << (tInt == intTmp) << endl;
  cout << tInt << " != " << intTmp << " ? " << (tInt != intTmp) << endl;

/***********************************************************************************/
  cout << endl << endl;
  cout << "************************" << endl;
  cout << "*         CASTS        *" << endl;
  cout << "************************" << endl;
  cout << endl;

  Temps<int> ti3(5025);
  cout << "# Temps : " << ti3 << endl << endl;
  cout << setprecision(15);
  cout  << "float(ti)      : " << float(ti3)         << endl;
  cout  << "double(ti)     : " << double(ti3)        << endl;
  cout  << "long double(ti): " << (long double)(ti3) << endl;
  cout  << "long long(ti)  : " << (long long)(ti3)   << endl;
  cout  << "string(ti)     : " << string(ti3)        << endl;

  return EXIT_SUCCESS;
}