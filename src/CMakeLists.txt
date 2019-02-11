# Copyright 2016 Gábor Mező (gabor.mezo@outlook.com)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if(WIN32)
  file(GLOB SRC *.h* *.c*)
  set(WIN_DELAY_LOAD_HOOK "win_delay_load_hook.cc")
else()
  file(GLOB SRC *.h* *.c*)
  list(FILTER SRC EXCLUDE REGEX ".*win_delay_load_hook.cc$")
endif()

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries (${PROJECT_NAME}
  ${CMAKE_JS_LIB}
  ${DYNCALL_LIBRARIES}
  ${DYNCALLBACK_LIBRARIES}
  ${DYNLOAD_LIBRARIES})

if(MSVC)
  set(node_host_binary node)
  add_compile_definitions(HOST_BINARY=\"${node_host_binary}${CMAKE_EXECUTABLE_SUFFIX}\")
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/DELAYLOAD:${node_host_binary}${CMAKE_EXECUTABLE_SUFFIX}")
endif()

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  PREFIX "" 
  SUFFIX ".node")
