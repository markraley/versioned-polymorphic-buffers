#!/usr/bin/bash

pushd ./vectors
./setup_all.sh
./run_all.sh
./check_all.sh
popd

pushd ./maps
./setup_all.sh
./run_all.sh
./check_all.sh
popd
