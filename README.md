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
* Son lors d'une collision ?
* Bug sur Own ship lorsqu'il tourne, les sprites "clignotent"
* Ajouter des vaisseaux ennemis dans LevelOne
* Le système de tir random des vaisseaux ennemi doit être passé en OOP
* Si score supérieur à X, passer au niveau suivant. A faire OOP
* Si points de vie de Own ship == 0, quitter le niveau (comment les destructeurs sont appelés ?)