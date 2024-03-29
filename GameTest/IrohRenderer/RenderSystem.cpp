#include "RenderSystem.h"




RenderComponent* RenderSystem::createRenderComponent(SimpleTransform* transform, SpriteRenderable& spriteComponent){
	if(transform == nullptr){
		//can't create render component without parent transform
		return nullptr;
	}
	if (numRenderComponents > MAX_SPRITE_COMPONENTS) {
		cout << "exceeded render components pool size";
		return nullptr;
	}
	numRenderComponents++;
	RenderComponent* r = renderComponentPool.newElement(transform, spriteComponent);
	/*RenderComponent* r = renderComponentPool.allocate();
	r->sprite = spriteComponent;*/

	return r;
}

void RenderSystem::deleteRenderComponent(RenderComponent* component){
	numRenderComponents--;
	renderComponentPool.deallocate(component);
}

void RenderSystem::updateTransforms(){
	renderer.clearSprites();
	RenderComponent* freeSlot = renderComponentPool.firstFree();
	for (RenderComponent* r = renderComponentPool.first(); r != nullptr; r = renderComponentPool.next(r, freeSlot)) {
		r->sprite.position = r->transform->position;
		r->sprite.rotation = r->transform->rotation;
		r->sprite.scale = Vector3(r->transform->scale.x, r->transform->scale.y, r->sprite.scale.z);
		renderer.addSpriteToDrawList(&(r->sprite));
	}
}

void RenderSystem::update(float msec, ContentManager& contentManager) {
	updateTransforms();
	renderer.UpdateScene(msec, contentManager);
}

void RenderSystem::renderScene(){
	renderer.RenderScene();
}

//RenderComponent* RenderSystem::createRenderComponent(RenderComponent& component){
//	RenderComponent* c = renderComponentPool.allocate();
//	c = &component;
//}
