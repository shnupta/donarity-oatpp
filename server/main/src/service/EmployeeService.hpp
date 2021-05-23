//
// Created by Casey Williams on 23/05/2021.
//

#ifndef DONARITY_EMPLOYEESERVICE_HPP
#define DONARITY_EMPLOYEESERVICE_HPP

#include "db/EmployeeDb.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class EmployeeService {
private:
  typedef oatpp::web::protocol::http::Status Status;
  OATPP_COMPONENT(std::shared_ptr<EmployeeDb>, employeeDb); // Inject database component
public:
  oatpp::Object<EmployeeDto> getEmployee() const;
};


#endif //DONARITY_EMPLOYEESERVICE_HPP
