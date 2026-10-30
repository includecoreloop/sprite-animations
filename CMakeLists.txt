cmake_minimum_required(VERSION 4.0)
project(sprite-animations CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sprite-animations src/game/main.cpp)

target_sources(sprite-animations PRIVATE
        src/engine/ecs/ecs.hpp

        src/engine/core/config.hpp
        src/engine/core/math.hpp

        src/engine/components/transform.hpp
        src/engine/components/render.hpp
        src/engine/components/sprite.hpp
        src/engine/components/animated_sprite.hpp

        src/engine/systems/animation_system.cpp
        src/engine/systems/animation_system.hpp

        src/asset/SDL3/texture_manager.cpp
        src/asset/SDL3/texture_manager.hpp

        src/game/context.hpp

        src/game/scene.cpp
        src/game/scene.hpp

        src/game/prefabs/unit_prefab.cpp
        src/game/prefabs/unit_prefab.hpp
        src/game/prefabs/unit_attack_prefab.cpp
        src/game/prefabs/unit_attack_prefab.hpp
        src/game/prefabs/dude_prefab.cpp
        src/game/prefabs/dude_prefab.hpp
        src/game/prefabs/fire_prefab.cpp
        src/game/prefabs/fire_prefab.hpp
        src/game/prefabs/sword_prefab.cpp
        src/game/prefabs/sword_prefab.hpp

        src/game/tags.hpp

        src/game/systems/SDL3/render_system.cpp
        src/game/systems/SDL3/render_system.hpp
        src/game/systems/npc_system.cpp
        src/game/systems/npc_system.hpp

)

if (MSVC)
    set(SDL3_BASE_DIR "${CMAKE_SOURCE_DIR}/external/SDL3/SDL3-devel-3.4.18-VC/SDL3-3.4.18")
    set(SDL3_LIB_PATH "${SDL3_BASE_DIR}/lib/x64/SDL3.lib")
    set(SDL3_DLL_PATH "${SDL3_BASE_DIR}/lib/x64/SDL3.dll")

    set(SDL_IMAGE_BASE_DIR "${CMAKE_SOURCE_DIR}/external/SDL3/SDL3_image-devel-3.4.8-VC/SDL3_image-3.4.8")
    set(SDL_IMAGE_LIB_PATH "${SDL_IMAGE_BASE_DIR}/lib/x64/SDL3_image.lib")
    set(SDL_IMAGE_DLL_PATH "${SDL_IMAGE_BASE_DIR}/lib/x64/SDL3_image.dll")

    set(PLATFORM_LIBS "")
elseif (MINGW)
    add_link_options(-static -static-libgcc -static-libstdc++)

    set(SDL3_BASE_DIR "${CMAKE_SOURCE_DIR}/external/SDL3/SDL3-devel-3.4.18-mingw/SDL3-3.4.18/x86_64-w64-mingw32")
    set(SDL3_LIB_PATH "${SDL3_BASE_DIR}/lib/libSDL3.dll.a")
    set(SDL3_DLL_PATH "${SDL3_BASE_DIR}/bin/SDL3.dll")

    set(SDL_IMAGE_BASE_DIR "${CMAKE_SOURCE_DIR}/external/SDL3/SDL3_image-devel-3.4.8-mingw/SDL3_image-3.4.8/x86_64-w64-mingw32")
    set(SDL_IMAGE_LIB_PATH "${SDL_IMAGE_BASE_DIR}/lib/libSDL3_image.dll.a")
    set(SDL_IMAGE_DLL_PATH "${SDL_IMAGE_BASE_DIR}/bin/SDL3_image.dll")

    set(PLATFORM_LIBS mingw32)
else ()
    message(FATAL_ERROR "Unsupported platform or compiler!")
endif ()

target_include_directories(sprite-animations PRIVATE
        "${SDL3_BASE_DIR}/include"
        "${SDL_IMAGE_BASE_DIR}/include"
)

target_link_libraries(sprite-animations PRIVATE
        "${SDL3_LIB_PATH}"
        "${SDL_IMAGE_LIB_PATH}"
        ${PLATFORM_LIBS}
)

if (WIN32)
    add_custom_command(
            TARGET sprite-animations POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${SDL3_DLL_PATH}"
            "$<TARGET_FILE_DIR:sprite-animations>/SDL3.dll"
            COMMENT "Copying SDL3.dll to output folder..."
    )

    add_custom_command(
            TARGET sprite-animations POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${SDL_IMAGE_DLL_PATH}"
            "$<TARGET_FILE_DIR:sprite-animations>/SDL3_image.dll"
            COMMENT "Copying SDL3_image.dll to output folder..."
    )
endif ()

add_custom_command(
        TARGET sprite-animations POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:sprite-animations>/assets"
        COMMENT "Copying assets directory to output folder..."
)

if (MINGW)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    foreach (MINGW_DLL libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)
        if (EXISTS "${MINGW_BIN_DIR}/${MINGW_DLL}")
            add_custom_command(
                    TARGET sprite-animations POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${MINGW_BIN_DIR}/${MINGW_DLL}"
                    "$<TARGET_FILE_DIR:sprite-animations>/${MINGW_DLL}"
                    COMMENT "Copying ${MINGW_DLL} to output folder..."
            )
        endif ()
    endforeach ()
endif ()