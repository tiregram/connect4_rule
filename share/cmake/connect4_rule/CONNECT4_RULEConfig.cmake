get_filename_component(_connectrule_root "${CMAKE_CURRENT_LIST_FILE}" PATH)
message(${_connectrule_root} lapin)
set(_connectrule_root "${_connectrule_root}/../../..")
get_filename_component(_connectrule_root "${_connectrule_root}" ABSOLUTE)

set(
  CONNECT4_RULE_LIBRARIES
  ${_connectrule_root}/libc4rule.so
  CACHE INTERNAL "" FORCE
)

set(
  CONNECT4_RULE_INCLUDE_DIRS
  ${_connectrule_root}/include
  CACHE INTERNAL "" FORCE
)

export_lib(CONNECT4_RULE)
