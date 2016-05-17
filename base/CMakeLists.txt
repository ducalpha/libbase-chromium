project (BASE_CHROMIUM CXX)

add_definitions (-DNDEBUG)

file (GLOB BASE_CHROMIUM_SRC 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/debug/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/files/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/numerics/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/posix/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/process/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/strings/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/synchronization/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/third_party/icu/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nspr/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/time/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/threading/*.cc")

add_library (base_chromium STATIC ${BASE_CHROMIUM_SRC})
target_link_libraries (base_chromium log)
