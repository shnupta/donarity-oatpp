//
//  AppComponent.hpp
//  oatpp-web-starter
//
//  Created by Leonid on 3/2/18.
//  Copyright © 2018 lganzzzo. All rights reserved.
//

#ifndef AppComponent_hpp
#define AppComponent_hpp

#include <dto/ConfigDto.hpp>
#include "SitePath.hpp"
#include "StaticFileManager.hpp"
#include "FilesIndex.hpp"

#include "oatpp-libressl/server/ConnectionProvider.hpp"

#include "oatpp-zlib/EncoderProvider.hpp"

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/base/CommandLineArguments.hpp"

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
private:
  oatpp::base::CommandLineArguments m_cmdArgs;
public:
  AppComponent(const oatpp::base::CommandLineArguments& cmdArgs) : m_cmdArgs(cmdArgs) {}
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)("http-provider", [] {
    /* non_blocking connections should be used with AsyncHttpConnectionHandler for AsyncIO */
#if !defined(OATPP_TARGET_APP)
    v_uint16 port = 8000;
#else
    v_uint16 port = 80;
#endif
    return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", port, oatpp::network::Address::IP_4});
  }());
  
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverSecureConnectionProvider)("https-provider", [] {
    /* non_blocking connections should be used with AsyncHttpConnectionHandler for AsyncIO */
#if !defined(OATPP_TARGET_APP)
    v_uint16 port = 8443;
    const char* keyFile = "/usr/local/include/server.key";
    const char* certFile = "/usr/local/include/server.crt";
#else
    v_uint16 port = 443;
    const char* keyFile = "/certificate/oatpp.io.key";
    const char* certFile = "/certificate/oatpp.io.crt";
#endif
    auto config = oatpp::libressl::Config::createDefaultServerConfigShared(certFile, keyFile);
    return oatpp::libressl::server::ConnectionProvider::createShared(config, {"0.0.0.0", port, oatpp::network::Address::IP_4});
  }());
  
  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  
  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)("http-handler", [] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    /* Async ConnectionHandler for Async IO and Coroutine based endpoints */
    auto handler = std::make_shared<oatpp::web::server::AsyncHttpConnectionHandler>(router);
    handler->addRequestInterceptor(std::make_shared<SitePath::RedirectToSecureInterceptor>());
    return handler;
  }());
  
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverSecureConnectionHandler)("http-provider", [] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component

    /* Create HttpProcessor::Components */
    auto components = std::make_shared<oatpp::web::server::HttpProcessor::Components>(router);

    /* Add content encoders */
    auto encoders = std::make_shared<oatpp::web::protocol::http::encoding::ProviderCollection>();

    encoders->add(std::make_shared<oatpp::zlib::DeflateEncoderProvider>());
    encoders->add(std::make_shared<oatpp::zlib::GzipEncoderProvider>());

    components->contentEncodingProviders = encoders;

    /* Async ConnectionHandler for Async IO and Coroutine based endpoints */
    auto handler = std::make_shared<oatpp::web::server::AsyncHttpConnectionHandler>(components);
    handler->addRequestInterceptor(std::make_shared<SitePath::RedirectInterceptor>());
    return handler;
  }());
  
  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
    auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
    deserializerConfig->allowUnknownFields = false;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
    return objectMapper;
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<FilesIndex>, filesIndex)([] {
    auto files = std::make_shared<FilesIndex>(FRONT_PATH);
    files->buildIndex();
    return files;
  }());
  
  OATPP_CREATE_COMPONENT(std::shared_ptr<StaticFileManager>, staticFilesManager)([] {
    return std::make_shared<StaticFileManager>();
  }());

  OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDto>, config)([this] {

    const char* configPath = CONFIG_PATH;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    oatpp::String configText = oatpp::base::StrBuffer::loadFromFile(configPath);
    if (configText) {

      auto profiles = objectMapper->readFromString<oatpp::Fields<oatpp::Object<ConfigDto>>>(configText);

      const char *profileArg = std::getenv("CONFIG_PROFILE"); // first read from env variable
      if (profileArg == nullptr) {
        profileArg = m_cmdArgs.getNamedArgumentValue("--profile", "dev"); // if no env varioable get from command line
      }

      OATPP_LOGD("Server", "Loading configuration profile '%s'", profileArg);

      auto profile = profiles.getValueByKey(profileArg, nullptr);
      if(!profile) {
        throw std::runtime_error("No configuration profile found. Server won't run.");
      }
      return profile;

    }

    OATPP_LOGE("AppComponent", "Can't load configuration file at path '%s'", configPath);
    throw std::runtime_error("[AppComponent]: Can't load configuration file");

  }());
};

#endif /* AppComponent_hpp */
