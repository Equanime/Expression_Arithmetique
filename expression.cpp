#include "expression.h"

//_________________________________Q1_________________________________//
//___________________Pile___________________//
Pile::Pile()
{
    this->tete = nullptr;
}

Pile::~Pile()
{
    if (this->tete != nullptr)
    {
        delete this->tete;
    }
}
//_____________Fonction_demandé_____________//

// empile un maillon contenant un string
void Pile::empiler(string val)
{
    Maillon *M = new Maillon;
    M->Info = val;
    M->suivant = this->tete;
    this->tete = M;
}

// retourne le string du maillon en tete de pile
string Pile::depiler()
{
    if (this->vide())
    {
        cout << "impossible depiler,la pile vide";
        exit(-1);
    }
    else
    {
        Maillon *temp = this->tete;
        this->tete = this->tete->suivant;
        return temp->Info;
    }
}

bool Pile::vide()
{
    if (this->tete == nullptr)
    {
        return true;
    }
    return false;
}

// affiche une pile
void Pile::afficher()
{
    Maillon *temp = this->tete;

    while (temp != nullptr)
    {
        cout << temp->Info << " ; ";
        temp = temp->suivant;
    }
    cout << endl;
}

// evalue une expresion string suffixé
string Pile::evaluer_suf(string exp_suff)
{
    string operande;
    double var1, var2;
    for (char &c : exp_suff)
    {
        bool is_ope_bin = c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
        bool is_ope_un = c == '_';
        bool is_operator = is_ope_bin || is_ope_un;
        if (c != ' ' && not(is_operator)) // Si c est un chiffre
        {
            operande += c; // Pour obtenir un string je concactène les char jusqu'a tombé sur un espace ou un operateur.
        }
        else
        {
            if (operande != "") // si mon operande/nombre est complete
            {
                this->empiler(operande); // je l'empile
                operande = "";           // je la réinitialise
            }
            if (is_ope_un)
            {
                var1 = stod(this->depiler());
                this->empiler(to_string(-var1));
            }
            if (is_ope_bin) // Si je tombe sur un operateur, je dépile deux operandes, calcul, ré empile.
            {
                var1 = stod(this->depiler());
                var2 = stod(this->depiler());
                switch (c)
                {
                case '+':
                    this->empiler(to_string(var1 + var2));
                    break;
                case '-':
                    this->empiler(to_string(var2 - var1));
                    break;
                case '*':
                    this->empiler(to_string(var1 * var2));
                    break;
                case '/':
                    this->empiler(to_string(var2 / var1));
                    break;
                case '^':
                    this->empiler(to_string(pow(var1, var2)));
                    break;
                }
            }
        }
    }
    return this->depiler(); // je depile le resultat
}
//______________Fonction_bonus______________//
void question1()
{
    cout << "//_________________________________Q1_________________________________//" << endl
         << endl;
    Pile Pl;
    cout << "Testons les fonctions vide,empiler,depiler sur la pile Pl." << endl;
    cout << "1) Pl est-elle vide ? ";
    if (Pl.vide())
    {
        cout << "La pile est vide" << endl;
    }
    cout << "2) J'empile '12.5', 'X' et '+' , voici Pl := ";
    Pl.empiler("X");
    Pl.empiler("12.5.0");
    Pl.empiler("+");
    Pl.afficher();
    cout << "3) Je dépile '+' et j'empile '- 9 Y' , voici Pl := ";
    Pl.depiler();
    Pl.empiler("9 Y -");
    Pl.afficher();
    cout << endl;

    cout << "Testons la fonction evaluer." << endl;
    Pile P;
    string expression_suffixe = "10.5 5 3-* 7/";
    cout << "Soit l'expression suffixé  := " << expression_suffixe << endl;
    cout << "Le resultat vaut := " << P.evaluer_suf("10.5 5 3-* 7/") << " ." << endl
         << endl;
}
//_________________________________Q2_________________________________//
//_____________Fonction_demandé_____________//

