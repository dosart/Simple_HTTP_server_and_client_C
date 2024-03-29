# 📢 echo-server

This project is a simple implementation of a TCP echo server using BSD sockets that I put together to explore different methods of synchronous I/O multiplexing in a Linux environment. It allows for the selection of a multiplexing method using an application argument. Available methods are select, poll, and epoll, and each method has performance and cross-platform compatibility trade-offs.

*Note*: this program uses epoll, a Linux kernel system call, so it can only be compiled in a Linux environment.

## Usage
```
echo_server 8080 epoll
```
- `arg[1]` the port you want the server to bind to.
- `arg[2]` the multiplexing method you want to use (select, poll, or epoll).

Both arguments are required.

The simplest way to test the server is using `telnet`.

## Synchronous I/O multiplexing methods

| Method  | Summary |
| ------------- | ------------- |
| [select()](https://man7.org/linux/man-pages/man2/select.2.html) | <ul><li>The primary advantage is portability. BSD sockets and WINSOCK interfaces fully support it.</li> <li>It can only monitor up to 1024 file descriptors. Unix man recommends that modern applications use `poll()` or `epoll()`.</li> <li>It isn't very efficient. The kernel has to iterate through the max file descriptor value, even when a single file descriptor is watched.</li> <li>File descriptor sets are reconstructed on return, so each subsequent call must reinitialize them.</li></ul>  |
| [poll()](https://man7.org/linux/man-pages/man2/poll.2.html) | <ul><li>It improves on the `select()` method, but it's only available in UNIX.</li><li>It stores file descriptors in an array, so it doesn't need to iterate through the max file descriptor value.</li><li>The `poll()` system call separates input and output events, allowing the array to be reused without having to reinitialize it.</li><li>The time complexity of `poll()`, like `select()` is O(n), and it's still a slow solution when a large number of file descriptors is used.</li></ul> |
| [epoll()](https://man7.org/linux/man-pages/man7/epoll.7.html) | <ul><li>It performs better than `select()` and `poll()`, but it's only available on Linux and not standardized by POSIX.</li><li>The time complexity of `epoll()` is O(1).</li><li>`epoll_wait()` only returns file descriptors ready for IO operations, so there's no need to iterate through the entire set.</li><li>It allows adding and removing file descriptors while waiting.</li><li>It can be used either as an edge-triggered or a level-triggered interface.</li></ul> |
