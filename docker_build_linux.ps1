param (
    [string]$maya_version = "2020"
)

docker run -ti --rm `
    -v ${env:DEVKIT_LOCATION}:/devkit `
    -v ${PWD}:/workspace `
    -e DEVKIT_LOCATION=/devkit `
    cmdc ./build_linux.sh $maya_version
