#include "Oyun.hpp"
#include <iostream>

int ilk = 0;
Oyun::Oyun()
{
	m_fps = 60;
	m_cerceveSuresi = sf::seconds(1.0f / m_fps);
}

Oyun::~Oyun()
{
}
TexturePtr Oyun::kaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu)
{
	if (m_aracKaplamaListesi.count(dosyaIsmi) == 0)
	{
		TexturePtr yeniKaplama = std::make_shared<sf::Texture>();
		sf::String yol = "./resimler/" + dosyaIsmi;
		std::filesystem::path tamyol(yol);

		if (arkaPlanOlsunmu)
		{
			if (yeniKaplama->loadFromFile(tamyol))
			{
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
			}
		}
		else
		{
			sf::Image image;
			if (image.loadFromFile(tamyol))
			{
				auto maskeRengi = image.getPixel(10, 258);
				image.createMaskFromColor(maskeRengi);
				yeniKaplama->loadFromImage(image);
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
				return yeniKaplama;
			}
		}
		return yeniKaplama;

	}
	else
	{
		return m_aracKaplamaListesi[dosyaIsmi];
	}

}
void Oyun::oyunuAyarla()
{
	kaplamaEkle("puzzle.png", false);
	m_oyunAlani = std::make_shared<OyunAlani>();
	m_oyunAlani->bolumYukle();
	animasyonYukle();

	m_skor = 0;

	m_top = Daire::daireUret();
	daireOzellikleriYukle();
	m_atisSayisi = 0;
	m_aktifHayvanAnim = "duran";
	m_patlamaAnim = false;
	m_carpisma = false;

	izgara.ayarla();

	arayuzleriYukle();

	olaylariBagla();
}
void Oyun::arayuzleriYukle()
{
	if (m_panelListesi.size() == 0)
	{
		m_font = std::make_shared<sf::Font>();
		if (!m_font->loadFromFile("./fontlar/alev.ttf"))
		{
			std::cout << "font bulunamadi" << std::endl;
		}
		kaplamaEkle("Button.png");
		kaplamaEkle("Windows.png");

		AracPaneliPtr yeniPanel = std::make_shared<AracPaneli>();
		yeniPanel->fontAta(m_font);
		yeniPanel->aracKaplamasi(m_aracKaplamaListesi["Button.png"]);
		yeniPanel->arkaPlanAta(m_aracKaplamaListesi["Windows.png"], sf::IntRect(sf::Vector2i(799, 933), sf::Vector2i(550, 742)));


		auto btnYeniOyun = yeniPanel->butonEkle("Yeni Oyun");
		auto btnCikis = yeniPanel->butonEkle("Cikis");

		btnCikis->tiklaFonksiyonuEkle([&] {
			this->oyunuKapat();
			});

		btnYeniOyun->tiklaFonksiyonuEkle([&] {
			m_panelListesi[0]->gorunurluk(false);
			m_devamEdiyormu = true;
			m_topAtisSaat.restart();
			std::cout << "---KURALLAR---\n" << std::endl;
			std::cout << "1- Top on saniyede bir otomatik firlatilir\n\n2- Sekiz top atisinda bir tavan alcalir\n\n" << 
				"3- Patlayan ayni renk top basina 10 puan eklenir ve tavan baglantisi kesilerek\n dusen top basina puan 20\'den baslayarak x2 seklinde katlanarak devam eder\n" << std::endl;
			std::cout << "***Oyun Basladi***\n" << std::endl;
			});


		float x = (m_genislik - yeniPanel->boyutGetir().x) / 2;
		float y = (m_yukseklik - yeniPanel->boyutGetir().y) / 2;
		yeniPanel->konumAta(sf::Vector2f(x, y));

		m_panelListesi.push_back(yeniPanel);
	}
}
void Oyun::olaylariBagla()
{
	if (ilk == 0)
	{
		m_pencere.hareketFonksiyonuEkle(
			std::bind(&Oyun::fareHareket, this, std::placeholders::_1, std::placeholders::_2));

		m_pencere.fareBasilmaFonksiyonuEkle(
			std::bind(&Oyun::fareBasildi, this, std::placeholders::_1));

		m_pencere.fareBirakilmaFonksiyonuEkle(
			std::bind(&Oyun::fareBirakma, this, std::placeholders::_1));

		m_pencere.tusBasilmaFonksiyonuEkle(
			std::bind(&Oyun::klavyeBasildi, this, std::placeholders::_1));
		ilk++;
	}
}
void Oyun::klavyeBasildi(sf::Keyboard::Key tus)
{
	if (tus == sf::Keyboard::Left && m_devamEdiyormu)
	{
		m_aktifHayvanAnim = "ceviren";
		if (m_cevirmeKolu->m_aktifSprite == 0)
		{
			m_cevirmeKolu->m_aktifSprite = 1;
		}
		if (izgara.m_hedefCubugu.getRotation().asDegrees() > 110)
			if(izgara.m_hedefCubugu.getRotation().asDegrees() == 253.11f)
				izgara.m_hedefCubugu.setRotation(sf::degrees(250));
			else
				izgara.m_hedefCubugu.rotate(sf::degrees(-5));
		else
			izgara.m_hedefCubugu.setRotation(sf::degrees(106.887));
	}
	if (tus == sf::Keyboard::Right && m_devamEdiyormu)
	{
		m_aktifHayvanAnim = "ceviren";
		if (m_cevirmeKolu->m_aktifSprite == 0)
		{
			m_cevirmeKolu->m_aktifSprite = 1;
		}
		if (izgara.m_hedefCubugu.getRotation().asDegrees() < 250)
			if (izgara.m_hedefCubugu.getRotation().asDegrees() == 106.887f)
				izgara.m_hedefCubugu.setRotation(sf::degrees(110));
			else
				izgara.m_hedefCubugu.rotate(sf::degrees(5));
		else
			izgara.m_hedefCubugu.setRotation(sf::degrees(253.11));
	}
	if (tus == sf::Keyboard::Space && m_top->hareketEdiyormu == false && m_devamEdiyormu)
	{
		m_atisSayisi += m_top->topAt(izgara.m_hedefCubugu.getRotation());
		std::cout << "Tavanin alcalmasina kalan atilacak top sayisi : " << 8 - m_atisSayisi << std::endl;
	}
}
void Oyun::fareHareket(int x, int y)
{
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareHareket(x, y);

	}
}
void Oyun::fareBasildi(sf::Event::MouseButtonEvent olay)
{
	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareButonBasildi(olay);
	}
}
void Oyun::fareBirakma(sf::Event::MouseButtonEvent olay)
{
	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
	{
		siradaki->fareButonBirakildi(olay);
	}
}
void Oyun::oyunuBaslat(unsigned int genislik, unsigned int yukseklik)
{
	m_genislik = genislik;
	m_yukseklik = yukseklik;
	m_pencere.olustur(genislik, yukseklik, "Puzzle Bobble");

	oyunuAyarla();
	m_mancinikAnimasyon = std::make_shared<Animasyon>();
	m_mancinikAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 1805), sf::Vector2i(64, 40), 1, sf::Vector2f(2.2,1.7), sf::Vector2f(32,40));
	m_mancinikAnimasyon->m_konum = sf::Vector2f(320,460);

	m_cevirmeKolu = std::make_shared<Animasyon>();
	m_cevirmeKolu->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1041, 1812), sf::Vector2i(16, 16), 4, sf::Vector2f(2.5, 2.5), sf::Vector2f(8, 16));
	m_cevirmeKolu->m_konum = sf::Vector2f(370, 460);

	AnimasyonPtr duranHayvan = std::make_shared<Animasyon>();
	duranHayvan->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(760, 2012), sf::Vector2i(32, 32), 3, sf::Vector2f(2.5, 2.5), sf::Vector2f(16, 32));
	duranHayvan->m_konum = sf::Vector2f(385, 460);
	duranHayvan->m_degisimSuresi = 8;
	m_hayvanAnimasyonHaritasi["duran"] = duranHayvan;

	AnimasyonPtr cevirenHayvan = std::make_shared<Animasyon>();
	cevirenHayvan->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 2045), sf::Vector2i(32, 32), 8, sf::Vector2f(2.5, 2.5), sf::Vector2f(16, 32));
	cevirenHayvan->m_konum = sf::Vector2f(385, 460);
	cevirenHayvan->m_degisimSuresi = 2;
	m_hayvanAnimasyonHaritasi["ceviren"] = cevirenHayvan;

	AnimasyonPtr okAnim = std::make_shared<Animasyon>();
	okAnim->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 1545), sf::Vector2i(64, 64), 1, sf::Vector2f(2.3, 2), sf::Vector2f(32, 32));
	okAnim->m_konum = sf::Vector2f(320, 425);
	izgara.m_okAnim = okAnim;

	saatiYenidenBaslat();
	while (m_pencere.acikmi())
	{
		m_pencere.olayKontrol();

		if (m_saat.getElapsedTime() >= m_cerceveSuresi)
		{
			guncelle();
			cizimFonksiyonu();
			saatiYenidenBaslat();
		}
		else
		{
			sf::sleep(m_cerceveSuresi - m_saat.getElapsedTime());
		}

	}
}
void Oyun::cizimFonksiyonu()
{
	m_pencere.cizimeBasla();

	for (auto siradaki : m_panelListesi)
	{
		siradaki->ciz(m_pencere);
	}

	if (m_devamEdiyormu)
	{
		m_mancinikAnimasyon->ciz(m_pencere);
		m_cevirmeKolu->ciz(m_pencere);
		izgara.ciz(m_pencere);
		patlat();
		m_oyunAlani->ciz(m_pencere);
		m_hayvanAnimasyonHaritasi[m_aktifHayvanAnim]->ciz(m_pencere);
		if (!m_patlamaAnim)
		{
			m_top->hareket();
			sureliTopAt();
			m_top->ciz(m_pencere);
			m_carpisma = carpismaKontrol();
			carpismaSonrasi(m_carpisma);
			patlamaKontrol(m_carpisma);
			tavanDusur();
		}
	}

	m_pencere.cizimiBitir();
}
void Oyun::saatiYenidenBaslat()
{
	m_saat.restart();
}
void Oyun::oyunuKapat()
{
	m_pencere.kapat();
}
void Oyun::daireOzellikleriYukle()
{
	std::vector<sf::Color> oyundakiRenkler;
	for (int i = 0; i < m_oyunAlani->m_daireler.size(); i++)
	{
		sf::Color simdiki = m_oyunAlani->m_daireler.at(i)->m_sekil.getFillColor();
		if (std::find(oyundakiRenkler.begin(), oyundakiRenkler.end(), simdiki) != oyundakiRenkler.end())
			continue;
		else
			oyundakiRenkler.push_back(simdiki);
	}

	int renkSayisi = oyundakiRenkler.size();
	if (renkSayisi != 0)
	{
		m_top->m_sekil.setFillColor(oyundakiRenkler.at(rand() % renkSayisi));

		if (m_top->m_sekil.getFillColor() == sf::Color::Red)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(436, 2614), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8,8));
			m_top->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(453, 2614), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(555, 2606), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			m_top->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (m_top->m_sekil.getFillColor() == sf::Color::Blue)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 2614), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(18, 2614), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(120, 2606), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			m_top->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (m_top->m_sekil.getFillColor() == sf::Color::Green)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(436, 2647), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(453, 2647), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(555, 2639), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			m_top->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (m_top->m_sekil.getFillColor() == sf::Color::Yellow)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 2647), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(18, 2647), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			m_top->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(120, 2639), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			m_top->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		m_top->animasyonDegistir("duran");
	}
	else 
		m_top->m_sekil.setFillColor(sf::Color::Black);


}
void Oyun::topUret(bool carpisma, bool devammi)
{
	if (carpisma && devammi)
	{
		m_top = Daire::daireUret();
		daireOzellikleriYukle();
	}
}
bool Oyun::carpismaKontrol()
{
	if(m_top->hareketEdiyormu)
	{
		for (int i = 0; i < m_oyunAlani->m_daireler.size(); i++)
		{
			float konumTopX = m_top->m_konum.x;
			float konumTopY = m_top->m_konum.y;
			float konumDaireX = m_oyunAlani->m_daireler.at(i)->m_konum.x;
			float konumDaireY = m_oyunAlani->m_daireler.at(i)->m_konum.y;
			if (mesafeHesapla(konumTopX, konumTopY, konumDaireX, konumDaireY) <= 39)
			{
				if (konumTopX > konumDaireX)
				{
					if (konumTopY - 10 <= konumDaireY)	// sag ust
					{
						m_top->m_konum.y = konumDaireY;
						m_top->m_konum.x = konumDaireX + 40;
						m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir;
						m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun + 2;
					}
					else // sag
					{
						if(konumDaireX != 460)
						{
							m_top->m_konum.y = konumDaireY + 20 * sqrtf(3);
							m_top->m_konum.x = konumDaireX + 20;
							m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir + 1;
							m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun + 1;
						}
						else
						{
							m_top->m_konum.y = konumDaireY + 20 * sqrtf(3);
							m_top->m_konum.x = konumDaireX - 20;
							m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir + 1;
							m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun - 1;
						}
					}
				}
				else
				{
					if (konumTopY - 10 <= konumDaireY)	// sol ust
					{
						m_top->m_konum.y = konumDaireY;
						m_top->m_konum.x = konumDaireX - 40;
						m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir;
						m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun - 2;
					}
					else // sol
					{
						if (konumDaireX != 180)
						{
							m_top->m_konum.y = konumDaireY + 20 * sqrtf(3);
							m_top->m_konum.x = konumDaireX - 20;
							m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir + 1;
							m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun - 1;
						}
						else
						{
							m_top->m_konum.y = konumDaireY + 20 * sqrtf(3);
							m_top->m_konum.x = konumDaireX + 20;
							m_top->konumSatir = m_oyunAlani->m_daireler.at(i)->konumSatir + 1;
							m_top->konumSutun = m_oyunAlani->m_daireler.at(i)->konumSutun + 1;
						}
					}
				}
				m_topAtisSaat.restart();
				return true;
			}
		}
		if (m_top->m_konum.y < izgara.m_ust.getSize().y + 20)
		{
			m_top->m_konum.y = izgara.m_ust.getSize().y + 20;
			m_top->konumSatir = 0;
			for (int i = 1; i <= 15; i += 2)
			{
				if (abs((160 + i * 20) - m_top->m_konum.x) <= 20)
				{
					m_top->m_konum.x = 160 + i * 20;
					m_top->konumSutun = i;
				}
			}
			m_topAtisSaat.restart();
			return true;
		}
		else if (m_top->m_konum.x <= 180 || m_top->m_konum.x >= 460)
		{
			m_top->m_yon *= -1;
		}
	}
	return false;
}
void Oyun::carpismaSonrasi(bool carpisma)
{
	if (carpisma)
	{
		m_top->hareketEdiyormu = false;
		m_oyunAlani->m_daireler.push_back(m_top);
		std::sort(m_oyunAlani->m_daireler.begin(),
			m_oyunAlani->m_daireler.end(),
			[](const DairePtr& lhs, const DairePtr& rhs)
			{
				return lhs->konumSatir > rhs->konumSatir;
			});
		m_oyunAlani->m_daireDizisi[m_top->konumSatir][m_top->konumSutun / 2] = m_top;
		m_oyunAlani->graph.graphTemizle();
		m_oyunAlani->graphOlustur();
	}
}
float Oyun::mesafeHesapla(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}
void Oyun::patlamaKontrol(bool carpisma)
{
	if (carpisma)
	{
		m_oyunAlani->graph.dfsRenk(m_top);
		if (m_oyunAlani->graph.patlamaListe.size() != 0)
		{
			m_skor += 10 * m_oyunAlani->graph.patlamaListe.size();
		}
		else
		{
			m_top->animasyonDegistir("hareket");
		}
	}
}
bool Oyun::devammi(bool carpisma)
{
	if (carpisma)
	{
		for (int i = 0; i < m_oyunAlani->m_daireler.size(); i++)
		{
			if (m_oyunAlani->m_daireler.at(i)->m_konum.y + 20 >= izgara.m_orta.getPosition().y)
			{
				for (int i = 0; i < m_oyunAlani->m_daireler.size(); i++)
				{
					m_oyunAlani->m_daireler.at(i)->m_sekil.setFillColor(sf::Color(220, 220, 220));
				}
				std::cout << "\nBasarisiz !\n\n***Oyun Sifirlandi***\n" << std::endl;
				return false;
			}
		}
		if (m_oyunAlani->m_daireler.size() == 0)
		{
			std::cout << "\nBasarili !\n\n***Oyun Sifirlandi***\n\n" << std::endl;
			return false;
		}
	}
	return true;
}
void Oyun::bastanBaslat(bool devammi)
{
	if (!devammi)
	{
		m_pencere.cizimeBasla();
		m_oyunAlani->ciz(m_pencere);
		m_pencere.cizimiBitir();
		sf::sleep(sf::seconds(2));
		m_panelListesi[0]->gorunurluk(true);
		m_devamEdiyormu = false;
		oyunuAyarla();
	}
}
void Oyun::sureliTopAt()
{
	if (m_topAtisSaat.getElapsedTime().asSeconds() >= 10 && m_top->hareketEdiyormu == false)
	{
		m_atisSayisi += m_top->topAt(izgara.m_hedefCubugu.getRotation());
		std::cout << "Tavanin alcalmasina kalan atilacak top sayisi : " << 8 - m_atisSayisi << std::endl;
	}
}
void Oyun::tavanDusur()
{
	if (m_atisSayisi == 8 && m_top->hareketEdiyormu == false)
	{
		for (int i = 0; i < m_oyunAlani->m_daireler.size(); i++)
		{
			m_oyunAlani->m_daireler.at(i)->m_konum.y += 40;
		}
		izgara.m_ust.setSize(sf::Vector2f(320, izgara.m_ust.getSize().y + 40));
		m_atisSayisi = 0;
		std::cout << "Tavan alcaldi"<< std::endl;
	}
}
void Oyun::havadakiToplariDusur()
{
	int baslangicKombo = 10;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			*m_oyunAlani->graph.tavanBaglantisi = false;
			if (m_oyunAlani->m_daireDizisi[i][j] != NULL)
			{
				if (m_oyunAlani->m_daireDizisi[i][j]->konumSatir == 0)
					continue;
				if (m_oyunAlani->graph.havadami(m_oyunAlani->m_daireDizisi[i][j]))
				{
					m_oyunAlani->m_daireDizisi[i][j]->animasyonDegistir("patlama");
					m_patlamaAnim = true;
					baslangicKombo *= 2;
				}
				m_oyunAlani->graph.graphTemizle();
				m_oyunAlani->graphOlustur();
			}
		}
	}
	if (baslangicKombo > 10)
		m_skor += baslangicKombo;
}

