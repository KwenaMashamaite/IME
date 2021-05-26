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
///  @code
///  #include <IME/IME.h>
///
/// // Step 1: Define a state
/// // Define the behaviour of the game state by overriding the scene methods.
/// // These functions will be called by the engine at specific times. Scene
/// // methods are overridden by a need to use case, however the 'onEnter'
/// // function must always be overridden
/// class Demo : public ime::Scene {
///   public:
///       void onEnter() override {
///           // Lets create our knight object, lets call him 'destroyerOfMen"
///           auto* knight = gameObjects().add(ime::GameObject::create(*this));
///           knight->setTag("destroyerOfMen");
///           knight->getSprite().setTexture("knight.png");
///
///           // Enable physics so that our knight can move around the grid, otherwise he'll be easily ambushed
///           auto gravity = ime::Vector2f{0, 9.8f};
///           createPhysWorld(gravity);
///           auto physicsBody = physWorld().createBody(ime::RigidBody::Type::Kinematic);
///           physicsBody->setLinearVelocity(ime::Vector2f{60.0f, 60.0f});
///           knight->attachRigidBody(std::move(physicsBody));
///
///           // We now create the grid in which the knight will patrol in
///           createTilemap(40, 40); // The size of each grid block will be 40x40
///           tilemap().construct({10, 10}, '.'); // Create a 10x10 grid
///           tilemap().addChild(knight, ime::Index{1, 1});
///
///           // We want our knight to move in the direction we want using the keyboard
///           auto gridMover = std::make_unique<ime::KeyboardGridMover>(tilemap());
///           gridMover->setTarget(knight);
///           gridMover->setMovementRestriction(ime::GridMover::MoveRestriction::NonDiagonal);
///           gridMovers().addObject(std::move(gridMover));
///
///           // And just like that, our kingdom is protected!
///
///           // Lets play some medieval music for our knight to Keep his spirit up
///           audio().play(ime::audio::Type::Music, "medievalTheme.wav");
///
///           // Quit the game when Esc key is pressed
///           input().onKeyUp([this](ime::Key key) {
///                 if (key == ime::Key::Escape)
///                     engine().quit();
///           });
///     }
/// };
///
/// int main()
/// {
///    // Step 2: Create engine configurations (They can also be defined in a text
///    //         file on the disk and loaded by providing the filename to the engines
///    //         constructor)
///    //
///    // All these configurations defaults so they can be left undefined.
///    // However it's better to specify your own settings. You can add you
///    // own entries if you wish to do so
///    PropertyContainer settings;
///    settings.addProperty({"WINDOW_TITLE", std::string("Demo")});
///    settings.addProperty({"WINDOW_WIDTH", 800});
///    settings.addProperty({"WINDOW_HEIGHT", 700});
///    settings.addProperty({"WINDOW_ICON", std::string("assets/bitmap/icon.png")});
///    settings.addProperty({"FULLSCREEN", false});
///    settings.addProperty({"FPS_LIMIT", 60});
///    settings.addProperty({"V_SYNC", true});
///    settings.addProperty({"FONTS_DIR", std::string("assets/fonts/")});
///    settings.addProperty({"IMAGES_DIR", std::string("assets/textures/")});
///    settings.addProperty({"TEXTURES_DIR", std::string("assets/textures/")});
///    settings.addProperty({"SOUND_EFFECTS_DIR", std::string("assets/soundEffects/")});
///    settings.addProperty({"MUSIC_DIR", std::string("assets/music/")});
///
///    // Step 3: Create the engine and initialize it
///    auto engine = ime::Engine("Demo", settings);
///    engine.initialize();
///
///    // Step 4: Push the initial state and run the engine
///    engine.pushScene(std::make_shared<Demo>());
///    engine.run();
///
///    return EXIT_SUCCESS;
/// }
/// @endcode
////////////////////////////////////////////////////////////
