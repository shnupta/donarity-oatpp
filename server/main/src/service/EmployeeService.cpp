//
// Created by Casey Williams on 23/05/2021.
//

#include "EmployeeService.hpp"

oatpp::Object<EmployeeDto> EmployeeService::getEmployee() const {
  auto dbResult = employeeDb->getEmployeeFromFirstName("Casey");
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<EmployeeDto>>>();
  return result[0];
}
