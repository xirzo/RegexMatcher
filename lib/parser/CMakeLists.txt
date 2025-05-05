add_library(parser STATIC ./src/parser.cpp ./src/lexer.cpp ./src/ast.cpp ./src/matcher.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(parser_headers INTERFACE)

target_include_directories(
  parser_headers
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

target_include_directories(
  parser
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(parser PUBLIC parser_headers)
