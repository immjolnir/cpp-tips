
# What's the difference between mutex and recursive_mutex?

If a thread tries to acquire a mutex it already has, it will block and you'll have a deadlock. A recursive (or reentrant) mutex can be acquired multiple times by the same thread.



# C++ Concurrency In Action Second EDITION


## 4.6 fetch the result by std::future


