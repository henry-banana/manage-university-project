// --- START OF MODIFIED FILE src/core/data_access/mock/MockLoginDao.h ---
#ifndef MOCKLOGIN_DAO_H
#define MOCKLOGIN_DAO_H

#include "../interface/ILoginDao.h"
#include <map>      // (➕)
#include <string>   // (➕)
// LoginCredentials, UserRole, LoginStatus, Error, std::expected đã được ILoginDao.h include

class MockLoginDao : public ILoginDao {
public:
    MockLoginDao();
    ~MockLoginDao() override = default;

    std::expected<LoginCredentials, Error> findCredentialsByUserId(const std::string& userId) const override;
    std::expected<bool, Error> addUserCredentials(const std::string& userId, const std::string& passwordHash, const std::string& salt, UserRole role, LoginStatus status) override;
    std::expected<bool, Error> updatePassword(const std::string& userId, const std::string& newPasswordHash, const std::string& newSalt) override;
    std::expected<bool, Error> removeUserCredentials(const std::string& userId) override;
    std::expected<UserRole, Error> getUserRole(const std::string& userId) const override;
    std::expected<LoginStatus, Error> getUserStatus(const std::string& userId) const override;
    std::expected<bool, Error> updateUserRoleAndStatus(const std::string& userId, UserRole newRole, LoginStatus newStatus) override;
    std::expected<std::vector<LoginCredentials>, Error> findByStatus(LoginStatus status) const override;

    static void initializeDefaultMockData();
    static void clearMockData();
};

#endif // MOCKLOGIN_DAO_H
// --- END OF MODIFIED FILE src/core/data_access/mock/MockLoginDao.h ---