// convertie une expression infixe en suffixe
string Pile::inf_suf(string str)
{
    string operande, operateur, Lsortie[str.size() * 5], a_evaluer; //*5 pour ne pas deborder du tableau
    int taille_L = 0;
    for (char &c : str)
    {
        bool est_operation = c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == ')' || c == ' ' || c == '^' || c == '_';
        if (not(est_operation))
        {
            Lsortie[taille_L++] = operande = c;
        }
        else
        {
            switch (c)
            {
            case '-' || ' ':
                while (not(vide()) && tete->Info != "(")
                {
                    Lsortie[taille_L++] = this->depiler();
                }
                break;
            case '+':
                while (not(vide()) && tete->Info != "-" && tete->Info != "(")
                {
                    Lsortie[taille_L++] = this->depiler();
                }
                break;
            case '/':
                while (not(vide()) && tete->Info != "-" && tete->Info != "+" && tete->Info != "(")
                {
                    Lsortie[taille_L++] = this->depiler();
                }
                break;
            case '*':
                while (not(vide()) && tete->Info != "-" && tete->Info != "+" && tete->Info != "/" && tete->Info != "(")
                {
                    Lsortie[taille_L++] = this->depiler();
                }
                break;
            case '_':
                while (not(vide()) && tete->Info != "-" && tete->Info != "+" && tete->Info != "/" && tete->Info != "(" && tete->Info != "_")
                {
                    Lsortie[taille_L++] = this->depiler();
                }
                break;
            case ')':
                while (not(vide()))
                {
                    if (tete->Info != "(")
                    {
                        Lsortie[taille_L++] = this->depiler();
                    }
                    else
                    {
                        this->depiler();
                    }
                }
                break;
            }
            if (c != ')')
            {
                Lsortie[taille_L++] = " ";
                empiler(operateur = c);
            }
        }
        /* cout << "liste ";
         this->affich_liste(Lsortie, taille_L);
         cout << "pile ";
         this->afficher();
         cout << endl;*/
    }

    if (not(vide()))
    {
        Lsortie[taille_L++] = this->depiler();
    }

    for (int j = 0; j < taille_L; j++)
    {
        a_evaluer += Lsortie[j];
    }
    cout << "On obtient l'expression suffixé := " << a_evaluer << ";" << endl;
    // cout << "Le resultat vaut ";
    return a_evaluer;
}

// evalue une expression infixé
string Pile::evaluer_inf(string str)
{
    cout << "Voici l'expression infixé :" << str << endl;
    return this->evaluer_suf(inf_suf(str));
}
//______________Fonction_bonus______________//
void question2()
{
    cout << "//_________________________________Q2_________________________________//" << endl
         << endl;
    Pile P;
    cout << "Testons la fonction qui transforme une expression infixé en suffixé." << endl
         << endl;
    cout << P.evaluer_inf("10.5*(5-3)/7") << " est le résultat du calcul." << endl
         << endl;
    cout << P.evaluer_inf("(5-3)/7+(_2)") << " est le résultat du calcul." << endl
         << endl;
}
//_________________________________Q3_________________________________//
//_____________Fonction_demandé_____________//

//_______________Pile_adresse_______________//
Pile_ad::Pile_ad()
{
    this->tete = nullptr;
}

Pile_ad::~Pile_ad()
{
    if (this->tete != nullptr)
    {
        delete this->tete;
    }
}

bool Pile_ad::vide_ad()
{
    if (this->tete == nullptr)
    {
        return true;
    }
    return false;
}
// empile l'adresse d'un Noeud
void Pile_ad::empiler_noeud(Noeud *N)
{
    Maillon_ad *M = new Maillon_ad;
    M->adresse = N;
    M->suivant = this->tete;
    this->tete = M;
}
// retourne l'adresse du maillon/noeud en tete de pile
Noeud *Pile_ad::depiler_noeud()
{
    if (this->vide_ad())
    {
        cout << "impossible depiler,la pile vide";
        exit(-1);
    }
    else
    {
        Maillon_ad *temp = this->tete;
        this->tete = this->tete->suivant;
        return temp->adresse;
    }
}
//_____________Cons/Destructeur_____________//

// construire Noeud vide
Noeud::Noeud()
{
    this->fg == nullptr;
    this->fd == nullptr;
}
// construire d'arbre vide
Arbre::Arbre()
{
    this->racine = nullptr;
}
// constructeur d'Arbre à partir d'un expression infixe (string)
Arbre::Arbre(string exp_infixe)
{
    this->racine = nullptr;
    Pile P;
    string expSuff = P.inf_suf(exp_infixe); // on transforme l'expression infixe en suffixe
    // on construit l'arbre
    Pile_ad Pad;
    string nombre = "";

    for (char &c : expSuff)
    {
        bool est_operation = c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '_';
        if (c != ' ' && not(est_operation)) // si c n'est pas un espace ou une operation
        {
            nombre += c;
        }
        else
        {
            if (nombre != "") // si le string nombre n'est pas vide
            {
                bool est_var = nombre == "X" || nombre == "Y" || nombre == "Z";
                if (est_var) // si c'est une variable
                {
                    Pad.empiler_noeud(new Noeud(nombre[0]));
                    nombre = "";
                }
                else
                {
                    Pad.empiler_noeud(new Noeud(stod(nombre)));
                    nombre = "";
                }
            }
            if (est_operation)
            {
                // cout << c << endl;
                if (c != '_')
                {
                    Noeud *N = new Noeud(c, nullptr, nullptr);
                    N->fd = Pad.depiler_noeud();
                    N->fg = Pad.depiler_noeud();
                    Pad.empiler_noeud(N);
                }
                else
                {
                    Noeud *N = new Noeud(c, nullptr, nullptr);
                    N->fd = Pad.depiler_noeud();
                    Pad.empiler_noeud(N);
                }
            }
        }
    }
    this->racine = Pad.depiler_noeud();
}

