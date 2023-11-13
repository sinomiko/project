/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cachelib/allocator/CacheAllocator.h"
#include "cachelib/datatype/FixedSizeArray.h"
#include "folly/init/Init.h"
#include <type_traits>
#include <vector>

namespace facebook {
namespace cachelib_examples {
using Cache = cachelib::LruAllocator; // or Lru2QAllocator, or TinyLFUAllocator
using CacheConfig = typename Cache::Config;
using CacheKey = typename Cache::Key;
using CacheReadHandle = typename Cache::ReadHandle;

// Global cache object and a default cache pool
std::unique_ptr<Cache> gCache_;
cachelib::PoolId defaultPool_;

void initializeCache() {
  CacheConfig config;
  config
      .setCacheSize(1 * 1024 * 1024 * 1024) // 1GB
      .setCacheName("My Use Case")
      .setAccessConfig(
          {25 /* bucket power */, 10 /* lock power */}) // assuming caching 20
                                                        // million items
      .validate(); // will throw if bad config
  gCache_ = std::make_unique<Cache>(config);
  defaultPool_ =
      gCache_->addPool("default", gCache_->getCacheMemoryStats().cacheSize);
}

void destroyCache() { gCache_.reset(); }

CacheReadHandle get(CacheKey key) { return gCache_->find(key); }

bool put(CacheKey key, const std::string& value) {
  auto handle = gCache_->allocate(defaultPool_, key, value.size());
  if (!handle) {
    return false; // cache may fail to evict due to too many pending writes
  }
  std::memcpy(handle->getMemory(), value.data(), value.size());
  gCache_->insertOrReplace(handle);
  return true;
}

class Foo
{
  public:
  Foo(){}

  Foo(int a_, int b_):a(a_),b(b_)
  {

  }

  virtual ~Foo(){}
  int a = 0;
  int b = 1;
};

bool put(CacheKey key, const Foo& value) {
  auto handle = gCache_->allocate(defaultPool_, key, sizeof(Foo));
  if (!handle) {
    return false; // cache may fail to evict due to too many pending writes
  }
  std::memcpy(handle->getMemory(), &value, sizeof(Foo));
  new (handle->getMemory()) Foo(value.a, value.b);
  gCache_->insertOrReplace(handle);
  return true;
}

} // namespace cachelib_examples
} // namespace facebook

using namespace facebook::cachelib_examples;
struct LargeUserData {
  uint64_t version;
  uint64_t timestamp;
  size_t length;
  std::vector<uint32_t> data;
};

