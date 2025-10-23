#include "quadtree.h"

//QuadTree::QuadTree() {}

// QuadTree::QuadTree(QVector2D &a, QVector2D &b, QVector2D &c, QVector2D &d)
// {
//     A=a;
//     B=b;
//     C=c;
//     D=d;
// }

void QuadTree::subDivide(int n)
{
    if (n>0){
        QVector2D a_=middle(A,B);
        QVector2D b_=middle(B,C);
        QVector2D c_=middle(C,D);
        QVector2D d_=middle(D,A);

        m=middle(A,C);

        sv=new QuadTree(A,a_,m,d_);
        sv->subDivide(n-1);
        sv->print();
        so=new QuadTree(a_,B,b_,m);
        so->subDivide(n-1);
        so->print();
        no=new QuadTree(m,b_,C,c_);
        no->subDivide(n-1);
        no->print();
        nv=new QuadTree(d_,m,c_,D);
        nv->subDivide(n-1);
        nv->print();

    }

}

QuadTree *QuadTree::findObject(VisualObject *GameObject)
{
    QVector2D ObjectPos={GameObject->getPosition().x(),GameObject->getPosition().z()};
    if(isLeaf()){
        return this;
    }
    else{
        m=middle(A,C);
        if(ObjectPos.y()<m.y()){
            //we are at the "south"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                sv->findObject(GameObject);
            }
            else{
                //we go right-> so
                so->findObject(GameObject);
            }
        }
        else{
            //we are at the "north"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                nv->findObject(GameObject);
            }
            else{
                //we go right-> so
                no->findObject(GameObject);
            }
        }
        return this;// is this where we return the quadtree?

    }
}

QuadTree *QuadTree::insertObject(VisualObject *GameObject)
{
    QVector2D ObjectPos={GameObject->getPosition().x(),GameObject->getPosition().z()};
    if(isLeaf()){
        GameObjects.push_back(GameObject);
        return this;
    }
    else{
        m=middle(A,C);
        if(ObjectPos.y()<m.y()){
            //we are at the "south"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                sv->insertObject(GameObject);
            }
            else{
                //we go right-> so
                so->insertObject(GameObject);
            }
        }
        else{
            //we are at the "north"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                nv->insertObject(GameObject);
            }
            else{
                //we go right-> so
                no->insertObject(GameObject);
            }
        }
        return this;// is this where we return the quadtree?

    }
}

void QuadTree::print()
{
    qDebug()<<"A: "<<A.x()<<", "<<A.y()<<"B: "<<B.x()<<", "<<B.y()<<"C: "<<C.x()<<", "<<C.y()<<"D: "<<D.x()<<", "<<D.y();
}
bool QuadTree::isLeaf() {
    if (sv == nullptr && so == nullptr && nv == nullptr && no == nullptr)
        return true;
    else {
        return false;
    }
}

QuadTree::QuadTree(const QVector2D &a, const QVector2D &b, const QVector2D &c, const QVector2D &d)
{
    A=a;
    B=b;
    C=c;
    D=d;
};
