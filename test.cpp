//
// Created by azathoth on 2021/12/10.
//

#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
using namespace std;

template <class K, class V>
std::string mapToString(map<K, V> m) {
    std::stringstream s;
    s << "begin traverse map:" << endl;

    for (const auto &i : m) {
        s << i.first << "\t" << i.second << "\n";
    }
    s << endl;
    return s.str();
}

template <class C>
std::ostream &containerToString(std::ostream &s, C const &c) {
    std::copy(c.begin(), c.end(), std::ostream_iterator<class C::value_type>(s, " "));
    return s;
}

template <class C>
std::string containerToString(C const &c) {
    std::stringstream s;
    s << "begin traverse container:" << endl;

    for (const auto &i : c) {
        s << i << "\t";
    }
    s << endl;
    return s.str();
}

// decltype(std::declval<C>().insert(std::declval<T>()), C{}) fillContainer(C c) {
//     std::for_each(in<T>(std::cin), in<T>(), [&c](T const &t) { c.insert(t); });
//     return c;
// }
//
// template <class C>
// decltype(std::declval<C>().insert(std::declval<typename C::value_type>()), std::declval<C &>()) fillContainer(C &c) {
//     using T = typename C::value_type;
//     std::for_each(in<T>(std::cin), in<T>(), [&c](T const &t) { c.insert(t); });
//     return c;
// }

void map_test() {
    using dataIndex = size_t;
    using subString = string;
    using maptype = map<dataIndex, subString>;
    maptype m;
    m[15] = "mark!";
    m[5] = " world";
    m[0] = "hello";
    m[11] = "I'm ";
    mapToString(m);

    auto it = m.begin();
    it++;

    m.erase(m.begin(), it);

    cout << mapToString(m);
}

void map_test2() {
    using dataIndex = size_t;
    using subString = string;
    map<dataIndex, subString> m;
    m[15] = "mark!";
    m[5] = " world";
    m[0] = "hello";
    m[11] = "I'm ";
    //    mapToString(m);

    auto it = m.begin();
    cout << it->first << endl;
}

void set_test() {
    using setT = set<string>;
    setT s = {"a", "gf", "zf", "ge"};
    cout << containerToString<setT>(s);
}

void string_test() {
    string s = "hello, my friend";
    string s1;
    if (s1.empty()) {
        cout << "empty" << endl;
    }
    //    cout << s.substr(s.size() - 1) << endl;
}

void stupid_test() {
    int i = 0;
    int j = 0;
    while (j < 5) {
        j++;
    }
    for (i = 0; i < 5; i++) {
    }
    cout << "i: " << i << endl;
    cout << "j: " << j << endl;
}

int main() {
    //    map_test();
    //    map_test2();
    set_test();
    //    string_test();
}