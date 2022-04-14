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
#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/core/exceptions/Exceptions.h"

namespace ime {
    Scene::Scene() :
        timescale_{1.0f},
        isEntered_{false},
        isInitialized_{false},
        isPaused_{false},
        isVisibleWhenPaused_{false},
        isBackgroundSceneUpdated_{true},
        isBackgroundSceneEventsEnabled_{false},
        hasPhysicsSim_{false},
        hasGrid2D_{false},
        cacheState_{false, ""},
        parentScene_{nullptr},
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
            grid2D_ = std::move(other.grid2D_);
            timescale_ = other.timescale_;
            isVisibleWhenPaused_ = other.isVisibleWhenPaused_;
            isBackgroundSceneUpdated_ = other.isBackgroundSceneUpdated_;
            isBackgroundSceneEventsEnabled_ = other.isBackgroundSceneEventsEnabled_;
            hasPhysicsSim_ = other.hasPhysicsSim_;
            hasGrid2D_ = other.hasGrid2D_;
            cacheState_ = other.cacheState_;
            isEntered_ = other.isEntered_;
            isInitialized_ = other.isInitialized_;
            isPaused_ = other.isPaused_;
            parentScene_ = other.parentScene_;
            backgroundScene_ = std::move(other.backgroundScene_);
        }

        return *this;
    }

    Scene::Ptr Scene::create() {
        return std::make_unique<Scene>();
    }

    void Scene::init(Engine &engine) {
        if (!isInitialized_) {
            isInitialized_ = true;
            engine_ = std::make_unique<std::reference_wrapper<Engine>>(engine);
            window_ = std::make_unique<std::reference_wrapper<Window>>(engine.getWindow());
            cameraContainer_ = std::make_unique<CameraContainer>(engine.getRenderTarget());
            camera_ = std::make_unique<Camera>(engine.getRenderTarget());
            cache_ = std::make_unique<std::reference_wrapper<PropertyContainer>>(engine.getCache());
            sCache_ = std::make_unique<std::reference_wrapper<PrefContainer>>(engine.getSavableCache());
            guiContainer_.setTarget(engine.getRenderTarget());
            onInit();
        }
    }

    bool Scene::unsubscribe_(const std::string &event, int id) {
        return internalEmitter_.removeEventListener(event, id);
    }

    std::string Scene::getClassName() const {
        return "Scene";
    }

    void Scene::setCached(bool cache, const std::string& alias) {
        cacheState_.first = cache;
        cacheState_.second = alias;
    }

    bool Scene::isCached() const {
        return cacheState_.first;
    }

    void Scene::setVisibleOnPause(bool visible) {
        if (isVisibleWhenPaused_ != visible) {
            isVisibleWhenPaused_ = visible;

            emitChange(Property("visibleOnPause", isVisibleWhenPaused_));
        }
    }

    bool Scene::isVisibleOnPause() const {
        return isVisibleWhenPaused_;
    }

    void Scene::setBackgroundScene(Scene::Ptr scene) {
        if (!isInitialized_)
            throw AccessViolationException("ime::Scene::setBackgroundScene() must not be called before the parent scene is initialized");

        if (!isEntered_)
            throw AccessViolationException("ime::Scene::setBackgroundScene() must not be called before the parent scene is entered");

        if (isBackgroundScene())
            throw AccessViolationException("ime::Scene::setBackgroundScene() must not be called on a background scene, nested background scenes are not supported");

        if (scene) {
            if (scene->isBackgroundScene())
                throw AccessViolationException("ime::Scene::setBackgroundScene() must not be called with a scene that is already a background of another scene");

            if (scene->hasBackgroundScene())
                throw AccessViolationException("ime::Scene::setBackgroundScene() must not be called with a scene that has a background scene, nested background scenes are not supported");
        }

        if (backgroundScene_ != scene) {
            if (backgroundScene_)
                backgroundScene_->onExit();

            backgroundScene_ = std::move(scene);

            if (backgroundScene_) {
                backgroundScene_->parentScene_ = this;
                backgroundScene_->init(*engine_);

                backgroundScene_->isEntered_ = true;
                backgroundScene_->onEnter();
            }
        }
    }

    Scene *Scene::getBackgroundScene() {
        return backgroundScene_.get();
    }

    const Scene *Scene::getBackgroundScene() const {
        return backgroundScene_.get();
    }

    Scene *Scene::getParentScene() {
        return parentScene_;
    }

    const Scene *Scene::getParentScene() const {
        return parentScene_;
    }

    bool Scene::isBackgroundScene() const {
        return parentScene_ != nullptr;
    }

    bool Scene::hasBackgroundScene() const {
        return backgroundScene_ != nullptr;
    }

    void Scene::setBackgroundSceneUpdates(bool update) {
        if (isBackgroundSceneUpdated_ != update) {
            isBackgroundSceneUpdated_ = update;

            emitChange(Property("backgroundSceneUpdates", isBackgroundSceneUpdated_));
        }
    }

    bool Scene::isBackgroundSceneUpdated() const {
        return isBackgroundSceneUpdated_;
    }

    void Scene::setBackgroundSceneEventsEnable(bool enable) {
        if (isBackgroundSceneEventsEnabled_ != enable) {
            isBackgroundSceneEventsEnabled_ = enable;

            emitChange(Property("backgroundSceneEventsEnable", enable));
        }
    }

    bool Scene::isBackgroundSceneEventsEnabled() const {
        return isBackgroundSceneEventsEnabled_;
    }

    bool Scene::isEntered() const {
        return isEntered_;
    }

    bool Scene::isPaused() const {
        return isPaused_;
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

    Engine &Scene::getEngine() {
        return const_cast<Engine&>(std::as_const(*this).getEngine());
    }

    const Engine &Scene::getEngine() const {
        if (!engine_)
            throw AccessViolationException("ime::Scene::getEngine() must not be called before the scene is initialized");
        else
            return *engine_;
    }

    Window &Scene::getWindow() {
        return const_cast<Window&>(std::as_const(*this).getWindow());
    }

    const Window &Scene::getWindow() const {
        if (!window_)
            throw AccessViolationException("ime::Scene::getWindow() must not be called before the scene is initialized");
        else
            return *window_;
    }

    Camera &Scene::getCamera() {
        return const_cast<Camera&>(std::as_const(*this).getCamera());
    }

    const Camera &Scene::getCamera() const {
        if (!camera_)
            throw AccessViolationException("ime::Scene::getCamera() must not be called before the scene is initialized");
        else
            return *camera_;
    }

    CameraContainer &Scene::getCameras() {
        return const_cast<CameraContainer&>(std::as_const(*this).getCameras());
    }

    const CameraContainer &Scene::getCameras() const {
        if (!cameraContainer_)
            throw AccessViolationException("ime::Scene::getCameras() must not be called before the scene is initialized");
        else
            return *cameraContainer_;
    }

    PhysicsEngine& Scene::getPhysicsEngine() {
        return const_cast<PhysicsEngine&>(std::as_const(*this).getPhysicsEngine());
    }

    const PhysicsEngine& Scene::getPhysicsEngine() const {
        if (!world_)
            throw AccessViolationException("ime::Scene::createPhysicsEngine() must be called first before calling ime::Scene::getPhysicsEngine()");
        else
            return *world_;
    }

    GridMoverContainer &Scene::getGridMovers() {
        return gridMovers_;
    }

    const GridMoverContainer &Scene::getGridMovers() const {
        return gridMovers_;
    }

    input::InputManager &Scene::getInput() {
        return inputManager_;
    }

    const input::InputManager &Scene::getInput() const {
        return inputManager_;
    }

    audio::AudioManager &Scene::getAudio() {
        return audioManager_;
    }

    const audio::AudioManager &Scene::getAudio() const {
        return audioManager_;
    }

    TimerManager &Scene::getTimer() {
        return timerManager_;
    }

    const TimerManager &Scene::getTimer() const {
        return timerManager_;
    }

    EventEmitter &Scene::getEventEmitter() {
        return eventEmitter_;
    }

    const EventEmitter &Scene::getEventEmitter() const {
        return eventEmitter_;
    }

    EventDispatcher &Scene::getGlobalEventEmitter() {
        return *EventDispatcher::instance();
    }

    PropertyContainer &Scene::getCache() {
        return const_cast<PropertyContainer&>(std::as_const(*this).getCache());
    }

    const PropertyContainer &Scene::getCache() const {
        if (!cache_)
            throw AccessViolationException("ime::Scene::getCache() must not be called before the scene is initialized");
        else
            return *cache_;
    }

    PrefContainer &Scene::getSCache() {
        return const_cast<PrefContainer&>(std::as_const(*this).getSCache());
    }

    const PrefContainer &Scene::getSCache() const {
        if (!sCache_)
            throw AccessViolationException("ime::Scene::getSCache() must not be called before the scene is initialized");
        else
            return *sCache_;
    }

    RenderLayerContainer &Scene::getRenderLayers() {
        return renderLayers_;
    }

    const RenderLayerContainer &Scene::getRenderLayers() const {
        return renderLayers_;
    }

    Grid2D &Scene::getGrid() {
        return const_cast<Grid2D&>(std::as_const(*this).getGrid());
    }

    const Grid2D &Scene::getGrid() const {
        if (!grid2D_)
            throw AccessViolationException("ime::Scene::createGrid2D() must be called first before calling ime::Scene::getGrid()");
        else
            return *grid2D_;
    }

    ui::GuiContainer &Scene::getGui() {
        return const_cast<ui::GuiContainer&>(std::as_const(*this).getGui());
    }

    const ui::GuiContainer &Scene::getGui() const {
        if (!guiContainer_.isTargetSet())
            throw AccessViolationException("ime::Scene::getGui() must not be called before the scene is initialized");
        else
            return guiContainer_;
    }

    ShapeContainer &Scene::getShapes() {
        return *shapeContainer_;
    }

    const ShapeContainer &Scene::getShapes() const {
        return *shapeContainer_;
    }

    GameObjectContainer &Scene::getGameObjects() {
        return *entityContainer_;
    }

    const GameObjectContainer &Scene::getGameObjects() const {
        return *entityContainer_;
    }

    SpriteContainer &Scene::getSprites() {
        return *spriteContainer_;
    }

    const SpriteContainer &Scene::getSprites() const {
        return *spriteContainer_;
    }

    void Scene::createPhysicsEngine(const Vector2f& gravity, const PhysIterations& iterations) {
        world_ = PhysicsEngine::create(*this, gravity);
        world_->setIterations(iterations);
        world_->createDebugDrawer(getEngine().getRenderTarget());
        hasPhysicsSim_ = true;

        if (hasGrid2D_)
            grid2D_->setPhysicsEngine(world_.get());
    }

    void Scene::createGrid2D(unsigned int tileWidth, unsigned int tileHeight) {
        grid2D_ = std::make_unique<Grid2D>(tileWidth, tileHeight, *this);

        if (hasPhysicsSim_)
            grid2D_->setPhysicsEngine(world_.get());

        hasGrid2D_ = true;
    }

    Scene::~Scene() {
        emitDestruction();
    }
}