#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <type_traits>

#define ROS_PLUS_MESSAGE_TRAITS(msgType)                                                \
    namespace ros {                                                                     \
    namespace message_traits {                                                          \
    template <>                                                                         \
    struct TimeStamp<msgType> {                                                         \
        static ros::Time value(const msgType& m) { return ros::Time(m.header.seq, 0); } \
    };                                                                                  \
    }                                                                                   \
    }

namespace ros {
namespace message_filters {

template <typename K, typename V>
class Filter {
  public:
    template <typename C0, typename C1>
    void registerCallback(C0&& c0, C1&& c1) {
        _pivotal_cb = std::forward<C0>(c0);
        _message_cb = std::forward<C1>(c1);
    }

    void addPivot(uint32_t seq, K pivot) {
        assert(!!_pivotal_cb);
        _pivotal_cb(seq, pivot);
    }

    V getMessage() {
        assert(!!_message_cb);

        K key = _message_cb();
        auto iter = _data.lower_bound(key);
        if (iter != _data.end()) {
            return iter->second;
        } else {
            // LOG(ERROR) << "Failed to find it";
            std::cerr << "Failed to find it: " << key << std::endl;
            // return std::nullptr;
            return {};
        }
    }

    void addMessage(const K& key, const V& value) { _data.emplace_hint(_data.end(), key, value); }

  private:
    std::map<K, V> _data;

    std::function<void(uint32_t, K)> _pivotal_cb;
    std::function<K()> _message_cb;
};

template <typename T, typename I>
struct n_tuple_helper {};

template <typename T, std::size_t... I>
struct n_tuple_helper<T, std::index_sequence<I...>> {
    using type = std::tuple<std::enable_if_t<I || true, T>...>;
};

template <typename T, std::size_t N>
class Message {
  public:
    template <class... Filters>
    Message(Filters... filters) {
        static_assert(sizeof...(Filters) == N, "The Filter's size must be exactly as N");
        std::tuple<Filters...> t{filters...};
        registerImpl(t, std::index_sequence_for<Filters...>{});
    }

    bool next() {
        if (!_pivotal_times.empty()) {
            clearOldPivotalTimes();
            return true;
        } else {
            return false;
        }
    }

  private:
    template <typename Tuple, std::size_t... Is>
    void registerImpl(Tuple& t, std::index_sequence<Is...>) {
        ((std::get<Is>(t)->registerCallback(
           [this](uint32_t seq, T pivot) { return this->template set<Is>(seq, pivot); },
           [this]() { return this->template get<Is>(); })),
         ...);
    }

    template <int i>
    void set(uint32_t seq, T t) {
        auto& tuple = _pivotal_times[seq];
        std::get<i>(tuple) = t;
    }

    template <int i>
    T get() {
        auto& tuple = _pivotal_times.begin()->second;
        return std::get<i>(tuple);
    }

    void clearOldPivotalTimes() { _pivotal_times.erase(_pivotal_times.begin()); }

  private:
    typedef typename n_tuple_helper<T, std::make_index_sequence<N>>::type PivotalTimes;
    std::map<uint32_t, PivotalTimes> _pivotal_times;
};

}  // namespace message_filters
}  // namespace ros
/*
template <typename T>
void extractProtoMessage(const std::string& bag_file,
                         const std::string& topic,
                         std::function<void(const T& msg)> func) {
    BagInterface bag;
    bag.open(bag_file);
    std::vector<std::string> topics{topic};
    bag.initialize(topics);

    while (!bag.end()) {
        T msg;
        if (msg.ParseFromString(bag.messageInstantiate<std_msgs::String>()->data)) {
            func(msg);
        } else {
            LOG(ERROR) << "Failed to parse " << bag.topic();
        }
        bag.next();
    }

    bag.close();
}

template <typename T>
void resetHeader(T& ptr, uint32_t pivotal_id) {
    typedef std::remove_cv_t<typename T::element_type> element_type;
    element_type* elem = const_cast<element_type*>(ptr.get());
    elem->header.seq = pivotal_id;
}
*/
