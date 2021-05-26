////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_CORE_H
#define IME_CORE_H

////////////////////////////////////////////////////////////////////////////////
// Includes all the core headers
////////////////////////////////////////////////////////////////////////////////

#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/common/Transform.h"
#include "IME/common/ITransformable.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Property.h"
#include "IME/common/PropertyContainer.h"
#include "IME/core/animation/Animation.h"
#include "IME/core/animation/Animator.h"
#include "IME/core/audio/SoundEffect.h"
#include "IME/core/audio/Music.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/core/event/Event.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/event/EventDispatcher.h"
#include "IME/core/exceptions/Exceptions.h"
#include "IME/core/input/InputManager.h"
#include "IME/core/input/Mouse.h"
#include "IME/core/input/Keyboard.h"
#include "IME/core/engine/Engine.h"
#include "IME/core/physics/grid/path/BFS.h"
#include "IME/core/physics/grid/path/DFS.h"
#include "IME/core/physics/rigid_body/AABB.h"
#include "IME/core/physics/rigid_body/RigidBody.h"
#include "IME/core/physics/rigid_body/colliders/Collider.h"
#include "IME/core/physics/rigid_body/colliders/BoxCollider.h"
#include "IME/core/physics/rigid_body/colliders/CircleCollider.h"
#include "IME/core/physics/rigid_body/colliders/PolygonCollider.h"
#include "IME/core/physics/rigid_body/colliders/EdgeCollider.h"
#include "IME/core/physics/rigid_body/joints/Joint.h"
#include "IME/core/physics/rigid_body/joints/JointDefinition.h"
#include "IME/core/physics/rigid_body/joints/DistanceJoint.h"
#include "IME/core/physics/grid/GridMover.h"
#include "IME/core/physics/grid/KeyboardGridMover.h"
#include "IME/core/physics/grid/RandomGridMover.h"
#include "IME/core/physics/grid/TargetGridMover.h"
#include "IME/core/physics/PhysicsWorld.h"
#include "IME/core/resources/ResourceLoader.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/scene/DrawableContainer.h"
#include "IME/core/scene/GameObjectContainer.h"
#include "IME/core/tilemap/Index.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/core/time/Clock.h"
#include "IME/core/time/Time.h"
#include "IME/core/time/Timer.h"
#include "IME/core/time/TimerManager.h"

#endif //IME_CORE_H
