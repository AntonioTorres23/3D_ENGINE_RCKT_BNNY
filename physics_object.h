#ifndef PHYSICS_OBJECT_HEADER
#define PHYSICS_OBJECT_HEADER

#include <reactphysics3d/reactphysics3d.h>
#include <iostream>
#include <string>

class PHYSICS_OBJ
{
public:

	PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, reactphysics3d::Vector3 halfway_argument, reactphysics3d::Vector3 initial_position_argument);

	PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, float height_argument, reactphysics3d::Vector3 initial_position_argument);

	PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, float radius_argument, reactphysics3d::Vector3 initial_position_argument);

	PHYSICS_OBJ(reactphysics3d::PhysicsCommon& physComArgument, reactphysics3d::PhysicsWorld* physWorldArgument, std::string colliderType, reactphysics3d::TriangleVertexArray& vertex_array, reactphysics3d::Vector3 initial_position_argument);

	PHYSICS_OBJ();

	~PHYSICS_OBJ();

	reactphysics3d::Collider* collider;

	reactphysics3d::Material material;

	reactphysics3d::Vector3 position_of_physics_object;

	reactphysics3d::RigidBody* rigid_body;

	reactphysics3d::Quaternion quarternion; 

	reactphysics3d::Transform transform;

	std::vector<reactphysics3d::Message> messages;

};


#endif // !PHYISCS_OBJECT_HEADER

