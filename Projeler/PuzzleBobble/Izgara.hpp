#pragma once

#include "Cizilebilir.hpp"
#include<SFML/Graphics.hpp>
#include "Animasyon.hpp"
class Izgara :public Cizilebilir
{
public:
	Izgara();

	void ayarla();


	// Inherited via Cizilebilir
	virtual void ciz(Pencere& pencere) override;

	sf::RectangleShape m_ust;
	sf::RectangleShape m_orta;
	sf::RectangleShape m_alt;
	sf::RectangleShape m_dikeyDortgen;
	sf::RectangleShape m_hedefCubugu;
	AnimasyonPtr		m_okAnim;
	
};
