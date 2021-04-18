#include "Splash.hpp"

#include "Assets.hpp"

void Splash::onCreate()
{
    auto font = yoku::Assets::getInstance()->loadFont("callingcode");
    m_Title.setFont(*font);
    m_Title.setString("PONG");
    m_Title.setCharacterSize(30);
    m_Title.setOrigin(m_Title.getLocalBounds().width / 2, m_Title.getLocalBounds().height / 2);
    m_Title.setPosition(m_width / 2, m_height / 2 - 150);

    m_Instruction.setFont(*font);
    m_Instruction.setString("press [ENTER] to start");
    m_Instruction.setCharacterSize(20);
    m_Instruction.setOrigin(m_Instruction.getLocalBounds().width / 2, m_Instruction.getLocalBounds().height / 2);
    m_Instruction.setPosition(m_width / 2, (m_height / 2));
}

void Splash::processEvent(sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
    {
        m_SM.switchTo("main");
        return;
    }
}

void Splash::draw(yoku::Window &window)
{
    window.draw(m_Title);
    window.draw(m_Instruction);
}