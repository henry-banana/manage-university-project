// --- START OF MODIFIED FILE src/core/data_access/mock/MockSalaryRecordDao.cpp ---
#include "MockSalaryRecordDao.h"
#include "../../entities/SalaryRecord.h"
#include "../../../common/ErrorType.h"
#include <map>
#include <vector>
#include <algorithm>
#include <expected>

namespace {
    std::map<std::string, SalaryRecord> mock_salary_records_data;
    bool mock_salary_record_data_initialized_flag = false;
}

void MockSalaryRecordDao::initializeDefaultMockData() {
    if (!mock_salary_record_data_initialized_flag) {
        mock_salary_records_data.clear();
        mock_salary_records_data.emplace("T001", SalaryRecord("T001", 15000000)); 
        mock_salary_records_data.emplace("T002", SalaryRecord("T002", 20000000)); 
        mock_salary_record_data_initialized_flag = true;
    }
}

void MockSalaryRecordDao::clearMockData() {
    mock_salary_records_data.clear();
    mock_salary_record_data_initialized_flag = false;
}

MockSalaryRecordDao::MockSalaryRecordDao() {
    // Constructor không tự động init data
}

std::expected<SalaryRecord, Error> MockSalaryRecordDao::getById(const std::string& teacherId) const {
    auto it = mock_salary_records_data.find(teacherId);
    if (it != mock_salary_records_data.end()) {
        return it->second;
    }
    return std::unexpected(Error{ErrorCode::NOT_FOUND, "Mock SalaryRecord for Teacher ID " + teacherId + " not found."});
}

std::expected<std::vector<SalaryRecord>, Error> MockSalaryRecordDao::getAll() const {
    std::vector<SalaryRecord> records;
    for (const auto& pair : mock_salary_records_data) {
        records.push_back(pair.second);
    }
    return records;
}

std::expected<SalaryRecord, Error> MockSalaryRecordDao::add(const SalaryRecord& salaryRecord) {
    ValidationResult vr = salaryRecord.validateBasic();
    if (!vr.isValid) {
        return std::unexpected(Error{ErrorCode::VALIDATION_ERROR, "Invalid SalaryRecord data: " + vr.errors[0].message});
    }
    if (mock_salary_records_data.count(salaryRecord.getTeacherId())) {
        return std::unexpected(Error{ErrorCode::ALREADY_EXISTS, "Mock SalaryRecord for Teacher ID " + salaryRecord.getTeacherId() + " already exists."});
    }
    auto insert_result = mock_salary_records_data.emplace(salaryRecord.getTeacherId(), salaryRecord);
    if (!insert_result.second) {
        return std::unexpected(Error{ErrorCode::OPERATION_FAILED, "Failed to emplace salary record into mock data."});
    }
    return salaryRecord;
}

std::expected<bool, Error> MockSalaryRecordDao::update(const SalaryRecord& salaryRecord) {
    ValidationResult vr = salaryRecord.validateBasic();
    if (!vr.isValid) {
        return std::unexpected(Error{ErrorCode::VALIDATION_ERROR, "Invalid SalaryRecord data for update: " + vr.errors[0].message});
    }
    auto it = mock_salary_records_data.find(salaryRecord.getTeacherId());
    if (it != mock_salary_records_data.end()) {
        it->second = salaryRecord;
        return true;
    }
    return std::unexpected(Error{ErrorCode::NOT_FOUND, "Mock SalaryRecord for Teacher ID " + salaryRecord.getTeacherId() + " not found for update."});
}

std::expected<bool, Error> MockSalaryRecordDao::remove(const std::string& teacherId) {
    if (mock_salary_records_data.erase(teacherId) > 0) {
        return true;
    }
    return std::unexpected(Error{ErrorCode::NOT_FOUND, "Mock SalaryRecord for Teacher ID " + teacherId + " not found for removal."});
}

std::expected<bool, Error> MockSalaryRecordDao::exists(const std::string& teacherId) const {
    return mock_salary_records_data.count(teacherId) > 0;
}
// --- END OF MODIFIED FILE src/core/data_access/mock/MockSalaryRecordDao.cpp ---