/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 04 - Temps
 Fichier     : Temps_impl.h
 Auteur(s)   : Mélodie Ohan, Dylan Canton
 Date        : 30.04.2020

 But         : Fournis une classe Temps permettant de créer un temps au format
               hh:mm:ss ainsi que d'effectuer différentes opérations telles que :
               l'addition, la soustraction, la comparaison, l'affectation,
               l'affichage, le cast et la modification d'objets Temps.

 Remarque(s) : Les erreurs sont traitées avec des exceptions indiquant le type
               d'erreur, la raison ainsi que la fonction concernée.

               La classe Temps est générique. Cependant nous garantissons le bon
               fonctionnement avec les types signés suivant :
               short, int, long, long long.
               Les types non-signés correspondant fonctionnent également, hormis
               pour le constructeur Temps(secondes) qui fera un dépassement en
               cas de nombre négatif entrée pour un type non-signé.

               Le constructeur Temps(s) se base sur des modulos, par conséquent
               le programme aura un comportement indéfini et ne supporte pas
               de type T réel.

               Dans un soucis d'éviter les overflows pour le maximum d'heures
               possibles relatif au type utilisé. Il a été décidé de fixer un
               nombre d'heures maximum, auquel cas une exception sera levée en
               cas de dépassement de cette valeur.
               Elle est définie par la macro "MAX_HEURE" présente dans "Temps_impl.h"

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef LABO_04_TEMPS_IMPL_H
#define LABO_04_TEMPS_IMPL_H

/**--------------------- CONFIG ---------------------*/
//Ne doit pas être modifié
//IntervalLe logique du temps (minutes et secondes)
#define MIN_TEMPS 0
#define MAX_TEMPS 59
//Prévient les overflows dans les additions
#define MAX_HEURE 32000

using namespace std;

/**------------------ CONSTRUCTEURS ------------------*/

