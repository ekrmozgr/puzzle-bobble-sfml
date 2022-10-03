#pragma once
#include <map>
#include <list>
#include "Daire.hpp"
class Graph {
public:
    Graph();
    std::map<DairePtr, bool> visited;
    std::map<DairePtr, std::list<DairePtr> > adj;
    std::vector<DairePtr> patlamaListe;
    void addEdge(DairePtr v, DairePtr w);
    void dfsRenk(DairePtr v);
    void dfsTavan(DairePtr v);
    void graphTemizle();
    bool havadami(DairePtr v);
    bool* tavanBaglantisi;
    int* sayac;
};