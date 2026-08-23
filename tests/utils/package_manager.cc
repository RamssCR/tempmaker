#include "scaffolder/utils/find_executable.hpp"
#include "scaffolder/utils/package_manager.hpp"
#include <boost/process/v2/environment.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockEnvironmentChecker : public TempMaker::SystemUtils::IEnvironmentChecker {
public:
    MOCK_METHOD(boost::filesystem::path, find_executable, (std::string_view), (const, override));
};

using ::testing::Return;
using ::testing::InSequence;

TEST(PackageManager, GetsAnEmptyListOfPackageManagers) {
    MockEnvironmentChecker mock{};
    EXPECT_CALL(mock, find_executable(testing::_)).Times(5);

    const auto result{TempMaker::SystemUtils::check_package_managers(mock)};
    EXPECT_TRUE(result.empty());
}

TEST(PackageManager, GetsNPMAndDenoInstalled) {
    MockEnvironmentChecker mock{};

    {
        InSequence seq{};

        EXPECT_CALL(mock, find_executable("npm"))
            .WillOnce(Return(boost::filesystem::path{"/usr/bin/npm"}));

        EXPECT_CALL(mock, find_executable("yarn"))
            .WillOnce(Return(boost::filesystem::path{""}));

        EXPECT_CALL(mock, find_executable("pnpm"))
            .WillOnce(Return(boost::filesystem::path{""}));

        EXPECT_CALL(mock, find_executable("deno"))
            .WillOnce(Return(boost::filesystem::path{"/usr/bin/deno"}));

        EXPECT_CALL(mock, find_executable("bun"))
            .WillOnce(Return(boost::filesystem::path{""}));
    }

    const auto result{TempMaker::SystemUtils::check_package_managers(mock)};

    EXPECT_THAT(result, ::testing::ElementsAre("npm", "deno"));
    EXPECT_EQ(result.size(), 2);
}

TEST(PackageManager, GetsAllPackageManagersInstalled) {
    MockEnvironmentChecker mock{};

    EXPECT_CALL(mock, find_executable(testing::_))
        .Times(5)
        .WillRepeatedly(Return(boost::filesystem::path{"/usr/bin/default"}));

    auto result{TempMaker::SystemUtils::check_package_managers(mock)};

    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.size(), 5);
    EXPECT_THAT(result, ::testing::ElementsAre("npm", "yarn", "pnpm", "deno", "bun"));
}