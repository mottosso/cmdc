param (
    [string]$maya_version = "2022"
)

docker run -ti --rm `
    -v ${PWD}:/workspace `
    cmdc:${maya_version} `
    mayapy -m nose -xv --exe ./tests