#include "Daire.hpp"
#include "Pencere.hpp"
#include <iostream>

Daire::Daire()
{
	m_sekil.setRadius(20);
	m_sekil.setOrigin(sf::Vector2f(20, 20));
	m_konum.x = 320;
	m_konum.y = 425;
	m_hiz = 20;
	hareketEdiyormu = false;
	m_yon = 1;
}
Daire::Daire(sf::Color& color, int konumX, int konumY)
{
	m_sekil.setRadius(20);
	m_sekil.setOrigin(sf::Vector2f(20, 20));
	m_sekil.setFillColor(color);
	m_konum.x = 160 + konumX * 20;
	m_konum.y = 25 + konumY * 20 * sqrtf(3);
	m_hiz = 20;
	hareketEdiyormu = false;
	m_yon = 0;
	konumSatir = konumY;
	konumSutun = konumX;
}
DairePtr Daire::daireUret(sf::Color& color, int konumX, int konumY)
{
	return std::make_shared<Daire>(color, konumX, konumY);
}
DairePtr Daire::daireUret()
{
	return std::make_shared<Daire>();
}
void Daire::hareket()
{
	if (hareketEdiyormu)
	{
		float aci = abs(270 - gidisAcisi.asDegrees());
		float radyanAci = aci * 3.14159265f / 180.0f;
		float vX = m_yon * m_hiz * cosf(radyanAci);
		float vY = m_hiz * sinf(radyanAci);

		m_konum = sf::Vector2f(m_konum.x + vX, m_konum.y - vY);
	}
}
int Daire::topAt(sf::Angle angle)
{
	if (hareketEdiyormu)
		return 0;
	hareketEdiyormu = true;
	gidisAcisi = angle;
	return 1;
}
void Daire::ciz(Pencere& pencere)
{
	m_sekil.setPosition(m_konum);

	//pencere.ciz(m_sekil);
	m_animasyonlar[m_aktifAnimasyon]->m_konum = m_konum;
	m_animasyonlar[m_aktifAnimasyon]->ciz(pencere);
	if (m_aktifAnimasyon.compare("hareket") == 0)
	{
		if ((m_animasyonlar[m_aktifAnimasyon]->m_sayac == m_animasyonlar[m_aktifAnimasyon]->m_degisimSuresi) && m_animasyonlar[m_aktifAnimasyon]->m_aktifSprite == 5)
		{
			m_aktifAnimasyon = "duran";
		}
	}
}

void Daire::guncelle()
{
	m_animasyonlar[m_aktifAnimasyon]->guncelle();
}

void Daire::animasyonDegistir(const std::string& yeniAnimasyon)
{
	m_aktifAnimasyon = yeniAnimasyon;
}
