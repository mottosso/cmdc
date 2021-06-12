param (
    [string]$maya_version = "2022"
)

docker run -ti --rm `
    -v ${PWD}:/workspace `
    cmdc:${maya_version} `
     ./build_linux.sh $maya_version