Arbre::~Arbre()
{
    if (this->racine != nullptr)
    {
        delete this->racine;
    }
}

Noeud::~Noeud()
{
    if (this->fg != nullptr)
    {
        delete this->fg;
    }
    if (this->fd != nullptr)
    {
        delete this->fd;
    }
}
//______________Arbre__binaire______________//
void Noeud::afficher()
{
    if (this->fg != nullptr)
    {
        cout << "(";
        this->fg->afficher();
    }
    bool var = this->ope == 'X' || this->ope == 'Y' || this->ope == 'Z';
    if (this->type == 'o' || var) // si operateur ou variable
    {
        if (this->ope == '_')
        {
            cout << "(-";
        }
        else
        {
            cout << this->ope;
        }
    }
    else // si valeur
    {
        cout << this->val;
    }
    if (this->fd != nullptr)
    {
        this->fd->afficher();
        cout << ")";
    }
}

void Arbre::afficher()
{
    if (this->racine != nullptr)
    {
        this->racine->afficher();
        cout << endl;
    }
}
// j'evalue un noeud qui creer une expression au fur et a mesure de la lecture de noeud
void Noeud::evaluer_noeud(Noeud *N, string &expSuf)
{
    if (N) // si le noeud N existe
    {
        evaluer_noeud(N->fg, expSuf);                                          // Parcours du sous-arbre gauche
        evaluer_noeud(N->fd, expSuf);                                          // Parcours du sous-arbre droit
        if (N->type == 'o' || N->ope == 'X' || N->ope == 'Y' || N->ope == 'Z') // si operateur ou variable
        {
            expSuf += N->ope;
        }
        else // si valeur
        {
            expSuf += to_string(N->val);
        }
        expSuf += ' ';
    }
}
// j'evalue un Arbre en utilisant la fonction ci-dessus
void Arbre::evaluer_arbre()
{
    Pile P;             // je creer la pile pour utiliser evaluer_suf
    string expSuf = ""; // je creer l'expression suffixé que je passe par reference pour la concactener
    if (this->racine == nullptr)
    {
        exit(-1);
    }
    this->racine->evaluer_noeud(this->racine, expSuf); // j'evalue chaque noeud depuis la racine
    cout << P.evaluer_suf(expSuf) << endl;             // j'évalue et affiche
}
//______________Fonction_bonus______________//
void question3()
{
    cout << "//_________________________________Q3_________________________________//" << endl
         << endl;

    cout << "Voici l'arbre A construit à partir d'une expression infixe. " << endl;
    Arbre A("10.5*(5-3)/7");
    cout << "Construit à partir de ";
    A.afficher();
    cout << "Le resultat de A vaut := ";
    A.evaluer_arbre();
    cout << endl;

    cout << "Voici l'arbre B construit à partir d'une expression infixe. " << endl;
    Arbre B("(5-3)/7+2");
    cout << "Construit à partir de ";
    B.afficher();
    cout << "Le resultat de B vaut : ";
    B.evaluer_arbre();
    cout << endl;

    cout << "Voici l'arbre C construit à partir de Noeuds := ";
    Arbre C(new Noeud('/', new Noeud('X'), new Noeud(1.0)));
    C.afficher();
    cout << endl;
    cout << "Voici l'arbre D construit à partir de Noeud := ";
    Arbre D(new Noeud('-', new Noeud('*', new Noeud(4.0), new Noeud('^', new Noeud('X'), new Noeud(2.0))), new Noeud('+', new Noeud('*', new Noeud(2.0), new Noeud('Y')), new Noeud('_', nullptr, new Noeud('Z')))));
    D.afficher();
    cout << endl;
}
//_________________________________Q4_________________________________//

