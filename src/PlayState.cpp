#include "PlayState.h"
#include "LevelSelectState.h"
#include "TransitionScreensState.h"

PlayState::PlayState(std::shared_ptr<GameTools> gameTools, std::shared_ptr<SharedData> sharedData)
    :m_gameTools(gameTools),m_sharedData(sharedData),m_contactListener(std::make_unique<MyContactListener>()),
    m_world{ std::make_shared<World>() }, m_lvlsMngr{ m_world }, m_levelIntroduction{ true }
{
    m_world->getWorld()->SetContactListener(m_contactListener.get());
	initilaize();
    
}

void PlayState::processManeger()
{
    if (m_levelIntroduction)
    {
        levelIntroduction();
        return;
    }

    if (m_birds.size() == 0)
        return;

    if (m_birds.back()->isDragged()) {
        sf::Vector2i mouseLocation = sf::Mouse::getPosition(m_gameTools->m_window.getWindow());
        sf::Vector2f worldPosition = m_gameTools->m_window.getWindow().mapPixelToCoords(mouseLocation, m_gameTools->m_window.getWindow().getView()); // Convert to world coordinates
        mouseLocation.x = worldPosition.x;
        mouseLocation.y = worldPosition.y;

        m_birds.back().get()->setRangeVector(mouseLocation, m_gameTools->m_window.getWindow());
        static_cast<Rogatka*>(m_worldObjects[1].get())->ignoreRogatka();
        GuideLine::getInstance().setPosition(m_birds.back()->getPosition());
       

    }
    if (m_birds.back()->isOnRogatka() && !m_birds.back()->isDragged())
    {
        static_cast<Rogatka*>(m_worldObjects[1].get())->resetRogatka();
        GuideLine::getInstance().reset();
    }
        


    if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_gameTools->m_window.getWindow().close();
            break;
        }
        auto location = m_gameTools->m_window.getWindow().mapPixelToCoords(
            { event.mouseButton.x, event.mouseButton.y }, m_gameTools->m_window.getWindow().getView());

        m_birds.back()->handleEvent(event, location);
        checkIfButtonPressed(event, location);
        
    }

}

void PlayState::update()
{
    if (!m_levelIntroduction)
    {
        if (levelEnd())
            return;

        deleteObj();
        updateView();
        if (!(m_birds.back()->isOnRogatka()) && isFinishedMoving())
            setNextBird(true);
    }
}

bool PlayState::levelEnd()
{
    if (m_pigs.size() == 0)
    {
        setUpForEndLevel("Pass", TransitionScreen::PASS);
        return true;
    }
    else if (m_birds.size() == 0)
    {
        setUpForEndLevel("Failed", TransitionScreen::FAILED);
        return true;
    }
    return false;
}

bool PlayState::isFinishedMoving()
{
    if (m_birds.back()->getBodyVelocity().LengthSquared() >= 0.05) 
        return false;
    return std::all_of(m_gameObjects.begin(), m_gameObjects.end(), [](const auto& obj) {return obj->getBodyVelocity().LengthSquared() <= 0.01f; });
}



void PlayState::setNextBird(const bool& x)
{
    if(x) m_birds.pop_back();
    
    if (m_birds.size() > 0)
    {
        static_cast<Rogatka*>(m_worldObjects[1].get())->resetRogatka();
        m_birds.back()->setPosition(std::move(sf::Vector2f(ROGATKA_X, ROGATKA_Y - 50.f)));
        m_birds.back()->setOnRogatka(true);
    }
}

//#level select
void PlayState::setUpForEndLevel(std::string status,const TransitionScreen& transitionScreen)
{
    m_world->getWorld()->SetContactListener(nullptr);
    m_sharedData->levelStatus = status;
    std::string levelScore = m_levelData[static_cast<int>(GameData::SCORE)].second.getString();
    m_sharedData->score = std::stoi(levelScore);
    setScore(-(m_sharedData->score));//to reset score
    m_world->getWorld()->SetContactListener(m_contactListener.get());
    m_gameTools->m_gameStates.addState(std::make_unique<TransitionScreens>(this ->m_gameTools, transitionScreen), false);
    m_gameTools->m_window.resetView();
    m_levelIntroduction = true;
}


void PlayState::Draw()
{
    m_gameTools->m_window.getWindow().clear();
    drawGame();
    m_gameTools->m_window.getWindow().display();
    m_world->step(1.f / 60.f, 8, 3);
}

void PlayState::Resume()
{
    if (m_sharedData->levelToRead > 0)
    {
        m_lvlsMngr.getSpecificLevel(m_sharedData->levelToRead, m_birds, m_pigs, m_gameObjects);
        setNextBird(false);
        m_levelData.at(static_cast<int>(GameData::LEVEL)).second = GameResources::getInstance().createText(std::to_string(m_sharedData->levelToRead), sf::Color::White, 1);
    }
    setSoundTexture(m_buttons.at(1));
}

