#include "quadtree.h"

void QuadTree::subDivide(int n)
{
    if (n>0){
        QVector2D a_={middle(A,B).x(),middle(A,B).z()};
        QVector2D b_={middle(B,C).x(),middle(B,C).z()};
        QVector2D c_={middle(C,D).x(),middle(C,D).z()};
        QVector2D d_={middle(D,A).x(),middle(D,A).z()};

        m=middle(A,C);

        sv=new QuadTree(A,a_,{m.x(),m.z()},d_);
        sv->subDivide(n-1);
        sv->print();
        so=new QuadTree(a_,B,b_,{m.x(),m.z()});
        so->subDivide(n-1);
        so->print();
        no=new QuadTree({m.x(),m.z()},b_,C,c_);
        no->subDivide(n-1);
        no->print();
        nv=new QuadTree(d_,{m.x(),m.z()},c_,D);
        nv->subDivide(n-1);
        nv->print();

    }

}

QuadTree *QuadTree::findObject(QVector2D *Point)
{
    QVector2D ObjectPos={Point->x(),Point->y()};
    if(isLeaf()){
        return this;
    }
    else{
        m=middle(A,C);
        if(ObjectPos.y()<m.y()){
            //we are at the "south"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                sv->findObject(Point);
            }
            else{
                //we go right-> so
                so->findObject(Point);
            }
        }
        else{
            //we are at the "north"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                nv->findObject(Point);
            }
            else{
                //we go right-> so
                no->findObject(Point);
            }
        }
        return this;// is this where we return the quadtree?
    }
}

void QuadTree::findLeaves(std::vector<QuadTree*> leaves)
{
    if(isLeaf()){
        this->m.setY(averageHeight(this)); //set middle point y value as average height of all points inside the quad
        leaves.push_back(this);
    }
    else{
        if (sv) //south left
            sv->findLeaves(leaves);
        if (so) //south right
            so->findLeaves(leaves);
        if (nv) //north left
            nv->findLeaves(leaves);
        if (no) //north right
            no->findLeaves(leaves);

    }
}

float QuadTree::averageHeight(QuadTree *quadtr)
{
    float height=0;
    if(quadtr->VerticesInQuad.size()>0){
        for(QVector3D* p: quadtr->VerticesInQuad){
            height+=p->y();
        }
        height=height/(quadtr->VerticesInQuad.size()-1);
        return height;
    }
    return height; //change later maybe to not 0
}

QuadTree *QuadTree::insertObject(QVector3D *Point)
{
    QVector2D ObjectPos={Point->x(),Point->y()};
    if(isLeaf()){
        VerticesInQuad.push_back(Point);
        return this;
    }
    else{
        m=middle(A,C);
        if(ObjectPos.y()<m.y()){
            //we are at the "south"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                sv->insertObject(Point);
            }
            else{
                //we go right-> so
                so->insertObject(Point);
            }
        }
        else{
            //we are at the "north"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                nv->insertObject(Point);
            }
            else{
                //we go right-> so
                no->insertObject(Point);
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


//-----------------------------------------------game objects------------------------------------------------------------------------------
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
