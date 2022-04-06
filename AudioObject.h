#pragma once
#include <stack>
#include <string>
#include <iostream>

namespace holoplot {

enum Action
{
    ADD = 0,
    DELETE,
    CHANGE_POSITION,
};

struct Id
{
    int m_id;

    Id()
    {
        m_id = m_id_counter;
        m_id_counter++;
    }

    Id(const int &id) : m_id{id}
    {
    }

    Id(const Id &id) : m_id{id.m_id}
    {
    }
    
    private:
    // Counter for generating unique object ids. 
    // This can hit integer limit so need another kind of management for a more complex scheme
    inline static int m_id_counter{};
};

struct Position
{
    int m_x{}, m_y{}, m_z{};

    bool operator==(const Position& rhs) const
    {
        return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z);
    }

    std::string toString() const
    {
        return "(" + std::to_string(m_x) + "," + std::to_string(m_y) + "," + std::to_string(m_z) + ")";
    }
};

struct SavedState
{
    Action action;
    Position position;
    int id;
};

class AudioObject
{
    public:
    AudioObject() = default;
    
    AudioObject(const Position &position) :  
            m_object_id{},
            m_object_position{position} 
    {
    }

    AudioObject(const Id &id, const Position &position) :  
            m_object_id{id},
            m_object_position{position} 
    {
    }

    void setPosition(const Position &position);
    Position getPosition() const;
    Id getObjectId() const;
    int getObjectIntId() const;
    bool isPositionEqual(const Position &position) const;

    private:
    Id m_object_id;
    Position m_object_position;
};
}