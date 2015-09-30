#include <cmath>
#include "background.h"

// ...

void star_init(SDL_Renderer *renderer, int axisX, int axisY, int posX, int posY) {
    // Dessine un cercle en blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Initialisation des variables
    int perimeter = 0; // Périmètre de départ

    int max = 250;
    int min = 0;

    // int posX = rand()%(max-min)+min; // Position de l'axe X (Random)
    // int posY = rand()%(max-min)+min; // Position de l'axe Y (Random)

    // Création du premier point de départ
    SDL_RenderDrawPoint(renderer, posX + axisX, posY - axisY);

    // Boucle du cercle
    for (axisX; axisX <= axisY; axisX++) {
        // On modifie le périmètre pour obtenir un rond
        if (perimeter < 0) {
            // L'axe Y ne change pas
            axisY = axisY;
            // Nouveau périmètre d'après l'axe X
            perimeter = perimeter + (10 * axisX) + 6;
        } else {
            // Sinon l'axe Y diminue
            axisY -= 1;
            // Nouveau périmètre d'après l'axe Y
            perimeter = perimeter + (10 * (axisX - axisY));
        }

        // Création des points du cercle avec comme paramètres :
        // Le rendu, le point sur l'axe X et le point sur l'axe Y
        SDL_RenderDrawPoint(renderer, posX + axisX, posY - axisY);
        SDL_RenderDrawPoint(renderer, posX - axisX, posY - axisY);
        SDL_RenderDrawPoint(renderer, posX + axisX, posY + axisY);
        SDL_RenderDrawPoint(renderer, posX - axisX, posY + axisY);
        SDL_RenderDrawPoint(renderer, posX + axisY, posY - axisX);
        SDL_RenderDrawPoint(renderer, posX - axisY, posY - axisX);
        SDL_RenderDrawPoint(renderer, posX + axisY, posY + axisX);
        SDL_RenderDrawPoint(renderer, posX - axisY, posY + axisX);
    }
}