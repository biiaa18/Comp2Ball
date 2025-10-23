#ifndef QUADTREE_H
#define QUADTREE_H
#include <QVector2D>
#include "VisualObject.h"

struct QuadTree
{
    QVector2D A;
    QVector2D B;
    QVector2D C;
    QVector2D D;
    QVector2D m;
    QuadTree* sv{nullptr};
    QuadTree* so{nullptr};
    QuadTree* nv{nullptr};
    QuadTree* no{nullptr};
    bool isLeaf();

    std::vector<VisualObject*> GameObjects;
    //QuadTree();
    QuadTree(const QVector2D& a, const QVector2D& b, const QVector2D& c, const QVector2D& d);
    void subDivide(int n);
    QuadTree* findObject(VisualObject* GameObject);
    QuadTree* insertObject(VisualObject* GameObject);
    void print();

    QVector2D middle(const QVector2D& p1,const QVector2D& p2){
        QVector2D m;
        m.setX((p2.x()+p1.x())/2);
        m.setY((p2.y()+p1.y())/2);
        return m;
    }
};



#endif // QUADTREE_H
