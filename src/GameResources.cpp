#include "GameResources.h"

//constructor
GameResources::GameResources()
{
   initTextures();
   initFonts();
   initSounds();
}

//static func - singelton class
//return intance to the class
GameResources& GameResources::getInstance()
{
    static GameResources resources;
    return resources;
}

//get the textures for the menu window
sf::Texture& GameResources::getMenuTexture(const int& index)
{
    return m_menuTexture.at(index);
}

sf::Texture& GameResources::getObstacleTexture(const int& index)
{
    return m_obstacles.at(index);
}

sf::Texture& GameResources::getPoofTexture(const int& index)
{
    return m_poofTexture.at(index);
}
sf::Texture& GameResources::getLock()
{
    return  m_lock;
}
sf::Texture& GameResources::getHelpTexture(const int& index)
{
    return m_helpScreenTexture.at(index);
}

sf::Texture& GameResources::getBirdTexture(const int& index) {
    return m_birdsTexture.at(index);
}


sf::Texture& GameResources::getRogatkaTexture(const int& index) {
    return m_rogatkaTexture.at(index);
}



sf::Texture& GameResources::getBackGroundScreens(const backGrounds& background)
{
    auto index = static_cast<int>(background);
    return m_backGround.at(index);
}

//this is for the Transition screens state 
sf::Texture& GameResources::getTransitionScreensState(const TransitionScreen& screen)
{
    auto index = static_cast<int>(screen);
    return m_transitionScreensState.at(index);
}

//get the textures for the level state screens
sf::Texture& GameResources::getLevelsFields(const int& index)
{
    return m_levelsFields.at(index);
}

//get buttons 
sf::Texture& GameResources::getButtons(const int& index)
{
    return m_buttons.at(index);
}


musicCommand GameResources::getMusicStatus() const
{
    return m_BackGroundSound.getStatus() == sf::Music::Playing ? musicCommand::PLAY : musicCommand::PAUSE;
}

void GameResources::playBackGroundMusic()
{
    if (m_BackGroundSound.getStatus() == sf::Music::Playing)
        m_BackGroundSound.pause();
    else
        m_BackGroundSound.play();
}

//get font
sf::Font& GameResources::getFont(const int& index)
{
    if (index < 2 && index >= 0)
        return m_font[index];
}


//create the text 
sf::Text& GameResources::createText(const std::string &dataName, const sf::Color& color, const int& font)
{
    m_text.setString(dataName);
    m_text.setFont(getFont(font));
    const auto rect = m_text.getLocalBounds();
    m_text.setOrigin(rect.width / 2, rect.height / 2);
    m_text.setCharacterSize(30);
    m_text.setFillColor(color);
    m_text.setStyle(sf::Text::Bold);
    return m_text;
}


