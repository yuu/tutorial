#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <sstream>

struct MyRecord
{
    int32_t x, y;
    float z;

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( x, y, z );
    }

    void print()
    {
        std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
    }
};

struct SomeData
{
    int32_t id;
    std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

    template <class Archive>
    void save( Archive & ar ) const
    {
        ar( data );
    }

    template <class Archive>
    void load( Archive & ar )
    {
        static int32_t idGen = 0;
        id = idGen++;
        ar( data );
    }
};

int main()
{
    using T = std::unordered_map<uint32_t, MyRecord>;
    std::stringstream ss;

    {
        cereal::PortableBinaryOutputArchive archive( ss, cereal::PortableBinaryOutputArchive::Options::BigEndian() );
        SomeData myData;

        std::shared_ptr<T> data(new T());
        MyRecord tmp;
        tmp.x = 100;
        tmp.y = 20;
        tmp.z = 300.333;
        data->insert(std::make_pair(1, tmp));
        myData.data = data;

        tmp.print();
        archive( myData );
    }

    std::cout << "above OutputArchive ------- below InputArchive" << std::endl;

    std::shared_ptr<T> data(new T());
    SomeData unzipData;
    unzipData.data = data;
    if (unzipData.data == nullptr) {
        std::cout << "nulllll" << std::endl;
    }

    {
        cereal::PortableBinaryInputArchive unzip( ss );// , cereal::PortableBinaryInputArchive::Options::LittleEndian() );
        unzip( unzipData );
    }
    {
        auto d = unzipData.data;
        if (d != nullptr) {
            for (auto &&x : *d) {
                x.second.print();
            }
        } else {
            std::cout << "unzipData.data is null" << std::endl;
        }

    }

    return 0;
}
