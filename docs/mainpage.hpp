////////////////////////////////////////////////////////////
/// \mainpage
///
/// \section welcome Welcome
/// Welcome to the official IME documentation. Here you will find a detailed
/// view of all the classes and functions. <br/>
///
/// \section example Short example
/// IME is state based, which means that the game flow is controlled by pushing
/// and popping game states at appropriate times. Here is an example, demonstrating
/// how to start the engine. This example will display an empty screen since the
/// state is not doing anything
///
/// You need to do four things to get started:
///  1. Define a state
///  2. Create engine settings/configurations
///  3. Instantiate the engine and initialize it
///  4. Push initial state and start the engine
///
///  \code
///
///  #include <IME/core/loop/Engine.h>
///  #include <IME/core/states/State.h>
///
///  // Step 1: Define a state
///  // Define the behaviour of the game state by overriding the state methods.
///  // These functions will be called by the engine at specific times
///  class DemoState : public IME::State {
///  public:
///      explicit DemoState(IME::Engine &engine) : State(engine) {}
///      void onEnter() override {}
///      bool isEntered() const override {}
///      void handleEvent(sf::Event event) override {}
///      void update(float deltaTime) override {}
///      void fixedUpdate(float deltaTime) override {}
///      void render(IME::Graphics::Window &renderTarget) override {}
///      void onPause() override {}
///      void onResume() override {}
///      void onExit() override {}
///  };
///
/// int main()
/// {
///     // Step 2: Create engine configurations (They can also be defined in a text
///     //         file on the disk and loaded by providing the filename to the engines
///     //         constructor)
///     //
///     // All these configurations except the window title have defaults so they
///     // can be left undefined. You can add you own entries if you wish to do so
///     auto configurations = IME::PropertyContainer();
///     configurations.addProperty({"WINDOW_TITLE", "STRING", "Demo"});
///     configurations.addProperty({"WINDOW_WIDTH", "INT", 504});
///     configurations.addProperty({"WINDOW_HEIGHT", "INT", 636});
///     configurations.addProperty({"FPS_LIMIT", "INT", 60});
///     configurations.addProperty({"FULLSCREEN", "BOOL", false});
///     configurations.addProperty({"V_SYNC", "BOOL", true});
///     configurations.addProperty({"FONTS_DIR", "STRING", "/assets/fonts/"});
///     configurations.addProperty({"TEXTURES_DIR", "STRING", "/assets/textures/"});
///     configurations.addProperty({"IMAGES_DIR", "STRING", "/assets/textures/"});
///     configurations.addProperty({"MUSIC_DIR", "STRING", "/assets/music/"});
///     configurations.addProperty({"SOUND_EFFECTS_DIR", "STRING", "/assets/soundEffects/"});
///
///     // Step 3: Create the engine and initialize it
///     auto engine = IME::Engine("Your awesome game name here", configurations);
///     engine.init();
///
///     // Step 4: Push the initial state and run the engine
///     engine.pushState(std::make_shared<DemoState>(engine));
///     engine.run();
///
///     return EXIT_SUCCESS;
/// }
/// \endcode
////////////////////////////////////////////////////////////
