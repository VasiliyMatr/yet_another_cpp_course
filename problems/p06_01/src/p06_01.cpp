#include <ya_cpp/p06_01.hpp>

namespace ya_cpp {

const std::string &Entity::data_as_string() const {
    if (m_cached_data.is_invalid) {
        m_cached_data.update(*this);
    }

    return m_cached_data.string;
}

void Entity::set_data_3(int data) {
    m_data_3 = data;

    m_cached_data.is_invalid = true;
}

void Entity::Cached_Data::update(const Entity &entity) {
    string = (std::to_string(entity.m_data_1) + '/' +
              std::to_string(entity.m_data_2) + '/' +
              std::to_string(entity.m_data_3));

    is_invalid = false;
}

} // namespace ya_cpp
