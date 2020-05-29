/* TEXT.h
 *   by Anonymous
 *
 * Created:
 *   5/29/2020, 2:48:57 PM
 * Last edited:
 *   5/29/2020, 4:58:11 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The text class provides the baseclass for all text-related
 *   GameObjects. It provides a uniform way of drawing and stores values
 *   for the font, font size and colour.
**/

#ifndef TEXT_INCLUDED
#define TEXT_INCLUDED

#include <string>
#include <SDL2/SDL_ttf.h>

#include "GameObject.h"
#include "Coord.h"
#include "MySDL.h"

class Text: public GameObject {
    protected:
        TTF_Font* font;
        
        SDL_Texture* texture;
        Coord size;

        /*! Create a new Text object with default position and given message
          @param mySDL the SDL window to render on
          @param message the message this Text object displays
          @param font_family the font family to render in
          @param font_size the size of the font
          @param colour the colour to render in
         */
        Text(MySDL& mySDL, std::string message, std::string font_family, unsigned int font_size, Color colour)
            : GameObject(GameObjectType::text),
            texture(nullptr),
            font(TTF_OpenFont(font_family.c_str(), font_size))
        {
            if (this->font == nullptr) {
                throw std::runtime_error("Could not load font \"" + font_family + "\".");
            }

            this->initialize_texture(mySDL, message, colour);
        }

        /*! Create a new Text object with given position
          @param mySDL the SDL window to render on
          @param position the position of the text
          @param message the message this Text object displays
          @param font_family the font family to render in
          @param font_size the size of the font
          @param colour the colour to render in
         */
        Text(MySDL& mySDL, Coord position, std::string message, std::string font_family, unsigned int font_size, Color colour)
            : GameObject(position, GameObjectType::text),
            texture(nullptr),
            font(TTF_OpenFont(font_family.c_str(), font_size))
        {
            if (this->font == nullptr) {
                throw std::runtime_error("Could not load font \"" + font_family + "\".");
            }

            this->initialize_texture(mySDL, message, colour);
        }

    public:
        /*! Destructor for the Text class.
         */
        ~Text() {
            if (this->texture != nullptr) {
                SDL_DestroyTexture(this->texture);
            }
        }

        /*! Default updater, which does nothing
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8* keyboardState, GameState& objects)
        {}

        /*! Draws the text, with pos being the center of it.
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Create a rectangle
            SDL_Rect rect;
            rect.x = this->pos.x - this->size.x / 2;
            rect.y = this->pos.y - this->size.y / 2;
            rect.w = this->size.x;
            rect.h = this->size.y;

            SDL_RenderCopy(mySDL.renderer(), this->texture, NULL, &rect);
        }

        /*! Initializes the texture for the text. Can be used to change the text displayed.
          @param message the message to draw.
         */
        void initialize_texture(MySDL& mySDL, std::string message, Color colour) {
            // If there is any texture, remove it first
            if (this->texture != nullptr) {
                SDL_DestroyTexture(this->texture);
            }

            // Create a SDL_Color from Color
            Uint8* c_list = (Uint8*) &colour;
            SDL_Color sdl_colour;
            sdl_colour.r = c_list[0];
            sdl_colour.g = c_list[1];
            sdl_colour.b = c_list[2];
            sdl_colour.a = c_list[3];

            std::cout << "Colour: " << ((int) sdl_colour.r) << ", " << ((int) sdl_colour.g) << ", " << ((int) sdl_colour.b) << ", " << ((int) sdl_colour.a) << std::endl;

            SDL_Surface* surface = TTF_RenderText_Solid(this->font, message.c_str(), sdl_colour);
            this->texture = SDL_CreateTextureFromSurface(mySDL.renderer(), surface);
            
            // Store the width and height in the rectangle
            this->size.x = surface->w;
            this->size.y = surface->h;

            // Cleanup the surface
            SDL_FreeSurface(surface);
        }
};

#endif
