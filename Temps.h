/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 04 - Temps
 Fichier     : Temps.h
 Auteur(s)   : Mélodie Ohan, Dylan Canton
 Date        : 30.04.2020

 But         : Définition de la classe Temps, des opérateurs correspondants ainsi
               que des messages d'exceptions personnalisés.

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef LABO_04_TEMPS_H
#define LABO_04_TEMPS_H
#include <string>

/**--------------------- CONFIG ---------------------*/
/** Messages d'exceptions **/
//Pour E_HEURE_RANGE, l'interval supérieur dépend de la constante MAX_HEURE
//définie dans Temps_impl.h, elle ne doit donc pas être modifiée
const std::string E_HEURE_RANGE = "Heure hors intervalle [0-32000] dans : ";
const std::string E_MIN_RANGE   = "Minute hors intervalle [0-59]  dans  : ";
const std::string E_SEC_RANGE   = "Seconde hors intervalle [0-59] dans  : ";
const std::string E_SEC_NEG     = "Seconde negative dans : " ;
const std::string E_MIN_NEG     = "Minute negative dans  : " ;
const std::string E_HEURE_NEG   = "Heure negative dans   : " ;
// Message lors de l'exception du constructeur par copie d'un objet Temps aberrant
const std::string E_RUN         = "Construction impossible, objet temps incorrecte "
                                  "dans : ";

/**--------------------- PRE-DECLARATIONS ---------------------*/
template <typename T>
class Temps;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Temps<T>& t);

template <typename T>
bool operator==(const Temps<T>& temps, const Temps<T>& other);

template <typename T>
bool operator!=(const Temps<T>& temps, const Temps<T>& other);

template <typename T>
Temps<T> operator+(Temps<T> temps, const Temps<T>& other);

template <typename T>
Temps<T> operator-(Temps<T> temps, const Temps<T>& other);

/**--------------------- CLASS ---------------------*/
template <typename T>
class Temps
{
  /**--------------------- FRIENDS ---------------------*/

  /**Opérateurs de flux**/
  //Cette fonction se base sur le cast string du Temps
  friend std::ostream& operator<< <>(std::ostream& os, const Temps<T>& t);

  /**Opérateurs de comparaison**/
  friend bool operator== <>(const Temps<T>& temps, const Temps<T>& other);
  friend bool operator!= <>(const Temps<T>& temps, const Temps<T>& other);

  /**Opérateurs d'additions-soustractions**/
  friend Temps<T> operator+ <>(Temps<T> temps, const Temps<T>& other);
  friend Temps<T> operator- <>(Temps<T> temps, const Temps<T>& other);

public:
  /**------------------ CONSTRUCTEURS ------------------*/

  /**Constructeurs spécifiques**/
  Temps(T heure, T minute, T seconde);
  Temps(const Temps& temps);
  Temps(T seconde);

  /**---------------------- GETTER ---------------------*/
  T getHeure  () const;
  T getMinute () const;
  T getSeconde() const;

  /**---------------------- SETTER ---------------------*/
  void setHeure  (T heure)  ;
  void setMinute (T minute) ;
  void setSeconde(T seconde);

  /**------------------- OPERATEURS --------------------*/

  /**Operateurs de cast**/
  //Cast de réels, représente le temps en réel sur 100 au lieu de 60
  explicit operator float       () const;
  explicit operator double      () const;
  explicit operator long double () const;
  //Cast le temps en secondes
  explicit operator long long   () const;
  //Cast en string hh:mm:ss
  explicit operator std::string () const;

  Temps& operator+= (Temps<T> temps);
  Temps& operator-= (Temps<T> temps);
  Temps& operator=  (Temps<T> const& other);

  /**---------------- METHODES STATICS -----------------*/

  //Vérifie que la valeur donnée soit entre 0 et 59
  static bool minSecCorrecte(const T& value);
  //Vérifie qu'une heure soit dans l'intervalle 0 et max défini
  static bool heureCorrecte (const T& heure);

private:
  T seconde = 0;
  T minute  = 0;
  T heure   = 0;
};

#include "Temps_impl.h"
#endif //LABO_04_TEMPS_H