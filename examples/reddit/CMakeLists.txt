file(GLOB _REDDIT_SOURCES ./src/*.cpp)

list(APPEND REDDIT_FILES ${_REDDIT_SOURCES})


IF ( BDN_PLATFORM_IOS )
	SET(MACOSX_BUNDLE_BUNDLE_NAME reddit)
	SET(MACOSX_BUNDLE_GUI_IDENTIFIER "io.boden.reddit")
	SET(MACOSX_BUNDLE_LAUNCH_STORYBOARD "LaunchScreen")

	set(REDDIT_ASSETS 
		./ios-assets/Base.lproj/LaunchScreen.storyboard
		./ios-assets/Assets.xcassets)
endif()


add_universal_executable(reddit No ${REDDIT_FILES} ${REDDIT_ASSETS})

set_xcode_property(reddit CODE_SIGN_STYLE Automatic)
set_xcode_property(reddit ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
set_xcode_property(reddit CODE_SIGN_IDENTITY "iPhone Developer")
#set_xcode_property(reddit DEVELOPMENT_TEAM <TeamID>)

use_boden_template_info_plist(reddit)

group_sources_automatically(${CMAKE_CURRENT_SOURCE_DIR} ${REDDIT_FILES})

target_link_libraries(reddit PRIVATE ui foundation net yogalayout nlohmann_json::nlohmann_json)


install(TARGETS reddit
    DESTINATION examples
    COMPONENT Examples)
