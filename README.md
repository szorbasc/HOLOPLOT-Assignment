# HOLOPLOT-Interview
HOLOPLOT Interview task in C++

My take on the assignment which they cannot give feedback and expected a bit more..

## DESCRIPTION
```
3D Object-based audio applications work with the concept of Audio objects - entities
consisting of audio data and metadata. For this assignment, we will not deal with the
audio data and assume that an AudioObject contains only two metadata members:
Position (3D) and Id. The goal of this task is to implement an AudioObjectManager class
which correctly implements the functions defined in the provided abstract base class
interface. The functions are actions which change the state of the AudioObjects and
should be implemented in the following way:
● add - adds a new AudioObject to the AudioObjectManager. Undoing this action
means removing the added object (with the same unique Id)
● remove - removes an existing AudioObject which has previously been added to
the manager. Undoing this action means re-creating the removed object
● changePosition - changes the Position member of the audio object with the
selected Id. Note: Undoing this action should revert the Position of the object
with the selected Id not only to the previous Position after the last
changePosition action, but to the Position held by this object before all
successive (!) changePosition actions for this object. In other words, all
successive changePosition actions for a specific object (“successive” in the sense
that they are not interleaved with different action types) shall be reverted
altogether by a single undo operation.
Eg. if we on one hand start with an object at Position A, move it sequentially to Position B
and C and undo, the Position of the object should be Position A again. If we on the other
HOLOPLOT GmbH
Ringbahnstrasse 10-14, 12099 Berlin, Germany 1 / 3
hand start with the same object at Position A, move it to Position B,
add/remove/changePosition of a different object, then move the first object sequentially
to Position C and D, after applying undo, the Position of the first object should be B
● undo - reverts the effects of the last action as described above. In the case of
sequential changePosition actions done on the same object, reverts to the state
before the first changePosition action for that action in the sequence
Please implement the functions as described and also fill in a simple implementation of
the declared types (Position, Id, AudioObject) as you see fit. Provide a solution which can
correctly demonstrate the state of AudioObjects after the following sequence of actions:
● Add object with first id and position A
● Add object with second id and position B
● Change position of object with first id to position C
● Add object with third id and position D
● Change position of object with second id to position E
● Remove object with first id
● Change position of object with third id to position F
● Change position of object with third id to position G
● Undo
● Undo
The correct state of objects present in the AudioObjectManager is the following:
● Object with first id has position C
● Object with second id has position E
● Object with third id has position D
Optional: For an additional challenge feel free to extend your implementation with a
redo functionality.
IAudioObjectManager.h
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
};
}
```
