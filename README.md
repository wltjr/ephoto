# ephoto
[![License](http://img.shields.io/badge/license-MIT-blue.svg?colorB=9977bb&style=plastic)](https://github.com/wltjr/ephoto/blob/master/LICENSE)
[![Build Status](https://github.com/wltjr/ephoto/actions/workflows/docker_build.yml/badge.svg)](https://github.com/wltjr/ephoto/actions)
[![Code Quality](https://sonarcloud.io/api/project_badges/measure?project=wltjr_ephoto&metric=alert_status)](https://sonarcloud.io/dashboard?id=wltjr_ephoto)

A comprehensive image viewer written using the core EFL.

This version is a fork, a break from the EFL/Enlightenment community, and
changes here shall not be backported to other versions without retaining
commit history and authorship for proper open source accreditation!

Others may resume their efforts, like all things in FOSS, nobody cares till
you do, then everyone has an opinion and is interested...

Original code/mess by Stephen M Houston/[@okratitan](https://github.com/okratitan)
under BSD Clause, future work is now under MIT license. Thanks to Stephen for
his past efforts being carried forward.

## Build

Meson is the build system used for this project. For more information please
see: [http://mesonbuild.com](http://mesonbuild.com)

### Build using meson

```sh
prefix=/usr/share
meson \
    --prefix "${prefix}" \
    --bindir "${prefix}/bin" \
    --datadir "${prefix}/share" \
    . build
ninja -C build install
```
