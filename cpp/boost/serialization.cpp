#include <fstream>
#include <string>
#include <cassert>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Person {
public:
    Person() {}
    Person(std::string const& name, int age):name_(name), age_(age) {}
    std::string const& name() const { return name_; }
    int age() const { return age_; }
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, unsigned int const /*version*/)
    {
        ar & name_;
        ar & age_;
    }
    std::string name_;
    int age_;
};

int main()
{
    {
        Person p1("Akira", 25);
        std::ofstream ofs("persion.txt");
        boost::archive::text_oarchive oa(ofs);
        oa << p1;
    }
    {
        std::ifstream ifs("persion.txt");
        boost::archive::text_iarchive ia(ifs);
        Person p2;
        ia >> p2;
        assert(p2.name() == "Akira");
        assert(p2.age() == 25);
    }
}
