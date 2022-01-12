////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/scene/Scene.h"
#include "IME/core/engine/Engine.h"
#include "IME/core/physics/PhysicsWorld.h"

namespace ime {
    Scene::Scene() :
        timescale_{1.0f},
        isEntered_{false},
        isVisibleWhenPaused_{false},
        isTimeUpdatedWhenPaused_{false},
        isEventUpdatedWhenPaused_{false},
        hasPhysicsSim_{false},
        hasTilemap_{false},
        cacheState_{false, ""},
        spriteContainer_{std::make_unique<SpriteContainer>(renderLayers_)},
        entityContainer_{std::make_unique<GameObjectContainer>(renderLayers_)},
        shapeContainer_{std::make_unique<ShapeContainer>(renderLayers_)}
    {
        renderLayers_.create("default");
    }

    Scene::Scene(Scene&& other) noexcept {
        *this = std::move(other);
    }

    Scene &Scene::operator=(Scene&& other) noexcept {
        // We can't use a default move assignment operator because of reference members
        if (this != &other) {
            Object::operator=(std::move(other));
            engine_ = std::move(other.engine_);
            window_ = std::move(other.window_);
            camera_ = std::move(other.camera_);
            cache_ = std::move(other.cache_);
            sCache_ = std::move(other.sCache_);
            world_ = std::move(other.world_);
            inputManager_ = std::move(other.inputManager_);
            audioManager_ = std::move(other.audioManager_);
            eventEmitter_ = std::move(other.eventEmitter_);
            internalEmitter_ = std::move(other.internalEmitter_);
            timerManager_ = std::move(other.timerManager_);
            guiContainer_ = std::move(other.guiContainer_);
            renderLayers_ = std::move(other.renderLayers_);
            entityContainer_ = std::move(other.entityContainer_);
            gridMovers_ = std::move(other.gridMovers_);
            shapeContainer_ = std::move(other.shapeContainer_);
            tileMap_ = std::move(other.tileMap_);
            timescale_ = other.timescale_;
            isVisibleWhenPaused_ = other.isVisibleWhenPaused_;
            isTimeUpdatedWhenPaused_ = other.isTimeUpdatedWhenPaused_;
            isEventUpdatedWhenPaused_ = other.isEventUpdatedWhenPaused_;
            hasPhysicsSim_ = other.hasPhysicsSim_;
            hasTilemap_ = other.hasTilemap_;
            cacheState_ = other.cacheState_;
            isEntered_ = false;
        }

        return *this;
    }

    Scene::Ptr Scene::create() {
        return std::make_unique<Scene>();
    }

    void Scene::init(Engine &engine) {
        engine_ = std::make_unique<std::reference_wrapper<Engine>>(engine);
        window_ = std::make_unique<std::reference_wrapper<Window>>(engine.getWindow());
        cameraContainer_ = std::make_unique<CameraContainer>(engine.getRenderTarget());
        camera_ = std::make_unique<Camera>(engine.getRenderTarget());
        cache_ = std::make_unique<std::reference_wrapper<PropertyContainer>>(engine.getPersistentData());
        sCache_ = std::make_unique<std::reference_wrapper<PrefContainer>>(engine.getSavablePersistentData());
        guiContainer_.setTarget(engine.getRenderTarget());
        onInit();
    }

    bool Scene::unsubscribe_(const std::string &event, int id) {
        return internalEmitter_.removeEventListener(event, id);
    }

    std::string Scene::getClassName() const {
        return "Scene";
    }

    void Scene::setOnPauseAction(Uint32 action) {
        if (action & OnPauseAction::Default) {
            isVisibleWhenPaused_ = false;
            isEventUpdatedWhenPaused_ = false;
            isTimeUpdatedWhenPaused_ = false;
            return;
        }

        if (action & OnPauseAction::Show)
            isVisibleWhenPaused_ = true;
        else
            isVisibleWhenPaused_ = false;

        if (action & OnPauseAction::UpdateAll) {
            isEventUpdatedWhenPaused_ = true;
            isTimeUpdatedWhenPaused_ = true;
            return;
        } else {
            isEventUpdatedWhenPaused_ = false;
            isTimeUpdatedWhenPaused_ = false;
        }

        if (action & OnPauseAction::UpdateTime)
            isTimeUpdatedWhenPaused_ = true;
        else
            isTimeUpdatedWhenPaused_ = false;

        if (action & OnPauseAction::UpdateSystem)
            isEventUpdatedWhenPaused_ = true;
        else
            isEventUpdatedWhenPaused_ = false;
    }

    void Scene::setInputEnable(bool enable) {
        if (enable && input().isAllInputEnabled() || !enable && input().isAllInputDisabled())
            return;

        input().setAllInputEnable(enable);
        emitChange(Property{"inputEnable", enable});
    }

