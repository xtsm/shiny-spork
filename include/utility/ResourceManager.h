#ifndef INCLUDE_UTILITY_RESOURCEMANAGER_H_
#define INCLUDE_UTILITY_RESOURCEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <stdexcept>
#include <cassert>

template<typename T>
class ResourceManager {
 public:
  ResourceManager() noexcept
      : resources_() {
    assert(typeid(T) == typeid(sf::Image)
                      || typeid(T) == typeid(sf::Texture)
                      || typeid(T) == typeid(sf::Font));
  }

  std::map<std::string, T> GetAllResources() const {
    return resources_;
  }

  T& GetOrLoadResource(const std::string& path) {
    if (resources_.count(path) == 0) {
      T new_resource;
      new_resource.loadFromFile(path);
      resources_.emplace(path, new_resource);
    }
    return resources_.at(path);
  }

  void Clear() {
    resources_.clear();
  }

 private:
  std::map<std::string, T> resources_;
};

#endif  // INCLUDE_UTILITY_RESOURCEMANAGER_H_
