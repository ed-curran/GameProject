#include "SceneNode.h"

SceneNode::SceneNode(Mesh*mesh, Vector4 colour)	{
	awake				= true;
	this->mesh			= mesh;
	this->colour		= colour;
	parent				= NULL;
	boundingRadius		= 100.0f;
	distanceFromCamera	= 0.0f;
	
	modelScale			= Vector3(1,1,1);
}

SceneNode::~SceneNode(void)	{
	for(unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void SceneNode::AddChild( SceneNode* s )	{
	children.push_back(s);
	s->parent = this;
}

bool	SceneNode::CompareByCameraDistance(SceneNode*a,SceneNode*b)  {
	return (a->distanceFromCamera < b->distanceFromCamera) ? true : false;
}

bool	SceneNode::CompareByZ(SceneNode*a,SceneNode*b)  {
	return (a->GetWorldTransform().GetPositionVector().z < b->GetWorldTransform().GetPositionVector().z) ? true : false;
}

void	SceneNode::Update(float msec)	 {
	if(parent) {
		SetModelScale(physicsData->scale);
		SetTransform(Matrix4::Translation(physicsData->position)*Matrix4::Rotation(physicsData->rotation, Vector3(0, 0, 1)));
		worldTransform = parent->worldTransform * transform;
	}
	else{
		worldTransform = transform;
	}

	for(vector<SceneNode*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}

bool SceneNode::RemoveChild(SceneNode* s,bool recursive) {

	for(auto i = children.begin(); i != children.end(); ++i) {
		if((*i) == s) {
			i = children.erase(i);
			return true;
		}
	}

	if(recursive) {
		for(auto i = children.begin(); i != children.end(); ++i) {
			if((*i)->RemoveChild(s,recursive)) {
				return true;
			}
		}
	}
	return false;
}