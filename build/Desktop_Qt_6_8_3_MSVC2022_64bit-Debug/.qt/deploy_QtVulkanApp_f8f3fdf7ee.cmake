include("C:/UnrealProjects/PhysicsRollingBall/Comp2Ball/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtVulkanApp-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/UnrealProjects/PhysicsRollingBall/Comp2Ball/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/QtVulkanApp.exe
    GENERATE_QT_CONF
)