//_____________Cons/Destructeur_____________//
// constructeur de noeud par recopie
Noeud::Noeud(Noeud *N)
{
    type = N->type;
    if (type == 'o' || (N->ope == 'X' || N->ope == 'Y' || N->ope == 'Z')) // si variable ou operateur
    {
        ope = N->ope;
    }
    else // si valeur
    {
        val = N->val;
    }
    if (N->fg != nullptr)
    {
        fg = new Noeud(N->fg);
    }
    if (N->fd != nullptr)
    {
        fd = new Noeud(N->fd);
    }
}
// constructeur d'Arbre par recopie
Arbre::Arbre(Noeud *racine)
{
    this->racine = new Noeud(racine);
}
//_____________Fonction_demandé_____________//

// constructeur de Noeud operateur
Noeud::Noeud(char ope, Noeud *fg, Noeud *fd)
{
    bool is_operateur = ope == '+' || ope == '-' || ope == '/' || ope == '*' || ope == '^' || ope == '_';
    if (is_operateur)
    {
        this->type = 'o';
        this->ope = ope;
        this->fg = fg;
        this->fd = fd;
    }
}
// constructeur de Noeud de nombre
Noeud::Noeud(double val)
{
    this->type = 'f';
    this->val = val;
    this->ope = '\0';
    this->fg = nullptr;
    this->fd = nullptr;
}
// constructeur de Noeud variable
Noeud::Noeud(char var)
{
    bool is_variable = var == 'X' || var == 'Y' || var == 'Z';
    if (is_variable)
    {
        this->type = 'f';
        this->ope = var;
        this->fg = nullptr;
        this->fd = nullptr;
    }
}

// Calcul la derivé du contenue d'un Noeud selon une variable
Noeud *Arbre::derive(Noeud *courant, char var)
{
    Noeud *C(courant);
    if (C->type == 'o')
    {
        if (C->ope == '-' || C->ope == '+')
        {
            return new Noeud(C->ope, this->derive(C->fg, var), this->derive(C->fd, var));
        }
        else if (C->ope == '*')
        {
            return new Noeud('+', new Noeud(C->ope, this->derive(C->fg, var), C->fd), new Noeud(C->ope, C->fg, this->derive(C->fd, var)));
        }
        else if (C->ope == '/')
        {
            return new Noeud('/', new Noeud('-', new Noeud('*', this->derive(C->fg, var), C->fd), new Noeud('*', C->fg, this->derive(C->fd, var))), new Noeud('^', C->fd, new Noeud(2.0)));
        }
        else if (C->ope == '_')
        {
            return new Noeud('_', nullptr, this->derive(C->fd, var));
        }
        else if (C->ope == '^')
        {
            if (C->fg->ope == var || C->fg->ope == var)
            {
                return new Noeud('*', new Noeud('*', C->fd, this->derive(C->fg, var)), new Noeud(C->ope, C->fg, new Noeud(C->fd->val - 1)));
            }
            else
            {
                return new Noeud(0.0);
            }
        }
    }
    else if (C->type == 'f' && C->ope == var)
    {
        return new Noeud(1.0);
    }
    else
    {
        return new Noeud(0.0);
    }
    return nullptr;
}

// Calcul la derivé d'une expression contenue dans un Arbre selon une variable
Arbre Arbre::derive_arbre_selon(char var)
{
    return (derive(this->racine, var));
}

//______________Fonction_bonus______________//
void question4()
{
    cout << "//_________________________________Q4_________________________________//" << endl
         << endl;

    cout << "Voici l'arbre E construit à partir de l'expression infixe '4*(X^2)-(2*Y)+(_Z)' ." << endl;
    Arbre E("4*(X^2)-(2*Y)+(_Z)");
    cout << "E vaut ";
    E.afficher();
    cout << endl;
    cout << "Voici l'arbre F construit par recopie de E, il représente la derivé de E en fonction de X : " << endl;
    Arbre F(E.derive_arbre_selon('X'));
    F.afficher();
    cout << endl;
    cout << "Voici l'arbre G construit par recopie de E, il représente la derivé de E en fonction de Y : " << endl;
    Arbre G(E.derive_arbre_selon('Y'));
    G.afficher();
    cout << endl;
    cout << "Voici l'arbre H construit par recopie de E, il représente la derivé de E en fonction de Z : " << endl;
    Arbre H(E.derive_arbre_selon('Z'));
    H.afficher();
    cout << endl;
}

//_______________________________Bonus________________________________//
void question_bonus()
{
    cout << "//_______________________________Bonus________________________________//" << endl
         << endl;
    cout << "rentrer une expression infixée := ";
    string exp_inf;
    cin >> exp_inf;
    cout << "Voici l'arbre I construit à partir de l'expression infixe " << exp_inf << " ." << endl;
    Arbre I(exp_inf);
    cout << "I vaut ";
    I.afficher();
}