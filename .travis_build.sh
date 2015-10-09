#!/bin/bash

set -ex

case ${TRAVIS_OS_NAME} in
linux)
    BUILD_IMPL=${BUILD_IMPL:-${IMPL}}
    impl=$(echo "${IMPL}" | tr '[:upper:]' '[:lower:]')
    build_impl=$(echo "${BUILD_IMPL}" | tr '[:upper:]' '[:lower:]')

    docker pull kanaka/mal-test-${impl}
    if [ "${impl}" != "${build_impl}" ]; then
        docker pull kanaka/mal-test-${build_impl}
    fi
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} id || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} touch /root/.multirust/blah || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} mount || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} ls -alrt / || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} ls -alrt /root/ || true
    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} ls -alrt /root/.multirust/ || true

    docker run -it -u $(id -u) -v `pwd`:/mal kanaka/mal-test-${build_impl} make -C ${BUILD_IMPL}
    ;;
osx)
    make -C ${IMPL}
    ;;
esac
