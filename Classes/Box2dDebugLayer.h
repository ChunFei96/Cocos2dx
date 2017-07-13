#ifndef b2DebugLayer_h__
#define b2DebugLayer_h__

#include "cocos2d.h"
#include "Box2dManager.h"
#include "Globals.h"
#include "Box2dDebugDraw.h"

USING_NS_CC;

class Box2dDebugLayer : public Layer
{
private:
    CustomCommand           m_drawCommand;
    
    void onDrawPrimitives(const kmMat4 &transform, bool transformUpdated)
    {
        kmGLPushMatrix();
        kmGLLoadMatrix(&transform);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
        Box2dManager::getInstance().getWorld().DrawDebugData();
        kmGLPopMatrix();
    }

    void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
    {
        m_drawCommand.init(_globalZOrder);
        m_drawCommand.func = CC_CALLBACK_0(Box2dDebugLayer::onDrawPrimitives, this, transform, transformUpdated);
        renderer->addCommand(&m_drawCommand);
    }

    bool init()
    {
        if (!Layer::init())
        {
            return false;
        }

        Box2dDebugDraw* m_debugDraw = new Box2dDebugDraw(PTM_RATIO);
        Box2dManager::getInstance().getWorld().SetDebugDraw(m_debugDraw);
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        // NOTE: DO NOT DELETE COMMETS BELOW!
        // flags += b2Draw::e_jointBit;
        // flags += b2Draw::e_centerOfMassBit;
        // flags += b2Draw::e_aabbBit;
        // flags += b2Draw::e_pairBit;
        m_debugDraw->SetFlags(flags);

        return true;
    }

public:
    CREATE_FUNC(Box2dDebugLayer);
};

#endif // b2DebugLayer_h__
