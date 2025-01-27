#ifndef _TEST_H_
#define _TEST_H_

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct Maillon // structure de liste chainée
{
    string Info;
    Maillon *suivant;
};

class Pile // Pile de Maillon
{
    Maillon *tete;

public:
    ~Pile();
    Pile();
    void empiler(string val);
    string depiler();
    bool vide();
    void afficher();
    string evaluer_inf(string str);
    string inf_suf(string str);
    string evaluer_suf(string str);
};

class Noeud
{
    char type;      // ‘o’ pour opérateur et ‘f’ pour valeur.
    char ope;       // operateur ou variable
    double val;     // valeur constante
    Noeud *fg, *fd; // fils gauche et fils droits
    friend class Arbre;

public:
    ~Noeud();
    Noeud();
    Noeud(Noeud *N);                             // constructeur par recopie
    Noeud(double ope);                           // constructeur d'operande/valeur
    Noeud(char variable);                        // constructeur de variable
    Noeud(char operateur, Noeud *fg, Noeud *fd); // constructeur d'operateur
    void afficher();
    void evaluer_noeud(Noeud *N, string &expSuf);
};
class Arbre
{
    Noeud *racine;

public:
    ~Arbre();
    Arbre();
    Arbre(Noeud *racine);
    Arbre(string exp_infixe);
    void afficher();
    void evaluer_arbre();
    Noeud *derive(Noeud *courant, char var); // calcul la derivée d'un Noeud rattaché à un arbre
    Arbre derive_arbre_selon(char var);      // calcul la derivé d"un arbre
};

struct Maillon_ad // Maillon adresse
{                 // contient l'adresse d'un Noeud et un pointeur vers le maillon suivant
    Noeud *adresse;
    Maillon_ad *suivant;
};

class Pile_ad
{
    Maillon_ad *tete;

public:
    Pile_ad();
    ~Pile_ad();
    bool vide_ad();
    void empiler_noeud(Noeud *N);
    Noeud *depiler_noeud();
};
// bonus
void question1();
void question2();
void question3();
void question4();
void question_bonus();

#endif