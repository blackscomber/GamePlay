/**
 * RenderTarget.cpp
 */

#include "Base.h"
#include "RenderTarget.h"

namespace gameplay
{

static std::vector<RenderTarget*> __renderTargets;

RenderTarget::RenderTarget(const char* id)
    : _id(id), _texture(NULL)
{
}

RenderTarget::~RenderTarget()
{
    SAFE_RELEASE(_texture);

    // Remove ourself from the cache
    std::vector<RenderTarget*>::iterator it = std::find(__renderTargets.begin(), __renderTargets.end(), this);
    if (it != __renderTargets.end())
    {
        __renderTargets.erase(it);
    }
}

RenderTarget* RenderTarget::create(const char* id, unsigned int width, unsigned int height)
{
    // Create a new texture with the given width
    Texture* texture = Texture::create(Texture::RGBA8888, width, height, NULL, false);
    if (texture == NULL)
    {
        return NULL;
    }

    RenderTarget* renderTarget = new RenderTarget(id);
    renderTarget->_texture = texture;

    __renderTargets.push_back(renderTarget);

    return renderTarget;
}

RenderTarget* RenderTarget::getRenderTarget(const char* id)
{
    // Search the vector for a matching ID.
    std::vector<RenderTarget*>::const_iterator it;
    for (it = __renderTargets.begin(); it < __renderTargets.end(); it++)
    {
        RenderTarget* dst = *it;
        if (strcmp(id, dst->getID()) == 0)
        {
            return dst;
        }
    }

    return NULL;
}

const char* RenderTarget::getID() const
{
    return _id.c_str();
}
     
Texture* RenderTarget::getTexture() const
{
    return _texture;
}

}
