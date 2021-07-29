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
/// ime::Scene. To get started, you must create the initial state (or scene),
/// then create the engine and push the initial scene to it. Here are the three
/// steps we need to do:
///
///     1. Create a game state
///     2. Instantiate the game engine
///     3. Push the initial state/scene
///
/// Here is the minimal and complete code to achieve the above steps:
///  @code
///  // Includes the entire IME library, you can selectively include headers
///  // once you know whats going on
///  #include <IME/IME.h>
///
/// // Step 1: Create a game state/scene
/// // You define the behavior of the game by overriding ime::Scene functions.
/// // These functions will be called by the engine at appropriate times. Scene
/// // methods are overridden on a need to use case.
///
/// // This scene displays a message at the centre of the screen
/// class StartUpScene : public ime::Scene {
///   public:
///       void onEnter() override {
///         // Greet the user
///          auto greeting = ime::ui::Label::create("Welcome to Infinite Motion Engine");
///          greeting->setOrigin(0.5f, 0.5f);
///          greeting->setPosition("50%", "50%");
///          greeting->getRenderer()->setTextColour(ime::Colour::White);
///          gui().addWidget(std::move(greeting), "lblGreeting");
///
///           // Quit the game when "Esc" key is pressed
///           input().onKeyUp([this](ime::Key key) {
///                 if (key == ime::Key::Escape)
///                     engine().quit();
///           });
///     }
/// };
///
/// int main()
/// {
///    // Step 2: Creating the game engine
///
///    // 2.1 - First we need to specify settings required by the engine (optional).
///    //       If a preference entry is not given, the engine will use a default value
///    ime::PrefContainer settings;
///    settings.addPref({"WINDOW_TITLE", ime::Preference::Type::String, std::string("IME Demo App")});
///    settings.addPref({"WINDOW_WIDTH", ime::Preference::Type::Int, 600});
///    settings.addPref({"WINDOW_HEIGHT", ime::Preference::Type::Int, 600});
///    settings.addPref({"WINDOW_ICON", ime::Preference::Type::String, std::string("assets/images/icon.png")});
///    settings.addPref({"FULLSCREEN", ime::Preference::Type::Bool, false});
///    settings.addPref({"FPS_LIMIT", ime::Preference::Type::Int, 60});
///    settings.addPref({"V_SYNC", ime::Preference::Type::Bool,  true});
///    settings.addPref({"FONTS_DIR", ime::Preference::Type::String, std::string("assets/fonts/")});
///    settings.addPref({"TEXTURES_DIR", ime::Preference::Type::String, std::string("assets/textures/")});
///    settings.addPref({"SOUND_EFFECTS_DIR", ime::Preference::Type::String, std::string("assets/soundEffects/")});
///    settings.addPref({"MUSIC_DIR", ime::Preference::Type::String, std::string("assets/music/")});
///
///    // Step 2.2 - Instantiating the engine
///    ime::Engine engine = ime::Engine("Name of game here", settings);
///    engine.initialize();
///
///    // Step 3: Push the initial state/scene and start the game loop
///    engine.pushScene(std::make_unique<StartUpScene>());
///    engine.run();
///
///    return EXIT_SUCCESS;
/// }
/// @endcode
////////////////////////////////////////////////////////////
