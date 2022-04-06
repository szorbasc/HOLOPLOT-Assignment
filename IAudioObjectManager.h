#pragma once
namespace holoplot {
struct Id;
struct Position;
class AudioObject;
class IAudioObjectManager
{
    public:
    virtual ~IAudioObjectManager() = default;
    virtual void add(const AudioObject &) = 0;
    virtual void remove(const Id &) = 0;
    virtual void changePosition(const Id &, const Position &) = 0;
    virtual void undo() = 0;
    //extra
    virtual void redo() = 0;
    virtual void printAll() = 0;
};
}
