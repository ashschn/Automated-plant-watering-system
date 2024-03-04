# Automated Plant Watering System

## Description
This project works to automate the plant watering process for indoor house plants. It includes various sensors and actuators that monitor the moisture in the soil and waters the plant when the soil becomes dry enough. It also monitors the temperature and humidity in the plant's environment and the water levels of source water and displays the information on the LCD so the user can easily monitor the system. 

The heart of the system is the Arduino AtMega2560 where all sensors are controlled from. Notably, no external libraries were used aside from <avr/io.h> (to get appropriate IO definitions for the Arduino) and <util/delay.h> (for delays when initalizing). Otherwise, all device drivers for peripheral devices were created from scratch. 

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
The project status stands as stated in the Project Description section. For future work, a schematic needs to be added to the documentation that shows connections between devices. Another feature to be added is to allow the user to input a type of plant, which will modify the level of dryness the soil must meet before it is watered. For example, drought tolerante plants like cactuses need to be drier than most other plants before it needs to be watered.
