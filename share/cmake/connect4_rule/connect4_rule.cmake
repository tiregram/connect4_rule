get_filename_component(_connectrule_root "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(_connectrule_root "${_connectrule_root}/../../..")
get_filename_component(_connectrule_root "${_curl_root}" ABSOLUTE)

set(
  CONNECTRULE_LIBRARIES
  ${_connectrule_root}/libc4rule.so
  CACHE INTERNAL "" FORCE
)

set(
  CONNECTRULE_INCLUDE_DIRS
  ${_connectrule_root}/include
  CACHE INTERNAL "" FORCE
)

qi_persistent_set(CONNECTRULE_DEPENDS)
export_lib(CONNECTRULE)