    bool Scene::isInputEnabled() const {
        return input().isAllInputEnabled();
    }

    void Scene::setCached(bool cache, const std::string& alias) {
        cacheState_.first = cache;
        cacheState_.second = alias;
    }

    bool Scene::isCached() const {
        return cacheState_.first;
    }

    bool Scene::isVisibleOnPause() const {
        return isVisibleWhenPaused_;
    }

    bool Scene::isEntered() const {
        return isEntered_;
    }

    void Scene::setTimescale(float timescale) {
        if (timescale_ == timescale)
            return;

        if (timescale < 0)
            timescale_ = 0.0f;
        else
            timescale_ = timescale;

        emitChange(Property{"timescale", timescale});
    }

    float Scene::getTimescale() const {
        return timescale_;
    }

    Engine &Scene::engine() {
        return *engine_;
    }

    const Engine &Scene::engine() const {
        return *engine_;
    }

    Window &Scene::window() {
        return *window_;
    }

    const Window &Scene::window() const {
        return *window_;
    }

    Camera &Scene::camera() {
        return *camera_;
    }

    const Camera &Scene::camera() const {
        return *camera_;
    }

    CameraContainer &Scene::cameras() {
        return *cameraContainer_;
    }

    const CameraContainer &Scene::cameras() const {
        return *cameraContainer_;
    }

    PhysicsWorld& Scene::physWorld() {
        return *world_;
    }

    const PhysicsWorld& Scene::physWorld() const {
        return *world_;
    }

    GridMoverContainer &Scene::gridMovers() {
        return gridMovers_;
    }

    const GridMoverContainer &Scene::gridMovers() const {
        return gridMovers_;
    }

    input::InputManager &Scene::input() {
        return inputManager_;
    }

    const input::InputManager &Scene::input() const {
        return inputManager_;
    }

    audio::AudioManager &Scene::audio() {
        return audioManager_;
    }

    const audio::AudioManager &Scene::audio() const {
        return audioManager_;
    }

    TimerManager &Scene::timer() {
        return timerManager_;
    }

    const TimerManager &Scene::timer() const {
        return timerManager_;
    }

    EventEmitter &Scene::eventEmitter() {
        return eventEmitter_;
    }

    const EventEmitter &Scene::eventEmitter() const {
        return eventEmitter_;
    }

    EventDispatcher &Scene::globalEventEmitter() {
        return *EventDispatcher::instance();
    }

    PropertyContainer &Scene::cache() {
        return *cache_;
    }

    const PropertyContainer &Scene::cache() const {
        return *cache_;
    }

    PrefContainer &Scene::sCache() {
        return *sCache_;
    }

    const PrefContainer &Scene::sCache() const {
        return *sCache_;
    }

    RenderLayerContainer &Scene::renderLayers() {
        return renderLayers_;
    }

    const RenderLayerContainer &Scene::renderLayers() const {
        return renderLayers_;
    }

    TileMap &Scene::tilemap() {
        return *tileMap_;
    }

    const TileMap &Scene::tilemap() const {
        return *tileMap_;
    }

    ui::GuiContainer &Scene::gui() {
        return guiContainer_;
    }

    const ui::GuiContainer &Scene::gui() const {
        return guiContainer_;
    }

    ShapeContainer &Scene::shapes() {
        return *shapeContainer_;
    }

    const ShapeContainer &Scene::shapes() const {
        return *shapeContainer_;
    }

    GameObjectContainer &Scene::gameObjects() {
        return *entityContainer_;
    }

    const GameObjectContainer &Scene::gameObjects() const {
        return *entityContainer_;
    }

    SpriteContainer &Scene::sprites() {
        return *spriteContainer_;
    }

    const SpriteContainer &Scene::sprites() const {
        return *spriteContainer_;
    }

    void Scene::createPhysWorld(const Vector2f& gravity, const PhysIterations& iterations) {
        world_ = PhysicsWorld::create(*this, gravity);
        world_->setIterations(iterations);
        world_->createDebugDrawer(engine().getRenderTarget());
        hasPhysicsSim_ = true;

        if (hasTilemap_)
            tileMap_->setPhysicsSimulation(world_.get());
    }

    void Scene::createTilemap(unsigned int tileWidth, unsigned int tileHeight) {
        tileMap_ = std::make_unique<TileMap>(tileWidth, tileHeight, renderLayers(), *this);
        if (hasPhysicsSim_)
            tileMap_->setPhysicsSimulation(world_.get());

        hasTilemap_ = true;
    }

    Scene::~Scene() {
        emit("destruction");
    }
}