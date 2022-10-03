#include "OyunAlani.hpp"
#include "json.hpp"
#include <string>
using json = nlohmann::json;

OyunAlani::OyunAlani()
{
	top_sayisi = 30;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_daireDizisi[i][j] = NULL;
		}
	}
}

void OyunAlani::ciz(Pencere& pencere)
{
	for (auto siradaki : m_daireler)
		siradaki->ciz(pencere);
}

void OyunAlani::bolumYukle()
{
	std::string jsonBolum = 
"{\n"
"  \"level\" : 1,\n"
"  \"top_sayisi\" : 30,\n"
"  \"toplar\": [\n"
"    {\n"
"      \"id\" : 0,\n"
"      \"konumX\" : 1,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 1,\n"
"      \"konumX\" : 3,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 2,\n"
"      \"konumX\" : 5,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 3,\n"
"      \"konumX\" : 7,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 4,\n"
"      \"konumX\" : 9,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 5,\n"
"      \"konumX\" : 11,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 6,\n"
"      \"konumX\" : 13,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 7,\n"
"      \"konumX\" : 15,\n"
"      \"konumY\" : 0,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 8,\n"
"      \"konumX\" : 2,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 9,\n"
"      \"konumX\" : 4,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 10,\n"
"      \"konumX\" : 6,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 11,\n"
"      \"konumX\" : 8,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 12,\n"
"      \"konumX\" : 10,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 13,\n"
"      \"konumX\" : 12,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 14,\n"
"      \"konumX\" : 14,\n"
"      \"konumY\" : 1,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 15,\n"
"      \"konumX\" : 1,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 16,\n"
"      \"konumX\" : 3,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 17,\n"
"      \"konumX\" : 5,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 18,\n"
"      \"konumX\" : 7,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 19,\n"
"      \"konumX\" : 9,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 20,\n"
"      \"konumX\" : 11,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 21,\n"
"      \"konumX\" : 13,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 22,\n"
"      \"konumX\" : 15,\n"
"      \"konumY\" : 2,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 23,\n"
"      \"konumX\" : 2,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"blue\"\n"
"    },\n"
"    {\n"
"      \"id\" : 24,\n"
"      \"konumX\" : 4,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 25,\n"
"      \"konumX\" : 6,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"green\"\n"
"    },\n"
"    {\n"
"      \"id\" : 26,\n"
"      \"konumX\" : 8,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 27,\n"
"      \"konumX\" : 10,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"red\"\n"
"    },\n"
"    {\n"
"      \"id\" : 28,\n"
"      \"konumX\" : 12,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"yellow\"\n"
"    },\n"
"    {\n"
"      \"id\" : 29,\n"
"      \"konumX\" : 14,\n"
"      \"konumY\" : 3,\n"
"      \"renk\": \"yellow\"\n"
"    }\n"
"  ]\n"
"}";

	json j = json::parse(jsonBolum);
	int top_sayisi = j["top_sayisi"];
	for (int i = 0; i < top_sayisi; i++)
	{
		std::string renk = j["toplar"][i]["renk"];
		sf::Color color;
		int konumX = j["toplar"][i]["konumX"];
		int konumY = j["toplar"][i]["konumY"];
		if (renk._Equal("red"))
		{
			color = sf::Color::Red;
		}
		if (renk._Equal("yellow"))
		{
			color = sf::Color::Yellow;
		}
		if (renk._Equal("blue"))
		{
			color = sf::Color::Blue;
		}
		if (renk._Equal("green"))
		{
			color = sf::Color::Green;
		}
		DairePtr yeniDaire = Daire::daireUret(color, konumX, konumY);
		m_daireler.push_back(yeniDaire);
		m_daireDizisi[konumY][konumX / 2] = yeniDaire;
		std::sort(m_daireler.begin(),
			m_daireler.end(),
			[](const DairePtr& lhs, const DairePtr& rhs)
			{
				return lhs->konumSatir > rhs->konumSatir;
			});
	}
	graphOlustur();
}
void OyunAlani::graphBaglanti(DairePtr yeniDaire, int konumY, int konumX)
{
	if (konumX == 2)
	{
		if (m_daireDizisi[konumY - 1][konumX / 2 - 1] != NULL)	// Sol ust
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2 - 1]);
		}
		if (m_daireDizisi[konumY - 1][konumX / 2] != NULL)		// sag ust
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2]);
		}
		if (m_daireDizisi[konumY][konumX / 2 + 1] != NULL)		// sag
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 + 1]);
		}
		if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)		// sag alt
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
		}
		if (m_daireDizisi[konumY + 1][konumX / 2 - 1] != NULL)	// sol alt
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 - 1]);
		}
	}
	else if (konumX == 14)
	{
		if (m_daireDizisi[konumY - 1][konumX / 2] != NULL)		// sag ust
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2]);
		}
		if (m_daireDizisi[konumY - 1][konumX / 2 - 1] != NULL)	// Sol ust
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2 - 1]);
		}
		if (m_daireDizisi[konumY][konumX / 2 - 1] != NULL)		// sol
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 - 1]);
		}
		if (m_daireDizisi[konumY + 1][konumX / 2 - 1] != NULL)	// sol alt
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 - 1]);
		}
		if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)		// sag alt
		{
			graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
		}
	}
	else if (konumX == 1)
	{
		if (konumY == 0)
		{
			if (m_daireDizisi[konumY][konumX / 2 + 1] != NULL)		// Sag
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2 + 1] != NULL)	// Sag alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 + 1]);
			}
		}
		else {
			if (m_daireDizisi[konumY - 1][konumX / 2 + 1] != NULL)		// sag ust
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY][konumX / 2 + 1] != NULL)		// Sag
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2 + 1] != NULL)	// Sag alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 + 1]);
			}
		}
	}
	else if (konumX == 15)
	{
		if (konumY == 0)
		{
			if (m_daireDizisi[konumY][konumX / 2 - 1] != NULL)		// Sol
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 - 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)	// Sol alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 ]);
			}
		}
		else {
			if (m_daireDizisi[konumY][konumX / 2 - 1] != NULL)		// Sol
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 - 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)	// Sol alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
			}
			if (m_daireDizisi[konumY - 1][konumX / 2] != NULL)	// Sol ust
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2]);
			}
		}
	}
	else
	{
		if (konumY == 0)
		{
			if (m_daireDizisi[konumY][konumX / 2 + 1] != NULL)		// Sag
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY][konumX / 2 - 1] != NULL)		// Sol
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 - 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2 + 1] != NULL)	// Sag alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)	// Sol alt
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
			}
		}
		else
		{
			if (m_daireDizisi[konumY][konumX / 2 + 1] != NULL)		// Sag
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 + 1]);
			}
			if (m_daireDizisi[konumY][konumX / 2 - 1] != NULL)		// Sol
			{
				graph.addEdge(yeniDaire, m_daireDizisi[konumY][konumX / 2 - 1]);
			}


			if (konumX % 2 == 0)
			{
				if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)	// Sag alt
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
				}
				if (m_daireDizisi[konumY + 1][konumX / 2 - 1] != NULL)	// Sol alt
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 - 1]);
				}
				if (m_daireDizisi[konumY - 1][konumX / 2] != NULL)		// sag ust
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2]);
				}
				if (m_daireDizisi[konumY - 1][konumX / 2 - 1] != NULL)	// Sol ust
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2 - 1]);
				}
			}
			else
			{
				if (m_daireDizisi[konumY + 1][konumX / 2 + 1] != NULL)	// Sag alt
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2 + 1]);
				}
				if (m_daireDizisi[konumY + 1][konumX / 2] != NULL)	// Sol alt
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY + 1][konumX / 2]);
				}
				if (m_daireDizisi[konumY - 1][konumX / 2 + 1] != NULL)	// Sag ust
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2 + 1]);
				}
				if (m_daireDizisi[konumY - 1][konumX / 2] != NULL)	// Sol ust
				{
					graph.addEdge(yeniDaire, m_daireDizisi[konumY - 1][konumX / 2]);
				}
			}
		}
	}
}

void OyunAlani::graphOlustur()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_daireDizisi[i][j] != NULL)
			{
				graphBaglanti(m_daireDizisi[i][j], m_daireDizisi[i][j]->konumSatir, m_daireDizisi[i][j]->konumSutun);
			}
		}
	}
}
