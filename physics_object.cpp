#include "physics_object.h"

PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, reactphysics3d::Vector3 halfway_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)
	
{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->position_of_physics_object = initial_position_argument;
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);
	


	if (colliderType == "BOX")
	{
		reactphysics3d::BoxShape* BoxCollision = physComArgument.createBoxShape(halfway_argument);


		// create local transformation matrix for the rigid body collider position
		//reactphysics3d::Transform collider_local;
		reactphysics3d::Transform collider_transform = reactphysics3d::Transform::identity();

		// set the position relative to inside the object itself i.e. local origin
		//transform_local.setPosition(reactphysics3d::Vector3(0.0, 0.0, 0.0));

		// set a orientation local to the collider transformation matrix
		collider_transform.setOrientation(reactphysics3d::Quaternion::identity());


		// REMEMBER THIS TRANSFORMATION MATRIX IS FOR THE COLLIDER NOT FOR THE POSITION OF THE RIGID BODY ITSELF
		// THE RIGID BODY SHOULD BE OF LOCAL ORIGIN 
		this->collider = this->rigid_body->addCollider(BoxCollision, collider_transform);


		reactphysics3d::Material &temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}



}


PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, float height_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)

{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);

	if (colliderType == "CAPSULE")
	{
		reactphysics3d::Transform collider_transform = reactphysics3d::Transform::identity();
		collider_transform.setOrientation(reactphysics3d::Quaternion::identity());


		reactphysics3d::CapsuleShape* CapsuleCollision = physComArgument.createCapsuleShape(radius_argument, height_argument);
		this->collider = this->rigid_body->addCollider(CapsuleCollision, collider_transform);


		reactphysics3d::Material& temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}


}


PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, reactphysics3d::Vector3 initial_position_argument) : material(material)

{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);

	if (colliderType == "SPHERE")
	{

		reactphysics3d::Transform collider_transform = reactphysics3d::Transform::identity();
		collider_transform.setOrientation(reactphysics3d::Quaternion::identity());

		reactphysics3d::SphereShape* SphereCollision = physComArgument.createSphereShape(radius_argument);
		this->collider = this->rigid_body->addCollider(SphereCollision, collider_transform);


		reactphysics3d::Material& temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}
}

PHYSICS_OBJ::PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, reactphysics3d::TriangleVertexArray& vertex_array, reactphysics3d::Vector3 initial_position_argument) : material(material)
{
	this->quarternion = reactphysics3d::Quaternion::identity();
	this->transform.setPosition(initial_position_argument);
	this->transform.setOrientation(this->quarternion);
	this->rigid_body = physWorldArgument->createRigidBody(this->transform);

	if (colliderType == "CONCAVE_MESH")
	{

		reactphysics3d::Transform collider_transform = reactphysics3d::Transform::identity();
		collider_transform.setOrientation(reactphysics3d::Quaternion::identity());

		reactphysics3d::TriangleMesh* mesh = physComArgument.createTriangleMesh(vertex_array, this->messages);

		reactphysics3d::ConcaveMeshShape* ConcaveCollision = physComArgument.createConcaveMeshShape(mesh);

		this->collider = this->rigid_body->addCollider(ConcaveCollision, collider_transform);

		reactphysics3d::Material& temp_material = this->collider->getMaterial();

		this->material = temp_material;
	}
}

PHYSICS_OBJ::~PHYSICS_OBJ()
{
}
