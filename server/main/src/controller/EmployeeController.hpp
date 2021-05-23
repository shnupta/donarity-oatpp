//
// Created by Casey Williams on 22/05/2021.
//

#ifndef DONARITY_EMPLOYEECONTROLLER_HPP
#define DONARITY_EMPLOYEECONTROLLER_HPP

#include <service/EmployeeService.hpp>
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "../dto/EmployeeDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class EmployeeController : public oatpp::web::server::api::ApiController {
private:
  typedef EmployeeController __ControllerType;
  EmployeeService m_employeeService;

public:
  EmployeeController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}

public:
  static std::shared_ptr<EmployeeController> createShared( OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
    return std::make_shared<EmployeeController>(objectMapper);
  }

public:
  ENDPOINT_INFO(Employees) {
    info->summary = "Get one employee";

    info->addResponse<Object<EmployeeDto>>(Status::CODE_200, "application/json");
//    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
//    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

//    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT_ASYNC("GET", API_BASE "/employees", Employees) {
  ENDPOINT_ASYNC_INIT(Employees)

  Action act() override {

    auto dto = EmployeeDto::createShared();
    dto->firstName = "Casey";
    dto->lastName = "Williams";
    dto->description = "Imperial Student";

    return _return(controller->createDtoResponse(Status::CODE_200, controller->m_employeeService.getEmployee()));
  }

  };
};


#include OATPP_CODEGEN_END(ApiController)

#endif //DONARITY_EMPLOYEECONTROLLER_HPP