/**Constructeurs spécifiques**/
template <typename T>
Temps<T>::Temps(T heure, T minute, T seconde)
{
  try
  {
    if(!Temps<T>::heureCorrecte(heure))
    {
      throw range_error("std::range_error: " + E_HEURE_RANGE);
    }
    else if(minute < (T)MIN_TEMPS)
    {
      throw range_error( "std::range_error: " + E_MIN_NEG);
    }
    else if(seconde < (T)MIN_TEMPS)
    {
      throw range_error("std::range_error: " + E_SEC_NEG);
    }

    //A chaque étape on additionne l'excédent de l'unité de temps inférieur
    this->seconde =  seconde % (T)60;
    this->minute  = (seconde / (T)60)   % (T)60;
    this->minute +=  minute %  (T)60;
    this->heure   = (minute /  (T)60)   % (T)60;
    this->heure  += heure;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

//Constructeur par copie
template <typename T>
Temps<T>::Temps(const Temps& temps)
{
  try
  {
    //Par sécurité, pour ne pas copier un temps impossible
    if( !Temps<T>::minSecCorrecte(minute)  or
        !Temps<T>::minSecCorrecte(seconde) or
        heure < (T)MIN_TEMPS)
    {
      throw std::runtime_error("std::runtime_error: " + E_RUN);
    }

    *this = temps;  //Appel de l'opérateur d'affectation
  }
  catch (const std::runtime_error& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

template <typename T>
Temps<T>::Temps(T seconde)
{
  try
  {
    if(seconde < (T)MIN_TEMPS)
    {
      throw std::range_error("std::range_error: " + E_SEC_RANGE);
    }
    this->seconde =  seconde % (T)60;
    this->minute  = (seconde / (T)60)   % (T)60;
    this->heure   = (seconde / (T)3600) % (T)60;
  }
  catch (const std::range_error& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

/**---------------------- GETTER ---------------------*/
template <typename T>
T Temps<T>::getHeure() const
{
  return heure;
}

template <typename T>
T Temps<T>::getMinute() const
{
  return minute;
}

template <typename T>
T Temps<T>::getSeconde() const
{
  return seconde;
}

/**---------------------- SETTER ---------------------*/
template <typename T>
void Temps<T>::setHeure(T heure)
{
  try
  {
    if(!Temps<T>::heureCorrecte(heure))
    {
      throw std::range_error("std::range_error: " + E_HEURE_RANGE);
    }
    this->heure = heure;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

template <typename T>
void Temps<T>::setMinute(T minute)
{
  try
  {
    if(!Temps<T>::minSecCorrecte(minute))
    {
      throw range_error("std::range_error: " + E_MIN_RANGE);
    }

    this->minute = minute;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

template <typename T>
void Temps<T>::setSeconde(T seconde)
{
  try
  {
    if(!Temps<T>::minSecCorrecte(seconde))
    {
      throw std::range_error("std::range_error: " + E_SEC_RANGE);
    }

    this->seconde = seconde;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

/**---------------- METHODES MEMBRES -----------------*/
template <typename T>
Temps<T>& Temps<T>::operator+=(Temps<T> temps)
{
  try
  {
    //Gestion des heures
    if(this->heure + temps.heure > T(MAX_HEURE))
    {
      throw std::range_error("std::range_error: " + E_HEURE_RANGE);
    }
    this->heure += temps.heure;

    //Gestion des minutes
    if((this->minute + temps.minute) > (T)MAX_TEMPS)
    {
      if(this->heure + 1 > T(MAX_HEURE))
      {
        throw std::range_error("std::range_error: " + E_HEURE_RANGE);
      }
      this->heure += 1;
      this->minute = (this->minute + temps.minute) % (T)60;
    }
    else
    {
      this->minute += temps.minute;
    }

    //Gestion des secondes
    if(this->seconde + temps.seconde > (T)MAX_TEMPS)
    {
      this->minute += 1;
      this->seconde = (this->seconde + temps.seconde) % 60;
    }
    else
    {
      this->seconde += temps.seconde;
    }

    return *this;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

template <typename T>
Temps<T>& Temps<T>::operator-=(Temps<T> temps)
{
  try
  {
    //Gestion des secondes
    if(temps.seconde > this->seconde)
    {
      T secDiff = temps.seconde - this->seconde;
      this->seconde = ((T)MAX_TEMPS - secDiff + 1);

      //Gestion si la minute actuelle est à 0
      if(this->minute == (T)MIN_TEMPS)
      {
        //Gestion si l'heure actuelle est à 0
        if(this->heure == (T)MIN_TEMPS)
        {
          throw range_error("std::range_error: " + E_SEC_NEG);
        }
        else
        {
          this->heure -= 1;
          this->minute = (T)MAX_TEMPS;
        }
      }
      else
      {
        this->minute -= 1;
      }
    }
    else
    {
      this->seconde -= temps.seconde;
    }

    //Gestion des minutes
    if(temps.minute > this->minute)
    {
      T minDiff = temps.minute - this->minute;
      this->minute = ((T)MAX_TEMPS - minDiff + 1);

      //Gestion si l'heure actuelle est à 0
      this->heure == (T)MIN_TEMPS ? throw range_error("std::range_error: " +
                                                      E_MIN_NEG)
                                  : this->heure -= 1;
    }
    else
    {
      this->minute -= temps.minute;
    }

    //Gestion des heures
    temps.heure > this->heure ? throw range_error("std::range_error: " +
                                                  E_HEURE_NEG)
                              : this->heure -= temps.heure;
    return *this;
  }
  catch(exception& e)
  {
    cout << e.what() << __func__ << "()" << '\n';
  }
}

/**--------------------- FRIENDS ---------------------*/

/**Opérateurs de flux**/
template <typename T>
std::ostream& operator<< (std::ostream& os, const Temps<T>& t)
{
  os << std::string(t);
  return os;
}

/**--------------------- OPERATEURS  ---------------------*/

/**Opérateurs de comparaison**/
template <typename T>
bool operator==(const Temps<T>& temps, const Temps<T>& other)
{
  return temps.seconde == other.seconde and
         temps.minute  == other.minute  and
         temps.heure   == other.heure;
}

template <typename T>
bool operator!=(const Temps<T>& temps, const Temps<T>& other)
{
  return !(temps == other);
}

/**Opérateurs d'additions-soustractions**/
template <typename T>
Temps<T> operator+(Temps<T> temps, const Temps<T>& other)
{
  temps += other;
  return temps;
}

template <typename T>
Temps<T> operator-(Temps<T> temps, const Temps<T>& other)
{
  temps -= other;
  return temps;
}

/**Opérateurs d'affectation*/
template <typename T>
Temps<T>& Temps<T>::operator=(Temps<T> const& other)
{
  //Protection contre auto-affectation
  if(this == &other)
  {
    return *this;
  }

  heure   = other.heure  ;
  minute  = other.minute ;
  seconde = other.seconde;

  return *this;
}

/**Opérateurs de cast**/
template<typename T>
Temps<T>::operator float() const
{
  return  float(heure + (minute/60.f) + (seconde/3600.f));
}

template<typename T>
Temps<T>::operator double() const
{
  return  double(heure + (minute/60.) + (seconde/3600.));
}

template<typename T>
Temps<T>::operator long double() const
{
  return  (long double)(heure + (minute/60.l) + (seconde/3600.l));
}

template <typename T>
Temps<T>::operator long long()const
{
  long long t = heure * (long long)3600;
  t += minute * (long long)60;
  t += seconde;
  return t;
}

template<typename T>
Temps<T>::operator std::string() const
{
  std::string s;

  if(heure < 10)
  {
    s+='0';
  }
  s+= to_string(heure) + ':';

  if(minute < 10)
  {
    s+='0';
  }
  s+= to_string(minute) + ':';

  if(seconde < 10)
  {
    s+='0';
  }
  s+= to_string(seconde);

  return s;
}

//Vérifie que la valeur donnée soit entre 0 et 59
template <typename T>
bool Temps<T>::minSecCorrecte(const T& value)
{
  return (value >= (T)MIN_TEMPS and value <= (T)MAX_TEMPS);
}

//Vérifie qu'une heure soit dans l'intervalle 0 et max défini
template <typename T>
bool Temps<T>::heureCorrecte(const T& heure)
{
  return (heure >= (T)MIN_TEMPS and heure <= (T)MAX_HEURE);
}

#endif //LABO_04_TEMPS_IMPL_H