# cachelib-demo

## add repo
```bash
sh prerequisites-centos8.sh
```

## dependency
- [liburing-devel](https://vault.centos.org/centos/8/PowerTools/x86_64/os/Packages/liburing-devel-1.0.7-3.el8.x86_64.rpm)
- 依赖安装
```
wget https://vault.centos.org/centos/8/PowerTools/x86_64/os/Packages/liburing-devel-1.0.7-3.el8.x86_64.rpm
sudo rpm -ivh liburing-devel-1.0.7-3.el8.x86_64.rpm

sudo dnf install cachelib-devel folly-devel glog-devel fmt-devel fbthrift-devel double-conversion-devel boost-devel zstd wangle-devel fizz-devel  -y
```





**System**:
[Boost](https://www.boost.org),
[CMake](https://cmake.org),
[OpenSSLv1.0.2g](https://www.openssl.org),
[PThreads](https://computing.llnl.gov/tutorials/pthreads), and
[Zlib](https://zlib.net)

**External**:
[{fmt}](https://github.com/fmtlib/fmt),
[GFlags](https://github.com/gflags/gflags), and
[GLog](https://github.com/google/glog)

**Facebook**:
[Fizz](https://github.com/facebookincubator/fizz),
[Folly](https://github.com/facebook/folly),
[Wangle](https://github.com/facebook/wangle), and
[Zstd](https://github.com/facebook/zstd)