void PlayState::deleteObj()
{
    for (const auto& pig : m_pigs)
    {
        if (pig->getHp() <= 0) {
            setScore(pig->getScore());
            m_poofsContainer.push_back(pig->getPosition());
        }
    }
    std::erase_if(m_pigs, [](const auto& x) {return x->getHp() <= 0; });

    for (const auto& obj : m_gameObjects)
    {
        if (obj->getHp() <= 0) {
            setScore(obj->getScore());
            m_poofsContainer.push_back(obj->getPosition());
        }
    }
    std::erase_if(m_gameObjects, [](const auto& x) {return x->getHp() <= 0; });
}

void PlayState::drawGame()
{

    m_gameTools->m_window.getWindow().draw(m_backGround);

    for(auto& button: m_buttons)
        m_gameTools->m_window.getWindow().draw(button);

    if (!m_birds.empty() && m_birds.back()->isDragged()  )
        GuideLine::getInstance().drawGuideLine(m_gameTools->m_window.getWindow());

    for (auto& ea : m_gameObjects) 
    {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }

    for (auto& ea : m_pigs)
    {
        ea->objectUpdate();
        ea->drawObject(m_gameTools->m_window.getWindow());
    }

    std::for_each(m_birds.begin(), m_birds.end(), [this](auto& bird) {
        bird->drawObject(m_gameTools->m_window.getWindow()); 
        if (bird->isDragged()) {
            static_cast<Rogatka*>(m_worldObjects[1].get())->drawSit(m_gameTools->m_window.getWindow(),
                bird->getBeginPosition(), bird->getPosition(), bird->getBirdAngle());
        }
        });
    
    for (auto& string : m_levelData)
    {
        m_gameTools->m_window.getWindow().draw(string.first);
        m_gameTools->m_window.getWindow().draw(string.second);
    }
       
        
    m_worldObjects[1]->drawObject(m_gameTools->m_window.getWindow());
    

    drawDestroyedObj();
}

void PlayState::updateView()
{
    if (m_birds.back()->isHit())
        return;

    sf::Vector2f tempView{ m_gameTools->m_window.getWindow().getView().getSize() };
    if (m_birds.back()->getPosition().x - m_gameTools->m_window.getWindow().getView().getSize().x / 2 <= 0)
    {
        m_gameTools->m_window.setView(tempView.x / 2.f, tempView.y / 2.f);
        updateDataPosition();
    }
    else
    {
        m_gameTools->m_window.setView(m_birds.back()->getPosition().x, WINDOW_HEIGHT / 2);
        updateDataPosition();
    }

    if (m_birds.back()->getPosition().x + tempView.x / 2 >= m_backGround.getSize().x)
    {
        m_gameTools->m_window.setView(m_backGround.getSize().x - tempView.x / 2, WINDOW_HEIGHT / 2);
        updateDataPosition();
    }
  

}

void PlayState::initilaize()
{ 
    //init background
    m_backGround.setTexture(&GameResources::getInstance().getBackGroundScreens(backGrounds::LEVEL));
    m_backGround.setSize(sf::Vector2f(m_backGround.getTexture()->getSize().x * 3, m_backGround.getTexture()->getSize().y));
    m_backGround.setPosition(0, 0);

    //create the restart button
    for (int i = 0; i < 3; i++)
    {
        m_buttons.emplace_back();
        m_buttons.back().setRadius(30.f);
        m_buttons.back().setOrigin(m_buttons.back().getRadius(), m_buttons.back().getRadius());
    }
    m_buttons.at(0).setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::RESTART)));//restart
    m_buttons.at(1).setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::SOUND)));//sound
    m_buttons.at(2).setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::BACKWARD)));//back


    //init Text Data
    createLevelData();

    //init objects
    createGroundAndRogatka();
    
    GuideLine::getInstance().setWorld(m_world);

    for (size_t i{}; i < m_destroyAnimation.size(); ++i) {
        m_destroyAnimation.at(i).setSize(sf::Vector2f(50.f, 50.f));
        m_destroyAnimation.at(i).setTexture(&GameResources::getInstance().getPoofTexture(i));
    }
}

void PlayState::createGroundAndRogatka()
{
    m_worldObjects[0] = std::move(ObjectFactory<StaticObjects>::instance().create("ground", m_world, sf::Vector2f(0, 0), m_backGround.getSize(), { 0,0,0 }));
    m_worldObjects[1] = std::move(ObjectFactory<StaticObjects>::instance().create("rogatka", m_world, sf::Vector2f(ROGATKA_X, ROGATKA_Y), sf::Vector2f{ 15.f, 80.f }, {0,0,0}));
}

