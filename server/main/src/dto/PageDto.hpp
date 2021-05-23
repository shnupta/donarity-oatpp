//
// Created by Casey Williams on 23/05/2021.
//

#ifndef DONARITY_PAGEDTO_HPP
#define DONARITY_PAGEDTO_HPP

#include "dto/EmployeeDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class EmployeePageDto : public PageDto<oatpp::Object<EmployeeDto>> {
  DTO_INIT(EmployeePageDto, PageDto<oatpp::Object<EmployeeDto>>)
};

#endif //DONARITY_PAGEDTO_HPP
