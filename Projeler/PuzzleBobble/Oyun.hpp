#pragma once
#include "TemelTurler.hpp"
#include "Pencere.hpp"
#include "AracPaneli.hpp"
#include "Izgara.hpp"
#include "OyunAlani.hpp"
class Oyun
{
public:
	Oyun();
	~Oyun();
	void oyunuBaslat(unsigned int genislik = 640, unsigned int yukseklik = 465);
	void cizimFonksiyonu();
	TexturePtr kaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu = true);
	void oyunuAyarla();
	void arayuzleriYukle();
	void olaylariBagla();
	void fareHareket(int x, int y);
	void fareBasildi(sf::Event::MouseButtonEvent olay);
	void fareBirakma(sf::Event::MouseButtonEvent olay);
	void klavyeBasildi(sf::Keyboard::Key tus);
	void oyunuKapat();
	void daireOzellikleriYukle();
	void topUret(bool carpisma, bool devammi);
	bool carpismaKontrol();
	void carpismaSonrasi(bool carpisma);
	float mesafeHesapla(float x1, float y1, float x2, float y2);
	void patlamaKontrol(bool carpisma);
	bool devammi(bool carpisma);
	void bastanBaslat(bool devammi);
	void sureliTopAt();
	void tavanDusur();
	void havadakiToplariDusur();
	void animasyonYukle();
	void guncelle();
	void patlat();
private:

	void saatiYenidenBaslat();

	sf::Time			m_gecenSure;
	sf::Time			m_cerceveSuresi;
	sf::Clock			m_saat;
	sf::Clock			m_topAtisSaat;
	Pencere				m_pencere;
	KaplamaHaritasi		m_aracKaplamaListesi;
	int					m_fps;
	AracPaneliListesi	m_panelListesi;
	FontPtr				m_font;
	int					m_genislik;
	int					m_yukseklik;
	bool				m_devamEdiyormu;
	Izgara				izgara;
	OyunAlaniPtr		m_oyunAlani;
	DairePtr			m_top;
	int					m_atisSayisi;
	int					m_skor;
	AnimasyonPtr		m_mancinikAnimasyon;
	AnimasyonPtr		m_cevirmeKolu;
	AnimasyonHaritasi	m_hayvanAnimasyonHaritasi;
	std::string			m_aktifHayvanAnim;
	bool				m_patlamaAnim;
	DaireListesi		m_patlayacakliste;
	bool				m_carpisma;
};