void PlayState::createLevelData()
{
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Level: ", sf::Color::White, 1);
    m_levelData.emplace_back().first = GameResources::getInstance().createText("Score: ", sf::Color::White, 1);
    m_levelData.back().second = GameResources::getInstance().createText("0", sf::Color::White, 1);
    updateDataPosition();
}

void PlayState::updateDataPosition()
{
    float yPos = 50.f;
    for (auto& string : m_levelData)
    {
        string.first.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x + WINDOW_WIDTH/2 - 155, yPos));
        string.second.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x+ WINDOW_WIDTH/2 - 65, yPos));
        yPos += 50.f;
    }
    yPos = 50.f;
    auto xPos = 50.f;
    for (auto& button : m_buttons)
    {
        button.setPosition(sf::Vector2f(m_gameTools->m_window.getWindow().getView().getCenter().x - WINDOW_WIDTH / 2 + xPos, yPos));
        xPos += 75.f;
    }
}

void PlayState::setScore(const int &toAdd)
{
    std::string temp = m_levelData[static_cast<int>(GameData::SCORE)].second.getString();
    auto toSet = std::stoi(temp);
    toSet += toAdd;
    m_levelData[static_cast<int>(GameData::SCORE)].second.setString(std::to_string(toSet));

}

void PlayState::checkIfButtonPressed(const sf::Event& event, const sf::Vector2f& loc)
{
    if (event.type == sf::Event::MouseButtonReleased)
        if (m_buttons.at(0).getGlobalBounds().contains(loc))
            Restart();
        else if (m_buttons.at(1).getGlobalBounds().contains(loc))
            soundButtonClicked(m_buttons.at(1));
        else if (m_buttons.at(2).getGlobalBounds().contains(loc))
            Back();
}

void PlayState::Restart()
{
    m_birds.clear();
    m_pigs.clear();
    m_gameObjects.clear();
    std::string levelScore = m_levelData[static_cast<int>(GameData::SCORE)].second.getString();
    setScore(-(std::stoi(levelScore)));//to reset score
    m_lvlsMngr.getSpecificLevel(m_sharedData->levelToRead, m_birds, m_pigs, m_gameObjects);
    setNextBird(false);
    m_levelData.at(static_cast<int>(GameData::LEVEL)).second = GameResources::getInstance().createText(std::to_string(m_sharedData->levelToRead), sf::Color::White, 1);
}

void PlayState::Back()
{
    m_birds.clear();
    m_pigs.clear();
    m_gameObjects.clear();
    std::string levelScore = m_levelData[static_cast<int>(GameData::SCORE)].second.getString();
    setScore(-(std::stoi(levelScore)));//to reset score
    m_gameTools->m_window.resetView();
    m_levelIntroduction = true;
    m_gameTools->m_gameStates.switchStates();
    m_sharedData->levelStatus = "None";
}

void PlayState::levelIntroduction()
{
    //to make the zoom out only once
    static bool first = true;
    bool stop{ false };

    if (first)
    {
        m_gameTools->m_window.setZoom(1.5f);
        first = false;
    }


    if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
            stop = true;
        if (event.type == sf::Event::Closed)
            m_gameTools->m_window.getWindow().close();
    }
        
    
    if (!stop && m_backGround.getSize().x - m_gameTools->m_window.getWindow().getView().getCenter().x > WINDOW_WIDTH /2)
    {
        m_gameTools->m_window.setView(m_gameTools->m_window.getWindow().getView().getCenter().x + 4, WINDOW_HEIGHT / 2);
        updateDataPosition();
        return;
    }

    m_levelIntroduction = false;
    m_gameTools->m_window.resetView();
    m_gameTools->m_window.setZoom(1);
    first = true; 
}


void PlayState::drawDestroyedObj() {
   
    for (auto& poof : m_poofsContainer)
    {
        float elapsedTime = poof.elapsedTime().asSeconds();

        if (elapsedTime >= 0.f && elapsedTime < 0.3) {
            m_destroyAnimation[0].setPosition(poof.m_pos);
            m_gameTools->m_window.getWindow().draw(m_destroyAnimation[0]);
        }
        else if (elapsedTime >= 0.2f && elapsedTime < 0.6f) {
            m_destroyAnimation[1].setPosition(poof.m_pos);
            m_gameTools->m_window.getWindow().draw(m_destroyAnimation[1]);
        }
        else if (elapsedTime >= 0.6f && elapsedTime < 1.f) {
            m_destroyAnimation[2].setPosition(poof.m_pos);
            m_gameTools->m_window.getWindow().draw(m_destroyAnimation[2]);
        }
    }
    std::erase_if(m_poofsContainer, [](auto& p) {return p.elapsedTime().asSeconds() > 1.f; });
}
