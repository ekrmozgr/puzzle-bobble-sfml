#pragma once
#include "Daire.hpp"
#include "Graph.hpp"
class OyunAlani :public Cizilebilir
{
public:
	OyunAlani();
	// Inherited via Cizilebilir
	virtual void ciz(Pencere& pencere) override;
	void bolumYukle();

	DaireListesi	m_daireler;
	Graph			graph;
	void			graphBaglanti(DairePtr top, int konumY, int konumX);
	DairePtr		m_daireDizisi[12][8];
	void			graphOlustur();
	int				top_sayisi;
};

typedef std::shared_ptr<OyunAlani> OyunAlaniPtr;
