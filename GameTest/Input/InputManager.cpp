#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::clearRawInput(){
	for (int actor = 0; actor < InputActors::INPUT_ACTOR_MAX; actor++) {
		inputMappers[actor].clear();
	}
}

void InputManager::clearMappedInput(){
	for (int actor = 0; actor < InputActors::INPUT_ACTOR_MAX; actor++) {
		inputMappers[actor].clearMappedInput();
	}
}

void InputManager::addInputContext(InputActors actor, std::string contextName, InputContext context){
	inputMappers[actor].addInputContext(contextName, context);
}

void InputManager::addButtonDown(InputActors actor, InputRaw::Buttons button, bool keyRepeat){
	inputMappers[actor].addButtonDown(button, keyRepeat);
}

void InputManager::addButtonUp(InputActors actor, InputRaw::Buttons button){
	inputMappers[actor].addButtonUp(button);
}

void InputManager::addAxisValue(InputActors actor, InputRaw::Axes axis, float value){
	inputMappers[actor].addAxisValue(axis, value);
}

void InputManager::activateActor(InputActors actor){
	inputActorsActive[actor] = true;
}

void InputManager::deactivateActor(InputActors actor){
	inputActorsActive[actor] = false;
}

MappedInput& InputManager::getMappedInput(InputActors actor){
	return inputMappers[actor].getMappedInput();
}

void InputManager::performMapping(){
	for (int actor = 0; actor < InputActors::INPUT_ACTOR_MAX; actor++){
		if(inputActorsActive[actor]){
			inputMappers[actor].dispatch();
		}
	}
}