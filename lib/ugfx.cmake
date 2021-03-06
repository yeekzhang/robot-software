find_package(SDL2 REQUIRED)

add_definitions(-DGFX_OS_PRE_INIT_FUNCTION=sdl_driver_init)
add_definitions(-DGDISP_SCREEN_WIDTH=480)
add_definitions(-DGDISP_SCREEN_HEIGHT=320)

set(UGFX ugfx)

set(SOURCES
    ${UGFX}/src/gfx.c
    ${UGFX}/src/gdriver/gdriver.c
    ${UGFX}/src/gqueue/gqueue.c
    ${UGFX}/src/gdisp/gdisp.c
    ${UGFX}/src/gdisp/gdisp_fonts.c
    ${UGFX}/src/gdisp/gdisp_pixmap.c
    ${UGFX}/src/gdisp/gdisp_image.c
    ${UGFX}/src/gdisp/gdisp_image_native.c
    ${UGFX}/src/gdisp/gdisp_image_gif.c
    ${UGFX}/src/gdisp/gdisp_image_bmp.c
    ${UGFX}/src/gdisp/gdisp_image_jpg.c
    ${UGFX}/src/gdisp/gdisp_image_png.c
    ${UGFX}/src/gdisp/mcufont/mf_encoding.c
    ${UGFX}/src/gdisp/mcufont/mf_font.c
    ${UGFX}/src/gdisp/mcufont/mf_justify.c
    ${UGFX}/src/gdisp/mcufont/mf_kerning.c
    ${UGFX}/src/gdisp/mcufont/mf_rlefont.c
    ${UGFX}/src/gdisp/mcufont/mf_bwfont.c
    ${UGFX}/src/gdisp/mcufont/mf_scaledfont.c
    ${UGFX}/src/gdisp/mcufont/mf_wordwrap.c
    ${UGFX}/src/gevent/gevent.c
    ${UGFX}/src/gtimer/gtimer.c
    ${UGFX}/src/gwin/gwin.c
    ${UGFX}/src/gwin/gwin_widget.c
    ${UGFX}/src/gwin/gwin_wm.c
    ${UGFX}/src/gwin/gwin_console.c
    ${UGFX}/src/gwin/gwin_graph.c
    ${UGFX}/src/gwin/gwin_button.c
    ${UGFX}/src/gwin/gwin_slider.c
    ${UGFX}/src/gwin/gwin_checkbox.c
    ${UGFX}/src/gwin/gwin_image.c
    ${UGFX}/src/gwin/gwin_label.c
    ${UGFX}/src/gwin/gwin_radio.c
    ${UGFX}/src/gwin/gwin_list.c
    ${UGFX}/src/gwin/gwin_progressbar.c
    ${UGFX}/src/gwin/gwin_container.c
    ${UGFX}/src/gwin/gwin_frame.c
    ${UGFX}/src/gwin/gwin_tabset.c
    ${UGFX}/src/gwin/gwin_gl3d.c
    ${UGFX}/src/gwin/gwin_keyboard.c
    ${UGFX}/src/gwin/gwin_keyboard_layout.c
    ${UGFX}/src/gwin/gwin_textedit.c
    ${UGFX}/src/ginput/ginput.c
    ${UGFX}/src/ginput/ginput_mouse.c
    ${UGFX}/src/ginput/ginput_keyboard.c
    ${UGFX}/src/ginput/ginput_keyboard_microcode.c
    ${UGFX}/src/ginput/ginput_toggle.c
    ${UGFX}/src/ginput/ginput_dial.c
    ${UGFX}/src/gmisc/gmisc.c
    ${UGFX}/src/gmisc/gmisc_arrayops.c
    ${UGFX}/src/gmisc/gmisc_matrix2d.c
    ${UGFX}/src/gmisc/gmisc_trig.c
    ${UGFX}/src/gmisc/gmisc_hittest.c
    ${UGFX}/drivers/multiple/SDL/gdisp_lld_SDL.c
)

if (APPLE) # MacOS
    set(SOURCES ${SOURCES} ${UGFX}/src/gos/gos_osx.c)
elseif (UNIX) # Linux
    set(SOURCES ${SOURCES} ${UGFX}/src/gos/gos_linux.c)
else()
    message(FATAL_ERROR "Supported platforms: Linux and MacOS")
endif()

add_library(ugfx ${SOURCES})

target_include_directories(ugfx PUBLIC ${UGFX} ${UGFX}/src ${UGFX}/drivers/multiple/SDL)
target_link_libraries(ugfx ${SDL2_LIBRARY})
target_include_directories(ugfx PUBLIC ${SDL2_INCLUDE_DIR})

# Defined in other projects
target_link_libraries(ugfx gfxconf)

if(APPLE)
    target_compile_definitions(ugfx PUBLIC "GFX_USE_OS_OSX=GFXON")
elseif (UNIX) # Linux
    target_compile_definitions(ugfx PUBLIC "GFX_USE_OS_LINUX=GFXON")
else()
    message(FATAL_ERROR "Supported platforms: Linux and MacOS and ChibiOS")
endif()

