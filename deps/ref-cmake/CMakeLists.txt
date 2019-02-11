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

file(GLOB SRC ../ref/src/*.h* ../ref/src/*.c*)

if(WIN32)
  set(WIN_DELAY_LOAD_HOOK "../../src/win_delay_load_hook.cc")
  list (APPEND SRC ${WIN_DELAY_LOAD_HOOK})
endif()

add_library(ref SHARED ${SRC})

target_link_libraries (ref ${CMAKE_JS_LIB})

if(MSVC)
  set(node_host_binary node)
  add_compile_definitions(HOST_BINARY=\"${node_host_binary}${CMAKE_EXECUTABLE_SUFFIX}\")
  set_target_properties(ref PROPERTIES LINK_FLAGS "/DELAYLOAD:${node_host_binary}${CMAKE_EXECUTABLE_SUFFIX}")
endif()

set_target_properties(
  ref
  PROPERTIES
  PREFIX "" 
  SUFFIX ".node")
