#pragma once
#include "InputMapper.h"

/*
 * Author: Ed Curran (b15021040)
 * Class: InputManager
 * Description: Manages collecting and mapping raw input on behalf of specified input actors
 * 
 * raw input can be pushed to the input manager and marked as belonging to a particular input actor
 * Each actor then maps its raw input into an InputMapped instance
 * Can then access the mapped input belonging to a particular actor 
 * callbacks can be registered to recieve the mapped input from a particular actor (or combination of actors if i get round to that)
 * 
 * In reality this is basically just a wrapper around a collection of InputMappers
 * with each InputMapper corrosponding to an Actor
 * but I may change the implementation underneath pretty heavily so this is a pretty verbose wrapper because
 * 
 * E N C A P S U L A T I O N
 * N
 * C
 * A
 * P
 * S
 * U
 * L
 * A
 * T
 * I
 * N
 * 
 * As at this level we are exclusively working with our engine defined raw input
 * it means the input manager / mapping system is independent of any particular input library / collection method
 * 
 * Extend this class to facilitate collecting a wide range of input
 * eg could be extended to take sdlKey inputs
 * or nclgl keyboard 
 * 
 *  
 * 
 */
enum InputActors{
	INPUT_ACTOR_PLAYER1,
	INPUT_ACTOR_PLAYER2,
	INPUT_ACTOR_PLAYER3,
	INPUT_ACTOR_PLAYER4,
	INPUT_ACTOR_MAX,
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void clearRawInput();
	void clearMappedInput();

	//each actor (input mapper) can still have multiple input contexts
	//yeah you heard me. This might end up being overkill but
	//actors are a seperate concept from input contexts
	//eg actor 1 may have weapon a equiped and actor 2 weapon b
	//and so have different input contexts

	void addInputContext(InputActors actor, std::string contextName, InputContext context);

	void activateActor(InputActors actor);
	void deactivateActor(InputActors actor);
	/*
	 * Send raw input to actors
	 */

	void addButtonDown(InputActors actor, InputRaw::Buttons button, bool keyRepeat);
	void addButtonUp(InputActors actor, InputRaw::Buttons button);
	void addAxisValue(InputActors actor, InputRaw::Axes axis, float value);

	/*
	 * get resultant cooked input from actor
	 */
	MappedInput& getMappedInput(InputActors actor);

	/*
	 * map raw input to cooked input
	 */
	void performMapping();

	/*
	 * I don't really know how this is gunno work yet
	 * TODO: figure out how we're gunno implement this
	 */
	void registerCallback(InputActors actor);

protected:
	InputMapper inputMappers[INPUT_ACTOR_MAX];
	bool inputActorsActive[INPUT_ACTOR_MAX];
};
