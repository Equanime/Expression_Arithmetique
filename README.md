## Informations Générales
- **Cours :** Structures de Données et Algorithmes L2 Informatique
- **Travail Pratique :** Manipulation d'Expressions Arithmétiques

## Membres de l'équipe
- **Adragna Angelo**

# Présentation

## Description
Ce projet porte sur la manipulation d'expressions arithmétiques à l'aide de structures de données comme les piles, les listes chaînées et les arbres binaires. Les différentes étapes comprennent :
1. L'évaluation d'expressions en notation suffixée à l'aide d'une pile.
2. La conversion d'une expression infixée en notation suffixée via l'algorithme de la gare de triage.
3. La construction d'arbres binaires pour représenter les expressions et leur évaluation.
4. L'écriture de fonctions pour générer les arbres des dérivées d'expressions arithmétiques.

### Prérequis
- **Langage :** C++
- **Bibliothèques nécessaires :** Aucune spécifique à ce projet.
  
# Mode d'emploi

## Fonctionnalités principales

### 1. Évaluation d'une expression suffixée
- **Classe `Pile` :** Implémentée avec une liste chaînée, elle comprend les fonctions suivantes :
  - `void empiler(float valeur)`
  - `float depiler()`
  - `bool vide()`
- **Fonction `evaluer` :**
  - Parcourt l'expression de gauche à droite.
  - Empile les opérandes.
  - Dépile les deux derniers opérandes pour appliquer un opérateur, puis empile le résultat.

Exemple :
Pour l'expression `abc+*`, les étapes sont :
1. Empiler `a`, `b`, `c`.
2. Appliquer `+` à `b` et `c`, empiler le résultat.
3. Appliquer `*` au résultat précédent et à `a`.

### 2. Conversion infixée → suffixée
- **Algorithme de la gare de triage :**
  - Les opérandes sont ajoutés directement à la sortie.
  - Les opérateurs sont gérés à l'aide d'une pile selon leur priorité et associativité.
  - Les parenthèses permettent de déclencher des vidages partiels de la pile.
- Fonctionnalités à implémenter :
  - Gestion des priorités et associativités.
  - Conversion des expressions.

### 3. Construction d'arbres binaires
- **Classe `Noeud` :** Représente un opérateur ou une valeur.
  - `type` : `‘o’` pour opérateur, `‘f’` pour valeur.
  - `ope` : Caractère de l'opérateur.
  - `val` : Valeur flottante (si applicable).
  - `fg` et `fd` : Pointeurs vers les fils gauche et droit.
- **Classe `Arbre` :**
  - Constructeur avec une expression infixée.
  - Fonctions :
    - `evaluation` : Évalue l'arbre.
    - `afficher_infixe` : Affiche l'expression en notation infixée avec parenthèses.

### 4. Gestion des dérivées d'expressions
- Calcul des dérivées en utilisant les règles standards :
  - `(u + v)' = u' + v'`
  - `(u ∗ v)' = u' ∗ v + u ∗ v'`
  - `(u^n)' = n ∗ u' ∗ u^(n-1)`
  - etc.
- Adaptation des classes `Noeud` et `Arbre` pour permettre la représentation des expressions dérivées.

# Compilation et exécution

### Compilation
Utilisez un compilateur C++ standard :
```
make
```

### Exécution
Lancez le programme avec :
```
./Prog.exe
```

## Consignes
1. Implémentez chaque fonctionnalité en respectant les spécifications.
2. Testez vos fonctions avec des exemples simples et complexes.
3. Documentez votre code pour faciliter sa compréhension.

## Limites
1. Les expressions doivent être valides et bien formées.
2. Les arbres et piles utilisent une mémoire proportionnelle à la taille de l'expression.
3. La gestion des opérateurs est restreinte à `+`, `-`, `*`, `/` et `^`.

# Débogage et Améliorations

### Tests unitaires
Créez des tests unitaires pour chaque module afin d'assurer leur bon fonctionnement. Exemple :
- **Module `Pile` :**
  - Testez l'empilage et le dépilage avec différentes tailles de piles.
- **Conversion infixée → suffixée :**
  - Utilisez des cas limites comme `(a + b) * c` ou des opérateurs de même priorité.

### Suggestions d'amélioration
1. Ajouter la gestion des erreurs pour les expressions mal formées.
2. Implémenter une interface graphique pour visualiser les arbres binaires.
3. Intégrer la gestion d'opérateurs supplémentaires ou personnalisés.
4. Optimiser la gestion mémoire pour les structures dynamiques.

