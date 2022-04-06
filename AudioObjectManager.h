#pragma once
#include "IAudioObjectManager.h"
#include <unordered_map>
#include "AudioObject.h"

namespace holoplot {

// Implemented as singleton. We expect to have one globally accesible object manager.
class AudioObjectManager : public IAudioObjectManager
{
    private:
    AudioObjectManager() = default;                                       
    static AudioObjectManager &getInstance()                
    {                                         
        static AudioObjectManager instance;                
        return instance;                      
    }                                         
                                              
    public:                                       
    AudioObjectManager(const AudioObjectManager &) = delete;            
    AudioObjectManager &operator=(const AudioObjectManager &) = delete; 
    AudioObjectManager(AudioObjectManager &&) = delete;                 
    AudioObjectManager &operator=(AudioObjectManager &&) = delete;      
    static AudioObjectManager *getInstancePtr()            
    {                                         
        return &(getInstance());              
    }
    
    public:
    ~AudioObjectManager() = default;
    
    void add(const AudioObject &audioObject) override final;
    void remove(const Id &id) override final;
    void changePosition(const Id &id, const Position &position) override final;
    void undo() override final;
    void redo() override final;
    void printAll() override final;

    private:
    std::unordered_map<int, AudioObject> m_object_map{};
    std::stack<SavedState> m_change_history{};
    std::stack<SavedState> m_undo_history{};
};
}