/*
 * Author: Ed Curran (b15021040)
 * Class: InputManager
 * Extends: InputMapper
 * Description: provides functions to convert from sdl input 
 * into our raw input and add to the underlying InputManager
 * 
 * This is basically another mapping layer
 * to map from sdl inputs to engine raw inputs
 */

#pragma once
#include "../Input/InputManager.h"
#include "GameController.h"
#include <SDL.h>



class SdlInputManager :
	public InputManager
{
public:
	SdlInputManager();
	~SdlInputManager();

	bool addSdlKeyMapping(SDL_Keycode sdlKey, InputRaw::Buttons rawInputButton);
	bool addSdlGameControllerButtonMapping(SDL_GameControllerButton sdlButton, InputRaw::Buttons rawInputButton);
	bool addSdlGameControllerAxesMapping(SDL_GameControllerAxis sdlAxes, InputRaw::Axes rawInputAxes);

	bool addSdlKeyEvent(InputActors actor, SDL_Event &e);
	bool addSdlKeyUp(InputActors actor, SDL_Keycode keycode);
	bool addSdlKeyDown(InputActors actor, SDL_Keycode keycode, bool keyRepeat);

	
	void addSdlGameControllerState(InputActors actor, GameController& controller);
protected:
	bool mapSdlKeyToButton(SDL_Keycode keycode, InputRaw::Buttons& outButtonId);
	bool mapSdlControllerButtonToButton(SDL_GameControllerButton controllerButton, InputRaw::Buttons& outButtonId);
	bool mapSdlControllerAxesToAxes(SDL_GameControllerAxis controllerAxes, InputRaw::Axes& outAxesId);


	std::map<SDL_Keycode, InputRaw::Buttons>::iterator i;

	//mapping between sdl keys and engine raw input buttons
	std::map<SDL_Keycode, InputRaw::Buttons> sdlKeyMap;

	//mapping between sdl game controller buttons to raw input buttons
	std::map<SDL_GameControllerButton, InputRaw::Buttons> sdlGameControllerButtonMap;

	//mapping between sdl game controller axes to raw input axes
	std::map<SDL_GameControllerAxis, InputRaw::Axes> sdlGameControllerAxesMap;
};
