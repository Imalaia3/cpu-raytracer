#include "world.h"

void World::addObject(std::unique_ptr<Object> object) {
    m_objects.push_back(std::move(object));
}
void World::clearObjects() {
    m_objects.clear(); // smart pointers handle all the deallocations
}
const Object* World::getObjectWithName(std::string& name) const { 
    for (auto &&object : m_objects) {
        if (object.get()->getObjectName() == name)
            return object.get();
    }
    return nullptr;
}