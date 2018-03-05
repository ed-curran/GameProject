#include "SdlInput.h"



SdlInput::SdlInput(SdlInputManager& inputManager) : inputManager(inputManager){
	inputManager.addSdlKeyMapping(SDLK_w, InputRaw::Buttons::BUTTON_KEY_W);
	inputManager.addSdlKeyMapping(SDLK_a, InputRaw::Buttons::BUTTON_KEY_A);
	inputManager.addSdlKeyMapping(SDLK_s, InputRaw::Buttons::BUTTON_KEY_S);
	inputManager.addSdlKeyMapping(SDLK_d, InputRaw::Buttons::BUTTON_KEY_D);

	inputManager.addSdlGameControllerButtonMapping(SDL_CONTROLLER_BUTTON_A, InputRaw::Buttons::BUTTON_CONTROLLER_BUTTON_A);
	inputManager.addSdlGameControllerButtonMapping(SDL_CONTROLLER_BUTTON_B, InputRaw::Buttons::BUTTON_CONTROLLER_BUTTON_B);
	inputManager.addSdlGameControllerButtonMapping(SDL_CONTROLLER_BUTTON_X, InputRaw::Buttons::BUTTON_CONTROLLER_BUTTON_X);
	inputManager.addSdlGameControllerButtonMapping(SDL_CONTROLLER_BUTTON_Y, InputRaw::Buttons::BUTTON_CONTROLLER_BUTTON_Y);

	inputManager.addSdlGameControllerAxesMapping(SDL_CONTROLLER_AXIS_LEFTX, InputRaw::Axes::AXIS_CONTROLLER_AXIS_LEFTX);
	inputManager.addSdlGameControllerAxesMapping(SDL_CONTROLLER_AXIS_LEFTY, InputRaw::Axes::AXIS_CONTROLLER_AXIS_LEFTY);
}


SdlInput::~SdlInput(){
}

void SdlInput::update(){
	controllerContainer.update();

	//loop through controllers and add controler inputs to input manager according
	//to which controller it is
	GameController gameController;
	for (int i = 0; i < MAX_CONTROLLERS; i++) {
		//index has to be in bounds
		if (controllerContainer.connectedController(i, gameController)) {
			InputActors actor = static_cast<InputActors>(i);
			//we just set the actor as the index of controller
			//player1 equals controller with index 1
			inputManager.addSdlGameControllerState(actor, gameController);
		}
	}
}

void SdlInput::handleEvent(SDL_Event& e){
	//keyboard input only goes to player1
	if (inputManager.addSdlKeyEvent(InputActors::INPUT_ACTOR_PLAYER1, e)) { return; }
	if (controllerContainer.handleEvent(e)) { return; }
	//handle controller events
}
