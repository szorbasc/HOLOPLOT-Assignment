#include "AudioObject.h"
using namespace holoplot;

void AudioObject::setPosition(const Position &position)
{
    m_object_position = position;
}

Position AudioObject::getPosition() const
{
    return m_object_position;
}

Id AudioObject::getObjectId() const
{
    return m_object_id;
}

int AudioObject::getObjectIntId() const
{
    return m_object_id.m_id;
}

bool AudioObject::isPositionEqual(const Position &position) const
{
    if(m_object_position == position)
    {
        return true;
    }
    return false;
}