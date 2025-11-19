#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QVulkanWindow>
#include <vector>
#include "Vertex.h"
#include "structindex.h"
//#include "Triangle.h"
#include "Utilities.h"

class VisualObject
{
public:
    VisualObject();

    //ball
    float radius=0.1;//1
    QVector3D position{0.f,0.f,0.f};//{40.3f, 11.3f, 50.55f};
    QVector3D velocity={0.f, 0.f, 0.f};
    //wall
    QVector3D center;
    QVector3D normal;
    //fluid & ball
    bool isBall=false;
    bool isNotMoving=false;
    bool isFinishedMoving=false;
    bool isActive=false;//use this as active flag for object pooling for fluid simulation

    void move(float x, float y = 0.0f, float z = 0.0f);
    void scale(float s);
    void rotate(float t, float x, float y, float z);

	//Setters and Getters
    inline std::vector<Vertex> getVertices() { return mVertices; }
    inline VkBuffer& getVBuffer() { return mVertexBuffer.mBuffer; }
    inline VkDeviceMemory& getVBufferMemory() { return mVertexBuffer.mBufferMemory; }
	inline VkDeviceMemory& getIBufferMemory() { return mIndexBuffer.mBufferMemory; }
    inline void setVBuffer(VkBuffer bufferIn) { mVertexBuffer.mBuffer = bufferIn; }
    inline void setVBufferMemory(VkDeviceMemory bufferMemoryIn) { mVertexBuffer.mBufferMemory = bufferMemoryIn; }
    inline VkBuffer& getIBuffer() { return mIndexBuffer.mBuffer; }
    inline void setIBuffer(VkBuffer bufferIn) { mIndexBuffer.mBuffer = bufferIn; }
    inline void setIBufferMemory(VkDeviceMemory bufferMemoryIn) { mIndexBuffer.mBufferMemory = bufferMemoryIn; }
    inline void setName(std::string name) { mName = name; }
    inline std::string getName() const { return mName; }
    inline int getDrawType() const { return drawType; }
    inline QMatrix4x4 getMatrix() const {return mMatrix;}
	inline std::vector<Vertex> getVertices() const { return mVertices; }
    inline std::vector<uint32_t> getIndices() const { return mIndices; }

    QVector3D getPosition();
    void setPosition(float x, float y, float z);


    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    QMatrix4x4 mMatrix;
    std::string mName;

	BufferHandle mVertexBuffer;
	BufferHandle mIndexBuffer;
    //VkPrimitiveTopology mTopology{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST }; //not used

    int drawType{ 0 }; // 0 = fill, 1 = line

    std::vector<QVector3D> ctrl_p_flate;
    virtual float barysentriske(QVector2D vertx, float dt){return 1.f;};
    //virtual float barysentriskePoint(QVector2D vertx, Quadr){return 1.f;};
};


#endif // VISUALOBJECT_H

