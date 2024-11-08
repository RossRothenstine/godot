#!/usr/bin/env bash

set -uo pipefail

scons platform=android target=template_release arch=arm32
scons platform=android target=template_release arch=arm64
scons platform=android target=template_release arch=x86_32
scons platform=android target=template_release arch=x86_64 generate_apk=yes

scons platform=android target=template_debug arch=arm32
scons platform=android target=template_debug arch=arm64
scons platform=android target=template_debug arch=x86_32
scons platform=android target=template_debug arch=x86_64 generate_apk=yes

