#ifndef P11_03_HPP
#define P11_03_HPP

#include <functional>
#include <memory>
#include <unordered_map>

namespace ya_cpp::p11_03 {

template <class T, class... U>
class FactoryImpl : public FactoryImpl<T>, public FactoryImpl<U...> {};

template <class T> class FactoryImpl<T> {
  protected:
    std::function<T()> m_creator{};
};

template <class... Ts> struct Factory : public FactoryImpl<Ts...> {
    template <class T> [[nodiscard]] T create() {
        return FactoryImpl<T>::m_creator();
    }
    template <class T> void addCreator(std::function<T()> creator) {
        FactoryImpl<T>::m_creator = std::move(creator);
    }
};

class DynFactory final {
    std::unordered_map<const std::type_info *, std::function<void *()>>
        m_creators;

  public:
    template <class T> void addCreator(std::function<T()> creator) {
        m_creators.try_emplace(&typeid(T), [c = std::move(creator)]() {
            return static_cast<void *>(new T(c()));
        });
    }

    template <class T> std::unique_ptr<T> create() {
        return std::unique_ptr<T>(
            static_cast<T *>(m_creators.at(&typeid(T))()));
    }
};
} // namespace ya_cpp::p11_03

#endif // P11_03_HPP
