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

#ifndef IME_SCENEMANAGER_H
#define IME_SCENEMANAGER_H

#include "IME/Config.h"
#include "Scene.h"
#include <stack>
#include <memory>

namespace ime {
    /**
     * @brief Manages game scenes
     *
     * The transition between scenes is managed using the Last In First
     * Out (LIFO) technique (The same way std::stack works). Therefore
     * you cannot transition between scenes at random. The order in which
     * scenes are added to the Engine is important.
     *
     * For example, if while in the "gameplay" scene, you push a "pause" scene
     * to the game engine, the "gameplay" scene will be paused (onPause called)
     * and the "pause" scene will be entered (onEnter called on the pause scene
     * instance) and the "pause" scene will become the active scene (gets system
     * events, updates and rendered). If you pop the "pause" scene, the engine
     * will destroy it (onExit called on the pause scene instance) and return
     * to the "gameplay" scene (onResume called on the gameplay scene instance).
     * However, if you push (transition to) another scene while in the "pause"
     * scene, the process repeats; the "pause" scene gets paused and the the new
     * scene becomes active)
     *
     * This class is used internally and it is not meant to be instantiated
     * directly. However, it is available to be used if you want to implement
     * some sort of scene management within a scene (sub scenes within the
     * main scene; maybe instead of having the pause scene as a standalone
     * scene, you make it a sub scene of the gameplay scene. This functionality
     * is not supported in IME. All scenes are standalone and have no knowledge
     * of each other)
     */
    class IME_API SceneManager final {
    public:
        /**
         * @brief Add a Scene
         * @param scene Scene to be added
         * @param enterScene True to immediately enter the scene or false to
         *                   delay entry
         *
         * The scene maybe be added and entered immediately or delayed. By
         * default the scene is delayed. This option allows multiple scenes
         * to be pushed at once to the game engine
         *
         * for example you may want to add multiple scenes in one frame but
         * only enter the last one first as follows:
         *
         * @code
         * sceneManager.pushScene(MainMenu);
         * sceneManager.pushScene(Loading);
         * sceneManager.pushScene(Splash, true);
         *
         * // Because of LIFO, the scenes will be arranged in reverse order:
         * //   Splash -> Loading -> MainMenu.
         * //
         * // Because the enter flag is set to true when pushing the "Splash"
         * // scene, the scene will be added and entered immediately. Let's
         * // assume that the "Splash" and the "Loading" scenes pop themselves
         * // from the game engine when ready. The game flow will be as follows:
         * //
         * // The "Splash" scene shows for some time then pops/removes itself
         * // from the game engine, this triggers the engine to check for the
         * // next available scene. It finds the "Loading" scene and enters it.
         * // After the "Loading" scene has finished (say, loading some resources),
         * // it pops/removes itself. This again triggers the engine to check
         * // for the next available scene, it finds the "MainMenu" scene and
         * // enters it. From here the user may transition to the "Gameplay"
         * // or "Quit" scene
         * @endcode
         *
         * @note A scene can only belong to one scene manager and it cannot
         * be added more than once to the scene manager that owns it
         *
         * @warning The pointer must not be null
         *
         * @see enterTopScene
         */
        void pushScene(std::shared_ptr<Scene> scene, bool enterScene = false);

        /**
         * @brief Remove the current active scene
         */
        void popScene();

        /**
         * @brief Get the current number of scenes
         * @return The current number of scenes
         */
        std::size_t getSceneCount() const;

        /**
         * @brief Enter the scene at the top of the stack
         *
         * This function will enter the last scene to be added and set it
         * as the active scene. This function has no effect if the scene
         * is already entered or the manager has no scenes to manage
         */
        void enterTopScene() const;

        /**
         * @brief Destroy all scenes
         */
        void clear();

        /**
         * @brief Check if the scene manager is empty or not
         * @return True if the scene manager is empty, otherwise false
         */
        bool isEmpty() const;

        /**
         * @brief Render the current scene
         * @param window The window to render the scene on
         */
        void render(Window& window);

        /**
         * @brief Update the scene manager
         * @param deltaTime Time passed since last update
         */
        void preUpdate(Time deltaTime);

        /**
         * @brief Update the current scene using a variable time step
         * @param deltaTime Time passed since last update
         */
        void update(Time deltaTime);

        /**
         * @brief Update the current scene using a fixed time step
         * @param deltaTime Time passed since last update
         */
        void fixedUpdate(Time deltaTime);

        /**
         * @brief Handle a system event
         * @param event Event to be handled
         */
        void handleEvent(Event event);

    private:
        std::stack<std::shared_ptr<Scene>> scenes_; //!< Scenes container
        std::shared_ptr<Scene> prevScene_;          //!< Pointer to the active scene before a push operation
    };
}

#endif // IME_SCENEMANAGER_H