void Oyun::animasyonYukle()
{
	for (auto daire : m_oyunAlani->m_daireler)
	{
		if (daire->m_sekil.getFillColor() == sf::Color::Red)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(436, 2614), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(453, 2614), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(555, 2606), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			daire->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (daire->m_sekil.getFillColor() == sf::Color::Blue)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 2614), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(18, 2614), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(120, 2606), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			daire->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (daire->m_sekil.getFillColor() == sf::Color::Green)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(436, 2647), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(453, 2647), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(555, 2639), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			daire->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		else if (daire->m_sekil.getFillColor() == sf::Color::Yellow)
		{
			AnimasyonPtr duranAnimasyon = std::make_shared<Animasyon>();
			duranAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(1, 2647), sf::Vector2i(16, 16), 1, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["duran"] = duranAnimasyon;

			AnimasyonPtr hareketAnimasyon = std::make_shared<Animasyon>();
			hareketAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(18, 2647), sf::Vector2i(16, 16), 6, sf::Vector2f(40.0f / 16, 40.0f / 16), sf::Vector2f(8, 8));
			daire->m_animasyonlar["hareket"] = hareketAnimasyon;

			AnimasyonPtr patlamaAnimasyon = std::make_shared<Animasyon>();
			patlamaAnimasyon->olustur(m_aracKaplamaListesi["puzzle.png"], sf::Vector2i(120, 2639), sf::Vector2i(32, 32), 7, sf::Vector2f(4, 4), sf::Vector2f(16, 16));
			daire->m_animasyonlar["patlama"] = patlamaAnimasyon;
		}
		daire->animasyonDegistir("duran");
	}
}

