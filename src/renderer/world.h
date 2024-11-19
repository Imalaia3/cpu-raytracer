#pragma once
#include "object/object.h"
#include <memory>
#include <vector>

class World {
public:
    World() {};
    void addObject(std::unique_ptr<Object> object);
    const Object* getObjectWithName(std::string& name) const;
    const std::vector<std::unique_ptr<Object>>& getObjects() const { return m_objects; }
    const size_t objectCount() { return m_objects.size(); }
    void clearObjects();
private:
    std::vector<std::unique_ptr<Object>> m_objects;
};