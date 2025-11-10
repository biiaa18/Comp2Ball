#include "quadtree.h"

void QuadTree::subDivide(int n)
{
    if (n>0){
        QVector2D a_={middle(A,B).x(),middle(A,B).z()};
        QVector2D b_={middle(B,C).x(),middle(B,C).z()};
        QVector2D c_={middle(C,D).x(),middle(C,D).z()};
        QVector2D d_={middle(D,A).x(),middle(D,A).z()};

        m=middle(A,C);
        qDebug()<<"m: "<<m.x()<<" "<<m.z()<<"\n";
        sv=new QuadTree(A,a_,{m.x(),m.z()},d_);
        sv->subDivide(n-1);
        sv->m=middle(sv->A,sv->C); //we need children to have middle points, otherwise we wont be able to create a grid from middle points
        sv->print();
        so=new QuadTree(a_,B,b_,{m.x(),m.z()});
        so->subDivide(n-1);
        so->m=middle(so->A,so->C);
        so->print();
        no=new QuadTree({m.x(),m.z()},b_,C,c_);
        no->subDivide(n-1);
        no->m=middle(no->A,no->C);
        no->print();
        nv=new QuadTree(d_,{m.x(),m.z()},c_,D);
        nv->subDivide(n-1);
        nv->m=middle(nv->A,nv->C);
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

void QuadTree::findLeaves(std::vector<QuadTree*>* leaves)
{
    //std::vector<QuadTree*> leaves;
    if(isLeaf()){
        m.setY(averageHeight(this)); //set middle point y value as average height of all points inside the quad
        leaves->push_back(this);
        //return this;
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

    //return this;
}

std::vector<QuadTree *> QuadTree::findLeaves2(std::vector<QuadTree *> *leaves)
{
    if(isLeaf()){
        leaves->push_back(this);
        return *leaves;
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
        height=height/(quadtr->VerticesInQuad.size());
        return height;
    }
    return quadtr->m.y(); //change later maybe to not 0
}

bool QuadTree::hasPoint(QVector2D &Point)
{
    if(Point.x()>=A.x() && Point.y()<=C.y() && Point.x()<=C.x() && Point.y()>=A.y()) //m=A+C, and we compare to middle point in leaf
        return true;

    return false;
}

QuadTree *QuadTree::insertObject(QVector3D *Point,QuadTree* parent)
{
    QVector2D ObjectPos={Point->x(),Point->z()};
    if(isLeaf()){
        if(hasPoint(ObjectPos)){
            VerticesInQuad.push_back(Point);
            return this;
        }
        else{
            std::vector<QuadTree*> leaves;
            leaves=parent->findLeaves2(&leaves); //find all leaves of parent tree to find the correct leaf and insert the point in it
            for(QuadTree* it: leaves){
                if(it->hasPoint(ObjectPos)){
                    it->VerticesInQuad.push_back(Point);
                    return it;
                }
            }

        }
    }
    else{
        m=middle(A,C);
        if(ObjectPos.y()<m.z()){
            //we are at the "south"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                sv->insertObject(Point,parent);
            }
            else{
                //we go right-> so
                so->insertObject(Point,parent);
            }
        }
        else{
            //we are at the "north"
            if(ObjectPos.x()<m.x()){
                //we go left-> sv
                nv->insertObject(Point,parent);
            }
            else{
                //we go right-> so
                no->insertObject(Point,parent);
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
