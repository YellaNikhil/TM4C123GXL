**Hello!** 

This is a Repository for Bare Metal Device Drivers for TIVA Series Board **TM4C123GXL** Evaluation Board.
I have built this repo mainly to get the hand-on learning of Bare Metal Programming by reading the datasheets of Components, Microcontroller etc.,.

I will update the repo as needed whenever possible. It has basic GPIO to Communication Protocol Drivers.
Please feel free to fork the library or clone it.

If you want to contribute to the project, Please do make a pull request and send the results, will merge it into master.

We can use this project on several OS environments and with different IDEs. Following contains branches that has instructions to setup build environements on differnet platforms.

Linux with VSCodeIDE Makefile build:- [`2025/feature/makefile_build_ubuntu_from_keil_windows`](https://github.com/YellaNikhil/TM4C123GXL/tree/2025/feature/makefile_build_ubuntu_from_keil_windows).

Windows Keil IDE :- [main](https://github.com/YellaNikhil/TM4C123GXL/tree/main)

Please do checkout below links for ARM-toolchain setup on Ubuntu if you are working on Makefile based projects.

A fellow developer has clear instructions on why we use Makefile and set it up on Ubuntu Environment.
https://www.shawndsilva.com/blog/embedded%20systems/makefiles-for-embedded-systems
https://github.com/shawn-dsilva/tm4c-linux-template/blob/master/README.md

And to setup any IDE to use OpenOCD combined with GNU Debugger to debug or flash the hardware.
Checkout the below video: https://www.youtube.com/watch?v=FNDp1G0bYoU, following video gives explanation for STM32 but can be used for TIVA board as well.

For TM4c123GXL Launchpad, use the below path which has correct configuration:

`/usr/share/openocd/scripts/board/ti_ek-tm4c123gxl.cfg`

Thank you.
