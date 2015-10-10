#!/bin/bash

set -ex

# If NO_DOCKER is blank then launch use a docker image, otherwise
# use the Travis image/tools directly.
if [ -z "${NO_DOCKER}" ]; then
    BUILD_IMPL=${BUILD_IMPL:-${IMPL}}
    impl=$(echo "${IMPL}" | tr '[:upper:]' '[:lower:]')
    build_impl=$(echo "${BUILD_IMPL}" | tr '[:upper:]' '[:lower:]')

    docker pull kanaka/mal-test-${impl}
    if [ "${impl}" != "${build_impl}" ]; then
        docker pull kanaka/mal-test-${build_impl}
    fi
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} make -C ${BUILD_IMPL}
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal bash -c "set" || true
    #docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal bash -c "cd miniMAL && node -e \"console.log(require('ffi'))\"" || true
    #docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal bash -c "cd miniMAL && node -e \"console.log(require('./node_modules/ffi/lib/ffi.js'))\"" || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal bash -c "cd miniMAL && node node_readline.js" || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal node miniMAL/node_readline.js || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal bash -c "cd miniMAL && node ffi_test.js" || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-minimal node miniMAL/ffi_test.js || true
else
    make -C ${IMPL}
fi
