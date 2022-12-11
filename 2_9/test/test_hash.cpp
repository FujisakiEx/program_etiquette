#include "../hash.h"
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <iostream>

#include <gtest/gtest.h>

using namespace myhash;

TEST(GTestCheck, Math) {
    EXPECT_EQ(2, 1+1);
}

TEST(HashTest, hash){
    EXPECT_EQ(48, myhash::hash("0"));
    EXPECT_EQ(656, myhash::hash("hello"));
    EXPECT_EQ(804, myhash::hash("world"));
    EXPECT_EQ(584, myhash::hash("hello,world"));
    EXPECT_EQ(216, myhash::hash("hello, world"));
}

TEST(HashTest, basic) {
    // never init, get nullptr
    {
        auto ptr = lookup("hello", true, 0);
        EXPECT_FALSE(ptr);
    }
    // after init, create key
    {
        myhash::init_hash_table();
        myhash::Nameval* ptr = lookup("hello", true, 10);
        EXPECT_TRUE(ptr);
        EXPECT_EQ(ptr->name, "hello");
        EXPECT_EQ(ptr->value, 10);
        EXPECT_FALSE(ptr->next);
    }
    // lookup, but do not create key
    {
        auto ptr = lookup("hello2", false, 10);
        EXPECT_FALSE(ptr);
    }
    // lookup same key, do not update value 
    {
        auto ptr = lookup("hello", true, 12);
        EXPECT_TRUE(ptr);
        EXPECT_EQ(ptr->name, "hello");
        EXPECT_EQ(ptr->value, 10);
        EXPECT_FALSE(ptr->next);
    }
}

static const char charset[] = 
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

template<typename URBG>
std::string gen_string(std::size_t length, URBG&& g) {
    std::string result;
    result.resize(length);
    std::sample(std::cbegin(charset), 
                std::cend(charset),
                std::begin(result),
                std::intptr_t(length),
                std::forward<URBG>(g));
    return result;
}

TEST(HashTest, recreate){
    std::mt19937 gen;
    myhash::init_hash_table();
    uint32_t size = HASH_COUNT * 2;
    std::map<std::string, uint32_t> keyValueMap;

    for(uint32_t i = 0; i < size ; ++i){
        std::string key = gen_string(10, gen);
        if(keyValueMap.count(key) == 0){
            keyValueMap[key] = i;
            lookup(key, true, i);
        }
        // When recreate, i < size. size is too large assumed hash tabel size.
        uint32_t count = get_recreate_count();
        if(count == 2){
            EXPECT_TRUE(i + 1 < size);
            break;
        }
        else if(count > 2){
            break;
        }
        
    }
    // should be recreating table
    EXPECT_EQ(get_recreate_count(), 2);
    for(const auto& kv: keyValueMap){
        auto ptr = lookup(kv.first, false, 0);
        EXPECT_TRUE(ptr);
        EXPECT_EQ(ptr->name, kv.first);
        EXPECT_EQ(ptr->value, kv.second);
    }
    EXPECT_EQ(get_recreate_count(), 2);
}
