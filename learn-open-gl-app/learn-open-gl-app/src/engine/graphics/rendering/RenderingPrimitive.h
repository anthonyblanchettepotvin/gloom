#pragma once

#include "GraphicsObject.h"

class RenderingPrimitive
{
public:
    virtual ~RenderingPrimitive() = default;

    void SetGraphicsObject(GraphicsObject* graphicsObject) { m_GraphicsObject = graphicsObject; }
    GraphicsObject* GetGraphicsObject() const { return m_GraphicsObject; }

private:
    GraphicsObject* m_GraphicsObject;
};
