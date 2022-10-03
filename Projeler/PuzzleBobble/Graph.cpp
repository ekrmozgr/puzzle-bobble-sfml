#include "Graph.hpp"
#include <iostream>

Graph::Graph()
{
    sayac = new int(0);
    tavanBaglantisi = new bool(false);
}

void Graph::addEdge(DairePtr v, DairePtr w)
{
    adj[v].push_back(w);
}

void Graph::dfsRenk(DairePtr v)
{
    visited[v] = true;
    *sayac += 1;

    std::list<DairePtr>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i] && (*i)->m_sekil.getFillColor() == v->m_sekil.getFillColor())
            dfsRenk(*i);
    if (*sayac >= 3)
    {
        patlamaListe.push_back(v);
        v->animasyonDegistir("patlama");
    }
}

void Graph::dfsTavan(DairePtr v)
{
    visited[v] = true;

    std::list<DairePtr>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            dfsTavan(*i);
    if (v->konumSatir == 0)
        *tavanBaglantisi = true;
}

void Graph::graphTemizle()
{
    visited.clear();
    adj.clear();
    patlamaListe.clear();
    *sayac = 0;
    *tavanBaglantisi = false;
}

bool Graph::havadami(DairePtr v)
{
    auto it = adj.find(v);
    if (it == adj.end())
        return true;
    dfsTavan(v);
    return !*tavanBaglantisi;
}

