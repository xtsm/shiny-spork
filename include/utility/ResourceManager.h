#ifndef INCLUDE_UTILITY_RESOURCEMANAGER_H_
#define INCLUDE_UTILITY_RESOURCEMANAGER_H_
#include <vector>

class ResourceManager<T> {
 public:
  ResourceManager() = default;

  ResourceManager(const std::initializer_list<T>&);

  void AddNewResource(T resource) {
    resources_.push_back(resource);
  }

  std::vector<T> GetAllResources() const {
    return resources_;
  }

  T& operator[](size_t index) {
    if (index >= resources_.size()) {
      throw std::illegal_argument("Wrong index to ResourceManager!");
    }
    return resources_[index];
  }

  const T& operator[](size_t index) const {
    if (index >= resources_.size()) {
      throw std::illegal_argument("Wrong index to ResourceManager!");
    }
    return resources_[index];
  }

  void Clear() {
    resources_.clear();
  }

 private:
  std::vector<T> resources_;
};

#endif  // INCLUDE_UTILITY_RESOURCEMANAGER_H_