int main(int argc, char** argv) {
  folly::init(&argc, &argv);

  initializeCache();
  std::cout << std::boolalpha;
  std::cout << "is_pod(Foo)" << std::is_pod<Foo>::value 
  << ",is_pod(std::string):" << std::is_pod<std::string>::value << std::endl;

  
  // Use cache
  {
    auto res = put("key", "value");
    std::ignore = res;
    assert(res);

    auto item = get("key");
    folly::StringPiece sp{reinterpret_cast<const char*>(item->getMemory()),
                          item->getSize()};
    std::ignore = sp;
    std::cout << sp << std::endl;
    assert(sp == "value");
  }
  // Use cache
  {
    Foo foo(1,4);
    auto res = put("foo", foo);
    std::ignore = res;
    assert(res);

    auto item = get("foo");
    const Foo* foo_ptr = reinterpret_cast<const Foo*>(item->getMemory());
    if (foo_ptr)
    {
      std::cout << "foo_ptr,a:" << foo_ptr->a << ",b:" << foo_ptr->b << std::endl;
    }
  }

  using Array = ::facebook::cachelib::FixedSizeArray<uint32_t, Cache>;
  {
    auto array =
        Array{gCache_->allocate(defaultPool_, "array",
                              Array::computeStorageSize(1024*1024*0.955 /* numElements */)),
              1024*1024*0.955 /* numElements */};
    std::cout << array.isNullItemHandle() << std::endl;
    for (uint32_t i = 0; i < array.size(); ++i) {
      array[i] = i;
    }
    std::vector<uint64_t> vec{2,2,3,4,5,6};
    array.copyFrom(vec.begin(), vec.end());
    // for (uint32_t i = 0; i < array.size(); ++i) {
    //   std::cout << i << "->" << array[i] << std::endl;
    // }
    gCache_->insertOrReplace(array.viewItemHandle());
  }

 {
    auto array =
          Array::fromItemHandle(gCache_->find("array", ::facebook::cachelib::AccessMode::kRead));

      // for (uint32_t i = 0; i < array.size(); ++i) {
      //   std::cout << i << "->" << array[i] << std::endl;
      // }
      std::cout << "array:->" << array.size()<< std::endl;
  }

  std::vector<uint32_t> vec{1,2,3,4,5};
  uint32_t* p =  vec.data();
  for (size_t i = 0; i < vec.size(); i++)
  {

    std::cout << *p++ << std::endl;

  }

  struct CustomParentItem {
    size_t numChunks;
    void* dataPtr[];  // an array of pointers to the chunks
  };
  std::vector<uint32_t> in_pre;
  {

    // std::unique_ptr<LargeUserData> userData = getLargeUserData();
    std::unique_ptr<LargeUserData> userData(new LargeUserData());
    size_t x = 1024*1024*1 + 1024;
    // userData->length = x;
    for (size_t i = 0; i < x; i++)
    {
      userData->data.push_back(i);
    }
    userData->data.shrink_to_fit();

    size_t userDataSize = sizeof(uint32_t) * userData->data.size();

    // For simplicity, we'll split the user data into 1MB chunks
    size_t numChunks = (userDataSize + (1024 * 1024 - 1)) / (1024 * 1024);



    size_t parentItemSize = sizeof(CustomParentItem) + numChunks * sizeof(void*);

    // for simplicity, assume this fits into 1MB
    assert(parentItemSize <(1024 * 1024));

    auto parentItemHandle =
        gCache_->allocate(defaultPool_, "chunk1", parentItemSize);

    CustomParentItem* parentItem =
        reinterpret_cast<CustomParentItem*>(parentItemHandle->getMemory());

    // Now split user data into chunks and cache them
    std::cout << "parentItemSize:" << parentItemSize  << "numChunks:" << numChunks << ", userDataSize:" << userDataSize << std::endl;

    for (size_t i = 0; i < numChunks; ++i) {
      size_t chunkSize = 1024 * 1024;
      auto chainedItemHandle =
          gCache_->allocateChainedItem(parentItemHandle, chunkSize);

      // For simplicity, assume we always have enough memory
      assert(chainedItemHandle != nullptr);

      // Compute user data offset and copy data over
      uint8_t* dataOffset =
          reinterpret_cast<uint8_t*>(userData->data.data()) + chunkSize * i;
      in_pre.push_back(*((uint32_t*)dataOffset));
      std::cout << *((uint32_t*)dataOffset) << std::endl;
      if (userDataSize <= chunkSize * i + chunkSize)
      {
        std::cout << "chunkSize * i " << chunkSize * i + chunkSize << std::endl;
        chunkSize = userDataSize - chunkSize * i;
      }
      
      std::memcpy(chainedItemHandle->getMemory(), dataOffset, chunkSize);

      // Add this chained item to the parent item
      gCache_->addChainedItem(parentItemHandle, std::move(chainedItemHandle));
    }
    // Now, make parent item visible to others
    gCache_->insert(parentItemHandle);

  }

  {
    auto res = gCache_->inspectCache("chunk1");
    std::cout << "first:" << res.first << std::endl;
    std::cout << "second:" << res.second << std::endl;
    auto handle = gCache_->find("chunk1");
    auto chainedAllocs =  gCache_->viewAsChainedAllocs(handle);

    std::cout << "computeChainLength:" << chainedAllocs.computeChainLength() << std::endl;;

    // // Confirm we have all the chained item iobufs
    int i = chainedAllocs.computeChainLength();
    auto x = in_pre.crbegin();
    for (const auto& c : chainedAllocs.getChain()) {

      const uint32_t* item =
            reinterpret_cast<const uint32_t*>(c.getMemory());

      // std::cout <<  (*item) << std::endl;
      std::cout << (*x == (*item)) << std::endl;
      x++;
      // *reinterpret_cast<const int*>(c.getMemory()))
    }
    // while (parent->hasChainedItem()) {
    //   auto child = alloc.popChainedItem(parent);
    //   ASSERT_NE(nullptr, child);
    //   ++numChildren;

    //   const uint8_t* buf =
    //       reinterpret_cast<const uint8_t*>(child->getMemory());
    //   for (uint8_t k = 0; k < 100; ++k) {
    //     ASSERT_EQ(k, buf[k]);
    //   }
    // }
  }

  destroyCache();
}
