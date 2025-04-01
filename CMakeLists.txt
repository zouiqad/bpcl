cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

#==============================================================
#                           Configuration
#==============================================================
set(PROJECT_NAME "bpcl")
set(EXECUTABLE_NAME "bpcl")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#=====================================
#				Options
#=====================================

if (NOT DEFINED ENV{VCPKG_ROOT})
    message(WARNING "VCPKG_ROOT is not set. Please set it to your local vcpkg path.")
else ()
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif ()

# Explicitly enable the new policy so OPENGL GLVND libraries
if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif ()

#==============================================================
#                           Sources
#==============================================================

set(SOURCES ${CMAKE_SOURCE_DIR}/src/)
set(LIBS ${CMAKE_SOURCE_DIR}/libs/)

#==============================================================
#                           Build
#==============================================================
project(${PROJECT_NAME})
set(CURRENT_TARGET ${EXECUTABLE_NAME})


add_executable(${CURRENT_TARGET} src/main.cpp
        src/components/Camera.h
        src/core/Types.h
        src/core/ComponentArray.h
        src/core/ComponentManager.h
        src/core/Mediator.h
        src/core/EntityManager.h
        src/core/Event.h
        src/core/EventManager.h
        src/core/System.h
        src/core/SystemManager.h
        src/WindowManager.cpp
        src/WindowManager.h
        src/systems/RenderSystem.cpp
        src/systems/RenderSystem.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/Mesh.cpp
        src/graphics/Mesh.h
        src/graphics/Model.cpp
        src/graphics/Model.h
        src/components/Renderable.h
        src/components/Transform.h
        src/systems/CameraControlSystem.cpp
        src/systems/CameraControlSystem.h
        src/graphics/PrimitiveMeshes.h
        src/graphics/Skybox.cpp
        src/graphics/Skybox.h
        src/components/Cubemap.h
        src/systems/SkyboxRenderSystem.cpp
        src/systems/SkyboxRenderSystem.h
        src/GUIManager.cpp
        src/GUIManager.h
        src/core/Logger.h
        src/game/Config.cpp
        src/game/Config.h
        src/graphics/PointCloud.cpp
        src/graphics/PointCloud.h
        src/systems/PointCloudSystem.cpp
        src/systems/PointCloudSystem.h
        src/core/Drawable.h
        src/components/Geometry.h
        src/systems/GeometrySystem.cpp
        src/systems/GeometrySystem.h
)

#==============================================================
#                           Libraries
#==============================================================

target_include_directories(${CURRENT_TARGET} PUBLIC ${SOURCES} PRIVATE ${LIBS})

#==============================================================
#                           Linking
#==============================================================

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)


target_link_libraries(${CURRENT_TARGET} PRIVATE glad::glad glfw imgui::imgui assimp::assimp OpenGL::GL glm::glm)

# Copy the resources directory to the build directory
add_custom_command(TARGET ${CURRENT_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "Copying resources into binary directory")