//load the texture for the game
void GameResources::initTextures()
{

    //---------------------------menu textures-----------------------------
    //all the texture images names for menu

    std::array<std::string, 3> menuTextureNames{ "play.png", "help.png", "exit.png" };
    for (size_t i = 0; i < menuTextureNames.size(); i++)
        m_menuTexture[i].loadFromFile(menuTextureNames.at(i));
    

    std::array<std::string, 4> helpScreen {  "instruction1.png", "instruction2.png", "instruction3.png", "back.png" };
    for (size_t i = 0; i < helpScreen.size(); i++)
        m_helpScreenTexture[i].loadFromFile(helpScreen.at(i));



    //vector string for the bird's names
    std::array<sf::IntRect, 4> birdLocation{ sf::IntRect{915, 865, 50, 50}, sf::IntRect{551, 658, 65, 55}, sf::IntRect{0 ,447,35,35} ,sf::IntRect{948,572,67,61} }; // 1 448
    for (size_t i = 0; i < birdLocation.size(); i++)
        m_birdsTexture[i].loadFromFile("Angry-Birds.png", birdLocation.at(i));
    

    std::array<sf::IntRect, 5> poofLocation{ sf::IntRect{40,715,126,120} , sf::IntRect{41,467,127,121} ,sf::IntRect{166,151,146,144},
    sf::IntRect{482,393,91,91}  , sf::IntRect{312,157,131,122} };
    for (size_t i = 0; i < poofLocation.size(); i++)
        m_poofTexture[i].loadFromFile("Angry-Birds.png", poofLocation.at(i));
   

    //--------------------------- Loading Obstacles -----------------------------//
    
                                         // Indexes: 0  ,  1  , 2   , 3
    std::array<sf::IntRect, 4> WoodLocation{ sf::IntRect{319,624,205,22} , sf::IntRect{319,647,205,21}, sf::IntRect{233,643,82,42}, sf::IntRect{233,772,83,41} };
    for (size_t i = 0; i < WoodLocation.size(); i++)
        m_obstacles[i].loadFromFile("StaticObjects.png", WoodLocation.at(i));
    
                                        // Indexes: 4  ,  5  , 6   , 7
    std::array<sf::IntRect, 4> IceLocation{ sf::IntRect{319,755,168,22} , sf::IntRect{319,821,168,22}, sf::IntRect{233,686,85,42}, sf::IntRect{233,815,85,42} };
    for (size_t i = 0; i < IceLocation.size(); i++)
        m_obstacles[i + 4].loadFromFile("StaticObjects.png", IceLocation.at(i));
   
                                        // Indexes: 8  ,  9  , 10   , 11
    std::array<sf::IntRect, 4> IronLocation{ sf::IntRect{319,711,168,22} , sf::IntRect{319,778,168,22}, sf::IntRect{805,501,85,42}, sf::IntRect{234,859,85,42} };
    for (size_t i = 0; i < IronLocation.size(); i++)
        m_obstacles[i + 8].loadFromFile("StaticObjects.png", IronLocation.at(i));
    

                                    // Indexes: 12  ,  13  , 14  , 15 ,  16 , 17 (wood - ice - iron)
    std::array<sf::IntRect, 6> BallsLocation{ sf::IntRect{392,121,75,75} , sf::IntRect{85,440,168,22},
                                              sf::IntRect{85,824,75,75}, sf::IntRect{85,748,75,75}, 
                                              sf::IntRect{162,364,75,75}, sf::IntRect{397,364,75,75} };
    for (size_t i = 0; i < BallsLocation.size(); i++)
        m_obstacles[i + 12].loadFromFile("StaticObjects.png", BallsLocation.at(i));
    
    //vector string for the pig's names  // Indexes: 18  ,  19
    std::array<sf::IntRect, 2> pigsLocation{ sf::IntRect{549,924,50,50},sf::IntRect{549,825,50,50} };
    for (size_t i = 0; i < pigsLocation.size(); i++)
        m_obstacles[i + 18].loadFromFile("Angry-Birds.png", pigsLocation.at(i));

    //rogatka texture
    std::array<std::string, 2> rogatkaNames{ "rogatka.png", "rogsit.png"};
    for (size_t i = 0; i < rogatkaNames.size(); i++)
        m_rogatkaTexture[i].loadFromFile(rogatkaNames.at(i));
    

    //get backgrounds
    std::array<std::string, 3> backGroundTextureNames{"MenuBackground.png", "LevelOne.png", "LevelSelectBackGround.png"};
    for (size_t i = 0; i < backGroundTextureNames.size(); i++)
        m_backGround[i].loadFromFile(backGroundTextureNames.at(i));
    
    
    //levels icons on level select state
    std::array<sf::IntRect, 6> levelFields{ sf::IntRect{50, 465, 175, 175}, sf::IntRect{250, 465, 175, 175}, sf::IntRect{450, 465, 175, 175},
                                               sf::IntRect{820, 465, 175, 175}, sf::IntRect{1010, 465, 175, 175}, sf::IntRect{1200, 465, 175, 175}}; // 1 448
    for (size_t i = 0; i < levelFields.size(); i++)
        m_levelsFields[i].loadFromFile("LevelSelectSpriteSheet.png", levelFields.at(i));
   
    
    //load the transition screens for states(game over level pass)
    std::array<std::string, 2> TransitionState{ "failedLevel.png", "LevelPass.png" };
    for (size_t i = 0; i < TransitionState.size(); i++)
        m_transitionScreensState[i].loadFromFile(TransitionState.at(i));
    

    //get buttons texture - 1)restart 2)sound 3)mute 4)backward 5)forward
    std::array<sf::IntRect, 5> buttonsPosition{ sf::IntRect{270,170,185, 185}, sf::IntRect{730, 170, 185, 185} , 
                                                sf::IntRect{965, 170, 185, 185},  sf::IntRect{280, 620, 185, 185}, sf::IntRect{50, 620, 185, 185}};
    for (size_t i = 0; i < buttonsPosition.size(); i++)
        m_buttons[i].loadFromFile("buttons.png", buttonsPosition.at(i));
    
    //get the lock Texture for LevelSelectState(when the levels still unaccessable)
    m_lock.loadFromFile("SpritesForLevelSelect.png", sf::IntRect{ 5, 510, 90, 120 });
}

//load the fonts for the game
void GameResources::initFonts()
{
    std::array<std::string,2> fontsPath = { "C:/Windows/Fonts/Arial.ttf" ,"C:/Windows/Fonts/Ravie.ttf" };
    for (int i = 0; i < 2; i++)
    {
        sf::Font temp;
        temp.loadFromFile(fontsPath[i]);
        m_font[i] = temp;
    }
}

////load the sounds for the game
void GameResources::initSounds()
{
    //load the music
    m_BackGroundBuffer.loadFromFile("menuThemeSong.opus");

    //init background music
    m_BackGroundSound.setBuffer(m_BackGroundBuffer);
    m_BackGroundSound.setLoop(true);
    m_BackGroundSound.play();
}