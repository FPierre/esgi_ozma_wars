# OZMA WARS #

A "Shoot Them Up" game for Android with NDK.

## What? ##

* https://fr.wikipedia.org/wiki/Ozma_Wars
* https://www.youtube.com/watch?v=p4vqA98HP5k

## Why? ##

Student project: build an Android game with NDK library

## Who? ##

* Pierre Flauder
* Florent Blot

## TODO ##

* Commenter le code
* Dans toutes les classes, passer par des getters/setters
* Lors d'un impact d'un missile ennemi, prendre en compte la force de l'arme (Own ship ne part pas forcément tous ses points de vie d'un coup)
* Lors de la destruction d'un vaisseau ennemi, augmenter le score
* Musique d'ambiance
* Destructeurs de toutes les classes (delete les pointeurs, fonts, etc)
* Image de l'espace en background
* (OK) Son lors d'une collision ?
* Bug : lorsque Own ship tourne, les sprites "clignotent"
* (OK) Ajouter des vaisseaux ennemis dans LevelOne
* (OK) Le système de tir random des vaisseaux ennemi doit être passé en OOP
* (OK) Limiter le nombre de tirs sur Own ship et vaisseaux ennemis
* (OK) Tirs renvoient un boolean, si TRUE, tir fait (déclenche le son à partir de ce boolean). FALSE si nombre max de missile atteint
* Si score supérieur à X, passer au niveau suivant. A faire OOP
* Si points de vie de Own ship == 0, quitter le niveau (comment les destructeurs sont appelés ?)
* Détruire en mémoire et du vector les missiles qui sortent de l'écran
* Détruire en mémoire et du vector les vaisseaux ennemis qui sortent de l'écran
* (OK) Repasser la taille de l'écran en dynamique (actuellement mis en dur)
* Déplacement des vaisseaux ennemis (random comme pour le tir ?)
* Own ship doit être crée dans Game, pas LevelOne
* Bug : plus les ennemis sont loins d'Own ship, plus leurs missilles sont rapides
* Mettre en place LevelTwo