#include <android/log.h>

#include "headers/Game.h"

#define LOG_TAG "Game"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Game::Game() {
    // LOGI("Constructeur trivial");
}

// TODO Faire le destructeur spécial de TTF
Game::Game(int _score, Window _window) : score(_score),
                                         window(_window) {

    // LOGI("Constructeur");
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 30);
    this->font = font;
    SDL_Color text_color = { 0, 0, 0 };
    this->text_color = text_color;

    Rgb blue_background(0, 255, 255);
    Sprite missile_image(55, 390, 50, 20, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);

    if (&missile_image != nullptr) {
        this->missile_image = missile_image;
    }
    else {
        LOGI("Sprite missile_image n'a pas pu être crée");
    }

    Rgb pink_background(255, 0, 255);
    Sprite enemy_ship_image(155, 303, 30, 28, 180.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    if (&enemy_ship_image != nullptr) {
        this->enemy_ship_image = enemy_ship_image;
    }
    else {
        LOGI("Sprite enemy_ship_image n'a pas pu être crée");
    }

    Sprite own_ship_image(41, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);
    Sprite own_ship_image_left(82, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);
    Sprite own_ship_image_right(0, 42, 40, 45, 0.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    if (&own_ship_image != nullptr) {
        this->own_ship_image = own_ship_image;
        this->own_ship_image_left = own_ship_image_left;
        this->own_ship_image_right = own_ship_image_right;
    }
    else {
        LOGI("Sprite missile_image n'a pas pu être crée");
    }

    Weapon canon(100, &(this->missile_image));

    OwnShip own_ship(500, 500, 100, 4, canon, &(this->own_ship_image),
                                                &own_ship_image_left,
                                                &own_ship_image_right);

    this->own_ship = own_ship;

    // Création des spites pour la destruction de vaisseau
    Sprite destroyed_ship_image_step1(0, 132, 78, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    Sprite destroyed_ship_image_step2(78, 132, 90, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    Sprite destroyed_ship_image_step3(168, 132, 103, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);

    if (&destroyed_ship_image_step1 != nullptr) {
        this->destroyed_ship_image_step1 = destroyed_ship_image_step1;
        this->destroyed_ship_image_step2 = destroyed_ship_image_step2;
        this->destroyed_ship_image_step3 = destroyed_ship_image_step3;
    }
    else {
        LOGI("Sprite destroyed_ship_image n'a pas pu être créée");
    }
}

Game::Game(const Game& _game) {
    LOGI("Constructeur par copie");

    score = _game.score;
    font = _game.font;
    window = _game.window;
    own_ship = _game.own_ship;
    missile_image = _game.missile_image;
    enemy_ship_image = _game.enemy_ship_image;
    own_ship_image = _game.own_ship_image;
    own_ship_image_left = _game.own_ship_image_left;
    own_ship_image_right = _game.own_ship_image_right;
}

Game::~Game() {

}

/**
 * @param int points Points à rajouter en plus du score actuel.
 */
int Game::update_score(int points) {
    return this->score += points;
}

void Game::render_score() {
    char buffer[4];
    int score = this->score;
    int ret = snprintf(buffer, sizeof(buffer), "%d", score);
    char *text = buffer;

    SDL_Surface *message = TTF_RenderText_Solid(this->font, text, this->text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
    int mWidth = message->w;
    int mHeight = message->h;
    SDL_Rect test = { 100, 10, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &test);
}

void Game::render_life() {
    char buffer[4];
    int number = this->own_ship.get_health();
    int ret = snprintf(buffer, sizeof(buffer), "%d", number);
    char *text = buffer;

    SDL_Surface *message = TTF_RenderText_Solid(this->font, text, this->text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
    int mWidth = message->w;
    int mHeight = message->h;
    SDL_Rect test = { 200, 10, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &test);
}

void Game::render_destroy(Ship& _ship) {
    LOGI("Statut du vaisseau (start) : %d", _ship.get_status());

    // On décrémente le statut du vaisseau
    _ship.set_status( 1 ); // status -= 1;

    // En fonction du statut, on affiche les étapes de l'explosion
    if (_ship.get_status() == 3) 
    {
        _ship.set_sprite(&(this->destroyed_ship_image_step1));
    } 
    else if (_ship.get_status() == 2) 
    {
        _ship.set_sprite(&(this->destroyed_ship_image_step2));
    } 
    else if (_ship.get_status() == 1)
    {
        _ship.set_sprite(&(this->destroyed_ship_image_step3));
    }

    LOGI("Statut du vaisseau (end) : %d", _ship.get_status());
}
