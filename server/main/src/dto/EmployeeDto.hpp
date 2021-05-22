//
// Created by Casey Williams on 22/05/2021.
//

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#ifndef DONARITY_EMPLOYEE_HPP
#define DONARITY_EMPLOYEE_HPP

#include OATPP_CODEGEN_BEGIN(DTO)

class EmployeeDto : public oatpp::DTO {
  DTO_INIT(EmployeeDto, DTO);

  DTO_FIELD(String, firstName);
  DTO_FIELD(String, lastName);
  DTO_FIELD(String, description);
};

#include OATPP_CODEGEN_END(DTO)

#endif //DONARITY_EMPLOYEE_HPP
