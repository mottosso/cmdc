if (-not $args.count) {
 $directory = "./tests"
} else {
 $directory = $args[0]
}

."$env:MAYA_LOCATION/bin/mayapy.exe" -m pytest -xv $directory