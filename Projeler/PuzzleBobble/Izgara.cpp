#include "Izgara.hpp"
#include "Pencere.hpp"

Izgara::Izgara()
{
	m_okAnim = NULL;
}

void Izgara::ayarla()
{
	m_ust.setSize(sf::Vector2f(320, 5));
	m_orta.setSize(sf::Vector2f(320, 5));
	m_alt.setSize(sf::Vector2f(320, 5));
	m_dikeyDortgen.setSize(sf::Vector2f(160, 465));
	m_hedefCubugu.setSize(sf::Vector2f(1, 80));

	m_alt.setFillColor(sf::Color::Magenta);
	m_orta.setFillColor(sf::Color(200, 100, 60));
	m_ust.setFillColor(sf::Color(100,150,70));
	m_dikeyDortgen.setFillColor(sf::Color::Magenta);

	m_ust.setPosition(sf::Vector2f(160, 0));
	m_orta.setPosition(sf::Vector2f(160, 385));
	m_alt.setPosition(sf::Vector2f(160, 460));
	m_hedefCubugu.setRotation(sf::degrees(180));
	m_hedefCubugu.setPosition(sf::Vector2f(320, 425));
}
void Izgara::ciz(Pencere& pencere)
{
	m_dikeyDortgen.setPosition(sf::Vector2f(0, 0));
	pencere.ciz(m_dikeyDortgen);

	m_dikeyDortgen.setPosition(sf::Vector2f(480, 0));
	pencere.ciz(m_dikeyDortgen);
	
	pencere.ciz(m_ust);
	pencere.ciz(m_orta);
	pencere.ciz(m_alt);
	//pencere.ciz(m_hedefCubugu);
	if (m_okAnim != NULL)
	{
		m_okAnim->m_spriteListesi.at(0).setRotation(sf::degrees(m_hedefCubugu.getRotation().asDegrees()-180));
		m_okAnim->ciz(pencere);
	}
}
