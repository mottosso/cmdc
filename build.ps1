# Example build script for Maya 2020

if (-not (Test-Path env:DEVKIT_LOCATION)) {
    Write-Host "Set the DEVKIT_LOCATION environment variable to the absolute path of Maya's devkit."
    exit(1)
}

if (-not (Test-Path env:MAYA_LOCATION)) {
    Write-Host "Set the MAYA_LOCATION environment variable to the absolute path of Maya's install directory."
    exit(1)
}

# Set the Visual Studio environment for PowerShell
pushd "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build"
cmd /c "vcvars64.bat&set" | foreach {
  if ($_ -match "=") {
    $v = $_.split("="); set-item -force -path "ENV:\$($v[0])"  -value "$($v[1])"
  }
}
popd
Write-Host "Visual Studio 2019 Command Prompt variables set." -ForegroundColor Yellow

# This is Python's convoluted way of letting us use anything other than
# what it has hardcoded as the de-facto compiler for Python, e.g. VS2013
$env:DISTUTILS_USE_SDK = 1
$env:MSSdk = 1

# These get picked up by our setup.py script
$env:INCLUDE_PATH = $env:DEVKIT_LOCATION + "\include"
# $env:INCLUDE_PATH += ";" + $env:VCTOOLSINSTALLDIR + "include"
$env:INCLUDE_PATH += ";" + $env:DEVKIT_LOCATION + "\include\Python"
$env:LIBRARY_PATH = $env:DEVKIT_LOCATION + "\lib"
# $env:LIBRARY_PATH += ";" + $env:VCTOOLSINSTALLDIR + "lib\x64"
$env:LIBRARIES = "OpenMaya OpenMayaRender OpenMayaUI OpenMayaAnim OpenMayaFX"

# python27.lib is the only holdout from the devkit, bummer
$env:LIBRARY_PATH += ";$env:MAYA_LOCATION\lib"

# Clean previous build  (may not exist, that's OK)
remove-item ./install/cmdc.pyd

& "$env:MAYA_LOCATION/bin/mayapy.exe" .\Scripts\mfn.py parse
& "$env:MAYA_LOCATION/bin/mayapy.exe" -m pip install  ./ --target ./install
& "$env:MAYA_LOCATION/bin/mayapy.exe" .\Scripts\mfn.py clear