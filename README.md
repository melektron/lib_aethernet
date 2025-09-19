
# lib_aethernet: Non-blocking Ethernet for Arduino

![Check Arduino status](https://github.com/melektron/lib_aethernet/actions/workflows/check-arduino.yml/badge.svg)
![Compile Examples status](https://github.com/melektron/lib_aethernet/actions/workflows/compile-examples.yml/badge.svg)
![Spell Check status](https://github.com/melektron/lib_aethernet/actions/workflows/spell-check.yml/badge.svg)

With the Arduino Ethernet Shield or any other system using the [WIZnet W5100](https://docs.wiznet.io/Product/iEthernet/W5100/overview) IC, this library allows an Arduino board to communicate via Ethernet.

Unlike the [original Arduino Ethernet library](https://github.com/arduino-libraries/Ethernet), this fork adds the following new features:
- Non-blocking TCP client class that allows the management of a TCP socket without blocking up to 1s until it is connected.

For more information about the original library, please visit the official Arduino Website:
https://www.arduino.cc/en/Reference/Ethernet

Added functionality is not documented there but may have in-code documentation comments.


## Why is it called like this?

My naming scheme for libraries is `lib_{whateveritdoes}`. The `a` in `aethernet` implies that this is a library for the Arduino Framework. Besides, it's a nice play on words.


## Disclaimer

This library is a fork of the original and is purely maintained by `melektron`. It has no affiliation with `Arduino LLC` whatsoever.


## License

Copyright (c) 2010 Arduino LLC. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
