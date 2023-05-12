#define AddRadars(kind)                                                                           \
    if (!radar_topics.kind.empty()) {                                                             \
        m.emplace(radar_topics.kind,                                                            \
                  [this]() { _##kind## _sub.addMessage(_bag.messageInstantiate<RadarMsgType>()); }); \
    }

AddRadars(bumper_radar);

// 上面的 radar_topic.kind.empty()， 不用加 ##。 是因为 . 本身也会当作 token来用. See https://stackoverflow.com/questions/13216423/error-pasting-and-red-does-not-give-a-valid-preprocessing-token
//
// 上面的 ##kind## 其实是为了把 tokenize the kind, so 
// `_##kind##_sub` will be tokenized to `_`, `kind`, `_` and `sub`
// See https://complete-concrete-concise.com/programming/c/preprocessor-the-token-pasting-operator/

