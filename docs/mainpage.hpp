////////////////////////////////////////////////////////////
/// \mainpage
///
/// \section welcome Welcome
/// Welcome to the official IME documentation. Here you will find a detailed
/// view of all the classes and functions. <br/>
///
/// \section example Getting started
/// IME is state based, which means that the game flow is controlled by pushing
/// and popping game states at appropriate times. In IME everything lives in a
/// ime::Scene. To get started, you must create a scene (or state), then create
/// the ime::Engine and initialize it. Finally, add a scene or scenes to the
/// engine and run it. This will start the main game loop.
///
/// Here is the minimal and complete code to achieve the above steps:
///  @code
///  // Includes the entire IME library, you can selectively include headers
///  // once you know whats going on
///  #include <IME/IME.h>
///
/// // Step 1: Create a scene (or state)
/// // You define the behavior of your game by overriding ime::Scene functions.
/// // These functions will be called by the engine at appropriate times. ime::Scene
/// // functions are overridden on a need to use case.
///
/// // This scene displays a welcome message at the centre of the screen
/// class StartUpScene : public ime::Scene {
///   public:
///       void onEnter() override {
///         // Greet the user
///          auto greeting = ime::ui::Label::create("Welcome to Infinite Motion Engine");
///          greeting->setOrigin(0.5f, 0.5f);
///          greeting->setPosition("50%", "50%");
///          greeting->getRenderer()->setTextColour(ime::Colour::White);
///          gui().addWidget(std::move(greeting));
///
///           // Quit the game when "Esc" key is pressed
///           input().onKeyUp([this](ime::Keyboard::Key key) {
///                 if (key == ime::Keyboard::Key::Escape)
///                     engine().quit();
///           });
///     }
/// };
///
/// int main()
/// {
///    // Step 2: Creating the game engine
///
///    // 2.1 - First we need to specify settings required by the engine. These
///    //       settings are optional. When not specified the engine will use
///    //       default values
///    ime::PrefContainer settings;
///    settings.addPref({"WINDOW_TITLE", ime::PrefType::String, std::string("IME Demo App")});
///    settings.addPref({"WINDOW_WIDTH", ime::PrefType::Int, 600});
///    settings.addPref({"WINDOW_HEIGHT", ime::PrefType::Int, 600});
///    settings.addPref({"WINDOW_ICON", ime::PrefType::String, std::string("assets/images/icon.png")});
///    settings.addPref({"FULLSCREEN", ime::PrefType::Bool, false});
///    settings.addPref({"FPS_LIMIT", ime::PrefType::Int, 60});
///    settings.addPref({"V_SYNC", ime::PrefType::Bool,  true});
///    settings.addPref({"FONTS_DIR", ime::PrefType::String, std::string("assets/fonts/")});
///    settings.addPref({"TEXTURES_DIR", ime::PrefType::String, std::string("assets/textures/")});
///    settings.addPref({"SOUND_EFFECTS_DIR", ime::PrefType::String, std::string("assets/soundEffects/")});
///    settings.addPref({"MUSIC_DIR", ime::PrefType::String, std::string("assets/music/")});
///
///    // Step 2.2 - Instantiating and initializing the engine
///    ime::Engine engine = ime::Engine("Name of game here", settings);
///    engine.initialize();
///
///    // Step 3: Push the initial state and start the game loop
///    engine.pushScene(std::make_unique<StartUpScene>());
///    engine.run();
///
///    return EXIT_SUCCESS;
/// }
/// @endcode
////////////////////////////////////////////////////////////
