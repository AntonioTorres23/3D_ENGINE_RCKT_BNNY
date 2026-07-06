#include "physics_object.h"

PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, reactphysics3d::Vector3 halfway_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)
	
{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);
	
	if (colliderType == "BOX")
	{
		reactphysics3d::BoxShape* BoxCollision = physComArgument.createBoxShape(halfway_argument);
		this->collider = this->rigid_body->addCollider(BoxCollision, transform);


		reactphysics3d::Material &temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}



}


PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, float height_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)

{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);

	if (colliderType == "CAPSULE")
	{
		reactphysics3d::CapsuleShape* CapsuleCollision = physComArgument.createCapsuleShape(radius_argument, height_argument);
		this->collider = this->rigid_body->addCollider(CapsuleCollision, transform);


		reactphysics3d::Material& temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}


}


PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)

{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);

	if (colliderType == "SPHERE")
	{
		reactphysics3d::SphereShape* SphereCollision = physComArgument.createSphereShape(radius_argument);
		this->collider = this->rigid_body->addCollider(SphereCollision, transform);


		reactphysics3d::Material& temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}
}