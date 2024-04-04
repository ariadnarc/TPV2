// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <bitset>
#include <cassert>
#include <vector>

#include "Component.h"
#include "ecs.h"

namespace ecs {

/*
 * A class that represents a collection of components.
 *
 */

class Entity {
public:
	Entity(ecs::grpId_t gId, Manager *mngr) :
			mngr_(mngr), //
			cmps_(), //
			currCmps_(), //
			alive_(),  //
			gId_(gId) //
	{
		// We reserve the a space for the maximum number of
		// components. This way we avoid resizing the vector.
		//
		currCmps_.reserve(ecs::maxComponentId);
	}

	// we delete the copy constructor/assignment because it is
	// not clear how to copy the components
	//
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	// Exercise: define move constructor/assignment for class Entity

	// Destroys the entity
	//
	virtual ~Entity() {

		// we delete all available components
		//
		for (auto c : currCmps_)
			delete c;
	}

	// Returns the manager to which this entity belongs
	inline Manager* getMngr() {
		return mngr_;
	}

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(bool alive) {
		alive_ = alive;
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive() {
		return alive_;
	}

	// Updating  an entity simply calls the update of all
	// components
	//
	void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}

	// Rendering an entity simply calls the render of all
	// components
	//
	void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}

	// Adds a component. It receives the type T (to be created), and the
	// list of arguments (if any) to be passed to the constructor.
	//
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts &&... args) {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		// delete the current component, if any
		//
		removeComponent<T>();

		// create, initialise and install the new component
		//
		Component *c = new T(std::forward<Ts>(args)...);
		c->setContext(this);
		c->initComponent();
		cmps_[cId] = c;
		currCmps_.push_back(c);

		// return it to the user so i can be initialised if needed
		return static_cast<T*>(c);
	}

	// Removes the component T
	//
	template<typename T>
	inline void removeComponent() {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		if (cmps_[cId] != nullptr) {

			// find the element that is equal tocmps_[cId] (returns an iterator)
			//
			auto iter = std::find(currCmps_.begin(), currCmps_.end(),
					cmps_[cId]);

			// must have such a component
			assert(iter != currCmps_.end());

			// and then remove it
			currCmps_.erase(iter);

			// destroy it
			//
			delete cmps_[cId];

			// remove the pointer
			//
			cmps_[cId] = nullptr;
		}
	}

	// Returns the component that corresponds to T, casting it
	// to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent() {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		return static_cast<T*>(cmps_[cId]);
	}

	// return true if there is a componentT
	//
	template<typename T>
	inline bool hasComponent() {

		// the component id
		constexpr cmpId_t cId = cmpId<T>;
		static_assert(cId < ecs::maxComponentId);

		return cmps_[cId] != nullptr;
	}

	// returns the entity's group 'gId'
	//
	inline ecs::grpId_t groupId() {
		return gId_;
	}


private:
	// the fields currCmps_ can be removed, and instead we can traverse cmps_
	// and process non-null elements. We keep it because sometimes the order
	// in which the components are executed is important

	Manager *mngr_;
	std::array<Component*, maxComponentId> cmps_;
	std::vector<Component*> currCmps_;
	bool alive_;
	ecs::grpId_t gId_;
};

} // end of name space
