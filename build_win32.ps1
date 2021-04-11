# requires python.exe
# requires cl.exe
# requires link.exe
# requires $env:DEVKIT_LOCATION

#
# Compile
#

$stopwatch = [system.diagnostics.stopwatch]::startNew()
$t0 = $stopwatch.ElapsedMilliseconds

Write-Host "(1) Parsing.."

& python .\scripts\mfn.py parse

$env:CMDC_VERSION = "0.1.1"
$env:DISTUTILS_USE_SDK = 1
$env:MSSdk = 1

$t1 = $stopwatch.ElapsedMilliseconds

$parse_duration = $t1 - $t0

Write-Host "(1) Finished in $parse_duration ms"
Write-Host "(1) ----------------------------"
Write-Host "(2) Compiling.."

# Make build directory, unless one already exists
md -Force build | Out-Null

& cl.exe `
    /Tpsrc/main.cpp `
    /Fobuild/main.obj `
    /c `
    /nologo `
    /Ox `
    /MD `
    /W3 `
    /GS- `
    /DNDEBUG `
    -DVERSION_INFO="$env:CMDC_VERSION" `
    -I "$env:DEVKIT_LOCATION\include" `
    -I "$env:DEVKIT_LOCATION\include\Python" `
    -I "$pwd\include" `
    /std:c++latest `
    /wd5033 `
    /EHsc `
    /bigobj


#
# Link
#

$t2 = $stopwatch.ElapsedMilliseconds
$compile_duration = $t2 - $t1

Write-Host "(2) Finished in $compile_duration ms"
Write-Host "(2) ----------------------------"
Write-Host "(3) Linking.."

& link.exe `
    /DLL `
    /nologo `
    /INCREMENTAL:NO `
    "/LIBPATH:$env:DEVKIT_LOCATION\lib" `
    "/LIBPATH:$pwd\lib" `
    Foundation.lib `
    OpenMaya.lib `
    OpenMayaRender.lib `
    OpenMayaUI.lib `
    OpenMayaAnim.lib `
    OpenMayaFX.lib `
    /EXPORT:initcmdc `
    build\main.obj `
    "/OUT:$pwd\build\cmdc.pyd" `
    "/IMPLIB:$pwd\build\cmdc.lib" `
    "/MANIFESTFILE:$pwd\build\cmdc.pyd.manifest"

$t3 = $stopwatch.ElapsedMilliseconds
$link_duration = $t3 - $t2

Write-Host "(3) Finished in $link_duration ms"
Write-Host "(3) ----------------------------"
Write-Host "(4) Cleaning.."

& python .\scripts\mfn.py clean

$t4 = $stopwatch.ElapsedMilliseconds

$clean_duration = $t4 - $t3
$total_duration = $t4 - $t0

Write-Host "(4) Finished in $clean_duration ms"
Write-Host "(4) ----------------------------"
Write-Host "Successfully created .\build\cmdc.pyd in $total_duration ms"