void Oyun::guncelle()
{
	if (m_aktifHayvanAnim.compare("ceviren") == 0)
	{
		if (m_hayvanAnimasyonHaritasi["ceviren"]->m_aktifSprite == 7)
		{
			m_hayvanAnimasyonHaritasi["ceviren"]->m_aktifSprite = 0;
			m_aktifHayvanAnim = "duran";
		}
	}
	if (m_cevirmeKolu->m_aktifSprite > 0)
	{
		m_cevirmeKolu->guncelle();
	}
	for (auto daire : m_oyunAlani->m_daireler)
	{
		daire->guncelle();
		if (daire->m_aktifAnimasyon.compare("patlama") == 0)
		{
			if (daire->m_animasyonlar["patlama"]->m_aktifSprite == 6)
			{
				m_patlayacakliste.push_back(daire);
			}
			m_patlamaAnim = true;
		}
	}
	m_hayvanAnimasyonHaritasi[m_aktifHayvanAnim]->guncelle();
}

void Oyun::patlat()
{
	if (m_patlayacakliste.size() != 0)
	{
		for (auto daire : m_patlayacakliste)
		{
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (m_oyunAlani->m_daireDizisi[i][j] == daire)
					{
						m_oyunAlani->m_daireDizisi[i][j] = NULL;
					}
				}
			}
			auto it = std::find(m_oyunAlani->m_daireler.begin(), m_oyunAlani->m_daireler.end(), daire);
			m_oyunAlani->m_daireler.erase(it);
		}
		m_patlayacakliste.clear();
		m_patlamaAnim = false;
		havadakiToplariDusur();
		m_oyunAlani->graph.graphTemizle();
		m_oyunAlani->graphOlustur();
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (m_oyunAlani->m_daireDizisi[i][j] == NULL)
				{
					continue;
				}
				if (m_oyunAlani->m_daireDizisi[i][j]->m_aktifAnimasyon.compare("patlama") == 0)
				{
					return;
				}
			}
		}
		std::cout << "SKOR = " << m_skor << std::endl;
	}
	bool _devammi = devammi(m_carpisma);
	topUret(m_carpisma, _devammi);
	bastanBaslat(_devammi);
}
