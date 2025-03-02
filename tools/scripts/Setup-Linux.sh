#!/bin/bash

pushd ../..
tools/bin/Premake/Linux/premake5 --cc=clang gmake2
popd
