#include "AudioObjectManager.h"
#include "AudioObject.h"
#include <iostream>
#include <string>

using namespace holoplot;

void AudioObjectManager::add(const AudioObject &audioObject) 
{
    int objId = audioObject.getObjectIntId();
    if(const auto &it = m_object_map.find(objId); it == m_object_map.end())
    {
        m_change_history.push(SavedState{Action::ADD, audioObject.getPosition(), objId});
        m_object_map.emplace(objId, audioObject);
        std::cout << "Added object with id:" << std::to_string(objId) << " position:" << audioObject.getPosition().toString() << std::endl;
        // Flush for redo operations
        if(!m_undo_history.empty())
        {
            m_undo_history = std::stack<SavedState>{};
        }
    }
}

void AudioObjectManager::remove(const Id &id) 
{
    if(const auto &it = m_object_map.find(id.m_id); it != m_object_map.end())
    {
        m_change_history.push(SavedState{Action::DELETE, it->second.getPosition(), it->second.getObjectIntId()});
        m_object_map.erase(id.m_id);
        std::cout << "Deleted object with id:" << std::to_string(id.m_id) << std::endl;
        // Flush for redo operations
        if(!m_undo_history.empty())
        {
            m_undo_history = std::stack<SavedState>{};
        }
    }
}

void AudioObjectManager::changePosition(const Id &id, const Position &position) 
{
    if(const auto& it = m_object_map.find(id.m_id); it != m_object_map.end() && !it->second.isPositionEqual(position))
    {
        const auto &latestChange = m_change_history.top();
        // Dont push the position change if there is already a saved position change state for the same id 
        if(latestChange.id == id.m_id && latestChange.action == Action::CHANGE_POSITION)
        {
            m_object_map.at(id.m_id).setPosition(position);
            std::cout << "Changed position of object with id:" << std::to_string(id.m_id) << " to position:" 
                << position.toString() << std::endl;
            return;
        }
        m_change_history.push(SavedState{Action::CHANGE_POSITION, it->second.getPosition(), it->second.getObjectIntId()});   
        m_object_map.at(id.m_id).setPosition(position);
        std::cout << "Changed position of object with id:" << std::to_string(id.m_id) << " to position:" 
                << position.toString() << std::endl;
        // Flush for redo operations
        if(!m_undo_history.empty())
        {
            m_undo_history = std::stack<SavedState>{};
        }
    }
}

void AudioObjectManager::undo() 
{
    if(m_change_history.empty())
    {
        std::cout << "No action to undo" << std::endl;
        return;
    }

    const auto &latestChange = m_change_history.top();
    switch (latestChange.action) 
    {
    case Action::CHANGE_POSITION:
        {
            if(const auto& it = m_object_map.find(latestChange.id); it != m_object_map.end())
            {
                m_undo_history.push(SavedState{Action::CHANGE_POSITION, it->second.getPosition(), it->second.getObjectIntId()});
                it->second.setPosition(latestChange.position);
                m_change_history.pop();
                std::cout << "Undone position change for object id:" << std::to_string(it->second.getObjectIntId()) << 
                            " latest position: " << it->second.getPosition().toString() << std::endl;
            } 
        }
        break;
    case Action::DELETE:
        {
            m_object_map.emplace(latestChange.id, AudioObject{Id{latestChange.id}, latestChange.position});
            m_undo_history.push(SavedState{Action::ADD, latestChange.position, latestChange.id});
            std::cout << "Undone delete for object id:" << std::to_string(latestChange.id) << 
                            " position: " << latestChange.position.toString() << std::endl;
            m_change_history.pop();
        }
        break;
    case Action::ADD:
        {
            if(const auto& it = m_object_map.find(latestChange.id); it != m_object_map.end())
            {
                m_change_history.pop();
                m_undo_history.push(SavedState{Action::DELETE, it->second.getPosition(), it->second.getObjectIntId()});
                std::cout << "Undone add for object id:" << std::to_string(it->second.getObjectIntId()) << 
                            " position: " << it->second.getPosition().toString() << std::endl;
                m_object_map.erase(it->second.getObjectIntId());
            }
        }
        break;
    default:
        std::cout << "No action to undo" << std::endl;
        break;
    }
}
void AudioObjectManager::redo() 
{
    if(m_undo_history.empty())
    {
        std::cout << "No action to redo" << std::endl;
        return;
    }
    const auto &latestUndo = m_undo_history.top();

    switch (latestUndo.action)
    {
    case Action::CHANGE_POSITION:
        {
            if(const auto& it = m_object_map.find(latestUndo.id); it != m_object_map.end())
            {
                m_change_history.push(SavedState{Action::CHANGE_POSITION, it->second.getPosition(), it->second.getObjectIntId()});
                it->second.setPosition(latestUndo.position);
                m_undo_history.pop();
                std::cout << "Redone position change for object id:" << std::to_string(it->second.getObjectIntId()) << 
                            " latest position: " << it->second.getPosition().toString() << std::endl;
            } 
        }
        break;
    case Action::DELETE:
        {
            m_change_history.push(SavedState{Action::ADD, latestUndo.position, latestUndo.id});
            m_object_map.emplace(latestUndo.id, AudioObject{Id{latestUndo.id}, latestUndo.position});
            std::cout << "Redone add for object id:" << std::to_string(latestUndo.id) << 
                            " position: " << latestUndo.position.toString() << std::endl;
            m_undo_history.pop();
        }
        break;
    case Action::ADD:
        {
            if(const auto& it = m_object_map.find(latestUndo.id); it != m_object_map.end())
            {
                m_change_history.push(SavedState{Action::DELETE, it->second.getPosition(), it->second.getObjectIntId()});
                m_undo_history.pop();
                std::cout << "Redone delete for object id:" << std::to_string(it->second.getObjectIntId()) << 
                            " position: " << it->second.getPosition().toString() << std::endl;
                m_object_map.erase(it->second.getObjectIntId());
            }
        }
        break;
    default:
        break;
    }
}

void AudioObjectManager::printAll() 
{
    std::cout << "ALL OBJECT STATES:" << std::endl;
    for(auto const& [key, val] : m_object_map)
    {
        std::cout << std::to_string(key)
              << ':' 
              << val.getPosition().toString()
              << std::endl;
    }
}