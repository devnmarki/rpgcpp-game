#ifndef TILEMAPUTILS_HPP
#define TILEMAPUTILS_HPP

#include <string>

#include <tmxlite/Object.hpp>

inline const tmx::Property* getObjectProperty(const tmx::Object& object, const std::string& propertyName) {
    for (const auto& prop : object.getProperties()) {
        if (prop.getName() == propertyName) {
            return &prop;
        }
    }
    return nullptr;
}

#endif