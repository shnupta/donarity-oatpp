//
// Created by Casey Williams on 23/05/2021.
//

#ifndef DONARITY_DATABASECOMPONENT_HPP
#define DONARITY_DATABASECOMPONENT_HPP

#include <db/EmployeeDb.hpp>
#include <dto/ConfigDto.hpp>

class DatabaseComponent {
public:
  OATPP_CREATE_COMPONENT(std::shared_ptr<EmployeeDb>, employeeDb)([] {
    OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Get config component

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config->dbConnectionString);

    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                          10 /* max-connections */,
                                                                          std::chrono::seconds(5) /* connection TTL */);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

    return std::make_shared<EmployeeDb>(executor);
  }());
};

#endif //DONARITY_DATABASECOMPONENT_HPP
