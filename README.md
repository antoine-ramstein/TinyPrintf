# 🖨️ Tinyprintf - Réimplémentation de printf

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Criterion](https://img.shields.io/badge/Testing-Criterion-green.svg)
![EPITA](https://img.shields.io/badge/School-EPITA-red.svg)

Il s'agit du développement d'une version simplifiée de la célèbre fonction `printf(3)` de la bibliothèque standard C.

## 📝 Description

L'objectif principal est de recréer la logique de formatage de chaînes et de gestion des arguments variadiques, en respectant des contraintes très strictes. Le code a été rédigé en respectant la norme C99 et doit compiler sans erreur avec les flags `-Werror`, `-Wall`, `-Wextra`, et `-pedantic`.

Les fonctionnalités et contraintes principales de notre implémentation sont :

- **Gestion des directives de base** : Prise en charge de `%%` (pourcentage), `%d` (décimal signé), `%u` (décimal non signé), `%c` (caractère), et `%s` (chaîne de caractères).
- **Conversions de bases** : Implémentation de `%o` pour la représentation octale non signée et `%x` pour l'hexadécimal en minuscules.
- **Gestion de la mémoire et des erreurs** : Si un argument de type chaîne (`%s`) est un pointeur `NULL`, la fonction affiche explicitement `(null)` au lieu de provoquer une erreur de segmentation.
- **Contrainte extrême** : L'intégralité du mécanisme d'affichage a été conçue en utilisant **uniquement** la fonction standard `putchar(3)`.
- **Valeur de retour** : Tout comme la fonction standard, l'implémentation calcule et retourne le nombre exact de caractères écrits sur la sortie standard.

## 🏗️ Architecture du Projet

Le code source est modulaire et séparé pour isoler la logique du programme de ses tests :

- 📂 `src/` : Contient le code source principal de la bibliothèque, avec l'implémentation dans `tinyprintf.c` et l'en-tête `tinyprintf.h`.
- 📂 `tests/` : Contient la suite complète de tests unitaires (`test.c`) développée avec le framework Criterion pour valider le comportement.
- 📄 `Makefile` : Le fichier d'orchestration situé à la racine pour automatiser la compilation et la vérification.

## ⚙️ Prérequis

Pour compiler et tester ce projet, votre environnement (idéalement Linux / UNIX) doit disposer des outils et bibliothèques suivants :

- Compilateur **GCC** ou **Clang**
- **Make**
- **Criterion** : Framework utilisé pour l'exécution de la suite de tests unitaires.

Installation des dépendances (Ubuntu/Debian) :

```bash
sudo apt update
sudo apt install build-essential libcriterion-dev
```

## 🚀 Compilation & Exécution (Makefile)

Le projet utilise un `Makefile` principal situé à la racine pour faciliter l'intégration et la compilation.

### 1. Compilation simple

Pour générer uniquement le fichier objet `src/tinyprintf.o`, exécutez la commande suivante à la racine du projet :

```bash
make
```

### 2. Lancement de la suite de tests

Pour compiler le projet et lancer automatiquement la suite de tests unitaires via Criterion :

```bash
make check
```

> **Note :** Ce projet est testé rigoureusement. Tous les tests doivent passer avec succès, sans aucune erreur ni plantage dans la sortie de Criterion.

### 3. Nettoyage du projet

Pour supprimer tous les fichiers produits par `make` lors de la compilation (`.o`, exécutables de test) afin de repartir sur un répertoire propre :

```bash
make clean
```

## 🖱️ Notice d'utilisation

Pour utiliser `tinyprintf` au sein de vos propres projets C, suivez ces étapes :

1. **Inclusion** : Incluez le fichier d'en-tête `tinyprintf.h` dans votre code source.
2. **Appel de la fonction** : Utilisez la fonction exactement de la même manière que le `printf` classique de `<stdio.h>`.

```c
#include "tinyprintf.h"

int main(void) {
    // Affiche : Hello [42] world!
    tinyprintf("%s [%d] %s\n", "Hello", 42, "world!");
    return 0;
}
```

3. **Édition de liens** : Lors de la compilation finale de votre programme, n'oubliez pas de lier le fichier objet généré (`src/tinyprintf.o`) avec vos autres sources.

## 👥 Auteur

Projet réalisé par :

- Antoine Ramstein
