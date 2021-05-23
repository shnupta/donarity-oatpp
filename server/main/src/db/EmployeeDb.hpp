//
// Created by Casey Williams on 23/05/2021.
//

#ifndef DONARITY_EMPLOYEEDB_HPP
#define DONARITY_EMPLOYEEDB_HPP

#include "../dto/EmployeeDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class EmployeeDb : public oatpp::orm::DbClient {
public:
  EmployeeDb(const std::shared_ptr<oatpp::orm::Executor>& executor) : oatpp::orm::DbClient(executor) {}

public:
  QUERY(getEmployeeFromFirstName,
        "SELECT firstName, lastName, description FROM Employees WHERE firstName=:firstName",
        PREPARE(true),
        PARAM(oatpp::String, firstName))
};


#include OATPP_CODEGEN_END(DbClient)

#endif //DONARITY_EMPLOYEEDB_HPP
