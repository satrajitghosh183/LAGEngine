#pragma once

#include "RigidBody.hpp"
#include "CollisionShape.hpp"
#include "SphereShape.hpp"
#include "BoxShape.hpp"
#include "../core/Time.hpp"
#include <vector>
#include <memory>
#include <functional>

namespace engine::physics {

struct ContactPoint {
    glm::vec3 position;
    glm::vec3 normal;
    float penetration;
    RigidBody* bodyA;
    RigidBody* bodyB;
    
    ContactPoint() : penetration(0.0f), bodyA(nullptr), bodyB(nullptr) {}
};

struct CollisionPair {
    RigidBody* bodyA;
    RigidBody* bodyB;
    
    CollisionPair(RigidBody* a, RigidBody* b) : bodyA(a), bodyB(b) {}
    
    bool operator==(const CollisionPair& other) const {
        return (bodyA == other.bodyA && bodyB == other.bodyB) ||
               (bodyA == other.bodyB && bodyB == other.bodyA);
    }
};

/**
 * @brief Main physics simulation world
 * Manages rigid bodies, collision detection, and integration
 */
class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld();

    // World management
    void update(float dt);
    void clear();

    // Body management
    void addRigidBody(std::shared_ptr<RigidBody> body);
    void removeRigidBody(std::shared_ptr<RigidBody> body);
    const std::vector<std::shared_ptr<RigidBody>>& getRigidBodies() const { return rigidBodies; }

    // Global physics properties
    void setGravity(const glm::vec3& gravity) { this->gravity = gravity; }
    const glm::vec3& getGravity() const { return gravity; }

    // Simulation settings
    void setTimeStep(float timeStep) { fixedTimeStep = timeStep; }
    float getTimeStep() const { return fixedTimeStep; }
    
    void setMaxSubSteps(int maxSteps) { maxSubSteps = maxSteps; }
    int getMaxSubSteps() const { return maxSubSteps; }

    // Raycasting
    bool raycast(const Ray& ray, RaycastHit& hit) const;
    std::vector<RaycastHit> raycastAll(const Ray& ray) const;

    // Collision queries
    std::vector<RigidBody*> getOverlappingBodies(const BoundingBox& aabb) const;
    bool checkOverlap(RigidBody* bodyA, RigidBody* bodyB) const;

    // Debug information
    const std::vector<ContactPoint>& getContactPoints() const { return contactPoints; }
    int getContactCount() const { return contactPoints.size(); }

    // Events
    std::function<void(RigidBody*, RigidBody*, const ContactPoint&)> onCollisionEnter;
    std::function<void(RigidBody*, RigidBody*, const ContactPoint&)> onCollisionStay;
    std::function<void(RigidBody*, RigidBody*)> onCollisionExit;

private:
    // Physics state
    std::vector<std::shared_ptr<RigidBody>> rigidBodies;
    std::vector<ContactPoint> contactPoints;
    std::vector<CollisionPair> activePairs;
    std::vector<CollisionPair> newPairs;
    
    glm::vec3 gravity{0.0f, -9.81f, 0.0f};
    float fixedTimeStep = 1.0f / 60.0f;
    int maxSubSteps = 10;
    float accumulator = 0.0f;

    // Collision detection
    void broadPhaseCollision();
    void narrowPhaseCollision();
    bool detectCollision(RigidBody* bodyA, RigidBody* bodyB, ContactPoint& contact);
    
    // Specific collision detection functions
    bool sphereVsSphere(RigidBody* bodyA, RigidBody* bodyB, ContactPoint& contact);
    bool boxVsBox(RigidBody* bodyA, RigidBody* bodyB, ContactPoint& contact);
    bool sphereVsBox(RigidBody* bodyA, RigidBody* bodyB, ContactPoint& contact);

    // Collision response
    void resolveCollisions();
    void resolveContact(const ContactPoint& contact);
    void separateBodies(const ContactPoint& contact);

    // Integration
    void integrateForces(float dt);
    void integrateBodies(float dt);

    // Utility
    Transform getRigidBodyTransform(RigidBody* body) const;
    void updateCollisionEvents();
    bool pairExists(const CollisionPair& pair, const std::vector<CollisionPair>& pairs) const;
};

} // namespace engine::physics