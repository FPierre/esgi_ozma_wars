#include <android/log.h>

#include "headers/Game.h"

#define LOG_TAG "Game"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Status des vaisseaux pour gérer l'animation de destruction
const int STATUS_NORMAL         = 80;
const int STATUS_DESTROY_STEP_1 = 60;
const int STATUS_DESTROY_STEP_2 = 40;
const int STATUS_DESTROY_STEP_3 = 20;
const int STATUS_DESTROY_END    = 0;

Game::Game() {

}

Game::Game(Window _window) : window(_window) {
    this->score = 0;
    this->force_exit = false;

    // Polices

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/consola.ttf", 30);
    this->font = font;
    SDL_Color text_black = { 0, 0, 0, 255 };
    this->text_black = text_black;

    SDL_Color text_white = { 255, 255, 255, 255 };
    this->text_white = text_white;

    // BUG: taille de police n'est pas prise en compte
    TTF_Font *font_title = TTF_OpenFont("fonts/consola.ttf", 120);
    this->font_title = font_title;
    // BUG: couleur rouge ne semble pas marcher
    SDL_Color text_red = { 255, 0, 0, 255 };
    this->text_red = text_red;

    // Sprites

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

    Sprite meteorite_image(0, 245, 60, 60, 0.0, "spritesheets/ship.bmp", pink_background, this->window.renderer);

    if (&meteorite_image != nullptr) {
        this->meteorite_image = meteorite_image;
    }
    else {
        LOGI("Sprite meteorite_image n'a pas pu être crée");
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
        LOGI("Sprite own_ship_image n'a pas pu être crée");
    }

    // Création des sprites pour la destruction de vaisseau
    Sprite destroyed_ship_image_step1(0, 132, 78, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    Sprite destroyed_ship_image_step2(78, 132, 90, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    Sprite destroyed_ship_image_step3(168, 132, 103, 90, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);
    Sprite destroyed_ship_image_step4(0, 0, 0, 0, 0.0, "spritesheets/projectile.bmp", blue_background, this->window.renderer);

    if (&destroyed_ship_image_step1 != nullptr) {
        this->destroyed_ship_image_step1 = destroyed_ship_image_step1;
        this->destroyed_ship_image_step2 = destroyed_ship_image_step2;
        this->destroyed_ship_image_step3 = destroyed_ship_image_step3;
        this->destroyed_ship_image_step4 = destroyed_ship_image_step4;
    }
    else {
        LOGI("Sprite destroyed_ship_image n'a pas pu être créée");
    }

    int screen_width = this->window.get_width();
    int screen_height = this->window.get_height();

    Weapon canon(100, this->missile_image, screen_width, screen_height);

    OwnShip own_ship(200, 550, 100, STATUS_NORMAL, canon, this->own_ship_image,
                                                          this->own_ship_image_left,
                                                          this->own_ship_image_right,
                                                          screen_width, screen_height);
    this->own_ship = own_ship;

    this->music = Mix_LoadMUS("musics/music.wav");

    if (this->music == NULL) {
        LOGI("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }

    this->next_level = false;
}

Game::Game(const Game& _game) {
    score = _game.score;
    font = _game.font;
    window = _game.window;
    own_ship = _game.own_ship;
    missile_image = _game.missile_image;
    meteorite_image = _game.meteorite_image;
    enemy_ship_image = _game.enemy_ship_image;
    own_ship_image = _game.own_ship_image;
    own_ship_image_left = _game.own_ship_image_left;
    own_ship_image_right = _game.own_ship_image_right;
    destroyed_ship_image_step1 = _game.destroyed_ship_image_step1;
    destroyed_ship_image_step2 = _game.destroyed_ship_image_step2;
    destroyed_ship_image_step3 = _game.destroyed_ship_image_step3;
    destroyed_ship_image_step4 = _game.destroyed_ship_image_step4;
    next_level = _game.next_level;
    apocalyse_now = _game.apocalyse_now;
    force_exit = _game.force_exit;
}

Game::~Game() {

}

Window Game::get_window() {
    return this->window;
}

int Game::get_score() {
    return this->score;
}

void Game::set_score(int _points) {
    this->score = _points;
}

int Game::update_score(int _points) {
    return this->score += _points;
}

int Game::get_level() {
    return this->level;
}

void Game::set_level(int _level) {
    this->level = _level;
}

// Affiche le score à l'écran
void Game::render_score() {
    char buffer[10];
    int score = this->score;
    int ret = snprintf(buffer, sizeof(buffer), "Score : %d", score);
    char *text = buffer;

    SDL_Surface *message = TTF_RenderText_Solid(this->font, text, this->text_white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
    int mWidth = message->w;
    int mHeight = message->h;
    SDL_Rect test = { 10, 10, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &test);
}

// Affiche la vie restante à l'écran
void Game::render_life() {
    char buffer[10];
    int number = this->own_ship.get_health();
    int ret = snprintf(buffer, sizeof(buffer), "Vie : %d", number);
    char *text = buffer;

    SDL_Surface *message = TTF_RenderText_Solid(this->font, text, this->text_white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
    int mWidth = message->w;
    int mHeight = message->h;
    SDL_Rect test = { 230, 10, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &test);
}

// Affiche le niveau actuel à l'écran
void Game::render_level() {
    char buffer[11];
    int number = this->get_level();
    int ret = snprintf(buffer, sizeof(buffer), "Niveau : %d", number);
    char *text = buffer;

    SDL_Surface *message = TTF_RenderText_Solid(this->font, text, this->text_white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, message);
    int mWidth = message->w;
    int mHeight = message->h;
    SDL_Rect test = { 440, 10, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &test);
}

// Animation lors d'une destruction
void Game::render_destroy(Ship& _ship) {
    LOGI("Statut du vaisseau (start) : %d", _ship.get_status());

    // On décrémente le statut du vaisseau
    _ship.dec_status( 1 ); // status -= 1;

    // En fonction du statut, on affiche les étapes de l'explosion
    if (_ship.get_status() < STATUS_NORMAL && _ship.get_status() >= STATUS_DESTROY_STEP_1)
    {
        _ship.set_sprite(this->destroyed_ship_image_step1);
    }
    else if (_ship.get_status() < STATUS_DESTROY_STEP_1 && _ship.get_status() >= STATUS_DESTROY_STEP_2)
    {
        _ship.set_sprite(this->destroyed_ship_image_step2);
    }
    else if (_ship.get_status() < STATUS_DESTROY_STEP_2 && _ship.get_status() >= STATUS_DESTROY_STEP_3)
    {
        _ship.set_sprite(this->destroyed_ship_image_step3);
    }
    else if (_ship.get_status() < STATUS_DESTROY_STEP_3 && _ship.get_status() >= STATUS_DESTROY_END)
    {
        _ship.set_sprite(this->destroyed_ship_image_step4);
    }

    LOGI("Statut du vaisseau (end) : %d", _ship.get_status());
}

// Affiche l'écran de Game Over
void Game::render_over() {
    // Fenêtre de dialogue
    SDL_Rect rect = { ((this->window.get_width() / 2) - 225), ((this->window.get_width() / 2) - 320), 450, 250 };
    SDL_SetRenderDrawColor(this->window.renderer, 0, 0, 0, 10); // BUG: opacité ne fonctionne pas...
    SDL_RenderDrawRect(this->window.renderer, &rect);
    SDL_RenderFillRect(this->window.renderer, &rect);

    // Bouton droit de quitter
    rect = { ((this->window.get_width() / 2) - 200), ((this->window.get_width() / 2) - 180), 180, 80 };
    SDL_SetRenderDrawColor(this->window.renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(this->window.renderer, &rect);

    // Bouton gauche de recommencer
    rect = { ((this->window.get_width() / 2) + 20), ((this->window.get_width() / 2) - 180), 180, 80 };
    SDL_SetRenderDrawColor(this->window.renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(this->window.renderer, &rect);

    // Titre de dialogue
    char buffer[70];
    snprintf(buffer, sizeof(buffer), "GAME OVER");
    char *text = buffer;

    SDL_Surface* title = TTF_RenderText_Solid(this->font, text, this->text_red); // BUG: title rouge ne fonctionne pas TOUT le tps
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->window.renderer, title);
    int mWidth = title->w;
    int mHeight = title->h;
    int mX = (this->window.get_width() / 2) - (mWidth/2);
    int mY = (this->window.get_height() / 2) - (mHeight/2) - 50;
    SDL_Rect gameover = { mX, mY, mWidth, mHeight };

    SDL_RenderCopy(this->window.renderer, texture, NULL, &gameover);
}
