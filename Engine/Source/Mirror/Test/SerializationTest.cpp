//
// Created by johnk on 2023/4/23.
//

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>

#include <gtest/gtest.h>

#include <Mirror/Registry.h>
#include <Mirror/Type.h>

int ga;
float gb;
std::string gc;

struct SerializationTestStruct0 {
    int a;
    float b;
    std::string c;
};

struct SerializationTestStruct1 {
    std::vector<int> a;
    std::unordered_set<std::string> b;
    std::unordered_map<int, std::string> c;
    std::vector<std::vector<bool>> d;
};

struct MirrorInfoRegistry {
    MirrorInfoRegistry()
    {
        Mirror::Registry::Get()
            .Global()
                .Variable<&ga>("ga")
                .Variable<&gb>("gb")
                .Variable<&gc>("gc");

        Mirror::Registry::Get()
            .Class<SerializationTestStruct0>("SerializationTestStruct0")
                .Constructor<>(Mirror::NamePresets::defaultConstructor)
                .MemberVariable<&SerializationTestStruct0::a>("a")
                .MemberVariable<&SerializationTestStruct0::b>("b")
                .MemberVariable<&SerializationTestStruct0::c>("c");

        Mirror::Registry::Get()
            .Class<SerializationTestStruct1>("SerializationTestStruct1")
                .Constructor<>(Mirror::NamePresets::defaultConstructor)
                .MemberVariable<&SerializationTestStruct1::a>("a")
                .MemberVariable<&SerializationTestStruct1::b>("b")
                .MemberVariable<&SerializationTestStruct1::c>("c")
                .MemberVariable<&SerializationTestStruct1::d>("d");
    }
};
static MirrorInfoRegistry registry;

TEST(SerializationTest, VariableFileSerializationTest)
{
    static std::filesystem::path fileName = "../Test/Generated/SerializationTest.VariableFileSerializationTest.bin";
    std::filesystem::create_directories(fileName.parent_path());
    {
        Common::BinaryFileSerializeStream stream(fileName.string());

        ga = 1;
        gb = 2.0f;
        gc = "3";

        const auto& globalScope = Mirror::GlobalScope::Get();
        globalScope.GetVariable("ga").Serialize(stream);
        globalScope.GetVariable("gb").Serialize(stream);
        globalScope.GetVariable("gc").Serialize(stream);
    }

    {
        ga = 4;
        gb = 5.0f;
        gc = "6";

        Common::BinaryFileDeserializeStream stream(fileName.string());

        const auto& globalScope = Mirror::GlobalScope::Get();
        globalScope.GetVariable("ga").Deserialize(stream);
        globalScope.GetVariable("gb").Deserialize(stream);
        globalScope.GetVariable("gc").Deserialize(stream);

        ASSERT_EQ(ga, 1);
        ASSERT_EQ(gb, 2.0f);
        ASSERT_EQ(gc, "3");
    }
}

TEST(SerializationTest, ClassFileSerializationTest)
{
    static std::filesystem::path fileName = "../Test/Generated/SerializationTest.ClassFileSerializationTest.bin";
    std::filesystem::create_directories(fileName.parent_path());
    {
        Common::BinaryFileSerializeStream stream(fileName.string());

        SerializationTestStruct0 obj;
        obj.a = 1;
        obj.b = 2.0f;
        obj.c = "3";

        Mirror::Any ref = std::ref(obj);

        const auto& clazz = Mirror::Class::Get("SerializationTestStruct0");
        clazz.Serialize(stream, &ref);
    }

    {
        Common::BinaryFileDeserializeStream stream(fileName.string());

        const auto& clazz = Mirror::Class::Get("SerializationTestStruct0");
        Mirror::Any obj = clazz.GetConstructor(Mirror::NamePresets::defaultConstructor).ConstructOnStack();
        clazz.Deserailize(stream, &obj);

        const auto& ref = obj.As<const SerializationTestStruct0&>();
        ASSERT_EQ(ref.a, 1);
        ASSERT_EQ(ref.b, 2.0f);
        ASSERT_EQ(ref.c, "3");
    }
}

TEST(SerializationTest, ContainerFileSerializationTest)
{
    static std::filesystem::path fileName = "../Test/Generated/SerializationTest.ContainerFileSerializationTest.bin";
    std::filesystem::create_directories(fileName.parent_path());
    const auto& clazz = Mirror::Class::Get("SerializationTestStruct1");
    {
        Common::BinaryFileSerializeStream stream(fileName.string());

        SerializationTestStruct1 obj;
        obj.a = { 1, 2 };
        obj.b = { "3", "4" };
        obj.c = { { 5, "6" }, { 7, "8" } };
        obj.d = { { false, true }, { true, false } };

        Mirror::Any ref = std::ref(obj);
        clazz.Serialize(stream, &ref);
    }

    {
        Common::BinaryFileDeserializeStream stream(fileName.string());

        Mirror::Any ref = clazz.GetDefaultConstructor().ConstructOnStack();
        clazz.Deserailize(stream, &ref);

        const auto& tRef = ref.As<const SerializationTestStruct1&>();
        ASSERT_EQ(tRef.a.size(), 2);
        ASSERT_EQ(tRef.a[0], 1);
        ASSERT_EQ(tRef.a[1], 2);
        ASSERT_EQ(tRef.b.size(), 2);
        ASSERT_EQ(tRef.b.contains("3"), true);
        ASSERT_EQ(tRef.b.contains("4"), true);
        ASSERT_EQ(tRef.c.size(), 2);
        ASSERT_EQ(tRef.c.at(5), "6");
        ASSERT_EQ(tRef.c.at(7), "8");
        ASSERT_EQ(tRef.d.size(), 2);
        ASSERT_EQ(tRef.d[0].size(), 2);
        ASSERT_EQ(tRef.d[0][0], false);
        ASSERT_EQ(tRef.d[0][1], true);
        ASSERT_EQ(tRef.d[1].size(), 2);
        ASSERT_EQ(tRef.d[1][0], true);
        ASSERT_EQ(tRef.d[1][1], false);
    }
}
