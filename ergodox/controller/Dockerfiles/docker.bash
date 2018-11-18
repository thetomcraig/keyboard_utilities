#!/usr/bin/env bash
# This is bash lib file for testing out dockerfiles
# Don't call this script directly
# Jacob Alexander 2018
set -e

# Generate the docker image
docker build -f "${Dockerfile}" -t "${Dockerimage}" ..
return_code=$?

if [[ "$return_code" -ne "0" ]] ; then
	echo "Error in build. Exiting..."
	exit $return_code
fi



#############
# Run Tests #
#############

# Remove old directories
sudo rm -rf ../Keyboards/Testing/linux-gnu.* ../Keyboards/linux-gnu.*

# Build Host-Side KLL
docker run -t --rm -v "$(pwd)/..:/controller" -w "/controller/Keyboards/Testing" "${Dockerimage}" /bin/bash -c "PIPENV_ACTIVE=1 GITHUB_APIKEY=${GITHUB_APIKEY} ./klltest.bash"

# Build Firmware
docker run -t --rm -v "$(pwd)/..:/controller" -w "/controller/Keyboards" "${Dockerimage}" /bin/bash -c "PIPENV_ACTIVE=1 GITHUB_APIKEY=${GITHUB_APIKEY} ./whitefox.bash"



# Done
echo "Dockerfile test is complete"

