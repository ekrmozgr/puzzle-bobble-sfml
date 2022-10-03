#pragma once
#include "Cizilebilir.hpp"
#include "Animasyon.hpp"
class Daire :public Cizilebilir
{
public:
	Daire(sf::Color& color,int konumX, int konumY);
	Daire();
	static std::shared_ptr<Daire> daireUret(sf::Color& color, int konumX, int konumY);
	static std::shared_ptr<Daire> daireUret();
	void hareket();
	int topAt(sf::Angle angle);
	virtual void ciz(Pencere& pencere) override;
	sf::CircleShape m_sekil;
	float m_hiz;
	bool hareketEdiyormu;
	sf::Angle gidisAcisi;
	int m_yon;
	int konumSatir;
	int konumSutun;
	void guncelle();
	AnimasyonHaritasi m_animasyonlar;
	std::string		m_aktifAnimasyon;
	void animasyonDegistir(const std::string& yeniAnimasyon);
private:

};

typedef std::shared_ptr<Daire>	DairePtr;
typedef std::vector<DairePtr>	DaireListesi;
