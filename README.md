# A Coefficient of Restitution Testing System for Baseballs

The central task of this project was to design and construct a system to reliably and accurately determine the COR of a baseball with a piece of wood as a function of the relative velocity between the two bodies. This system was designed as part of an interdisciplinary one month CAPSTONE project.

An air cannon, optical laser gate, collision tube assembly was created to determine the coefficient of restitution (CoR) between a baseball and a piece of wood as a function of the relative velocity between the two bodies. A PVC compressed air cannon rated for 120 psi accelerated a baseball to speeds nearing 70 mph, and an optical laser gate captured the speed of the baseball before and after a collision with a piece of wood (ash or pine). The collision was facilitated by a collision tube racked at the end of the cannon barrel. Values for COR from baseball to baseball were consistent to within plus or minus 0.4 at various inbound velocities between 20 and 70 mph. The COR appeared to decrease as the inbound velocity increased. However, not enough data were collected to confidently apply a mathematical model to relate the two quantities. The coefficient of determination for two attempted linear fits were 0.59 and 0.78.

by Adam Woo, Dana Wensberg

## Hardware

Here is a list of the selected hardware:

### Speed Gate
| Component | Model | Description | Price |
| --- | --- | --- | --- |
| Microcontroller | [DFRobot Romeo Board](https://www.dfrobot.com/product-844.html) | The Romeo board is a microcontroller based on the ATmega32u4 chip, like the Arduino Leonardo. While the Romeo board was designed for robotics, the only special features used of this board were the built in buttons to control the system. This board was a loan from the Trinity College Engineering Department. | $0 (Retail: ~$35) |
| LCD | [DFR0063](https://www.dfrobot.com/product-135.html) | This I2C 16x2 Arduino LCD Screen is using an I2C communication interface. It means it only needs 4 pins for the LCD display: VCC, GND, SDA, SCL. It will saves at least 4 digital / analog pins on Arduino. This component was a loan from the Trinity College Engineering Department. | $0 (Retail: ~$35) |
| Lasers |  [6x Generic 650nm 5V Diode Lasers](http://amzn.to/2hCx2co) | Any 5V laser could be used for this project. These were chosen because of their small form factor and cheap price. | ~$3.50 |
| Photodiodes | [6x Generic 5MM Photodiode](http://amzn.to/2zOcfr7) | Photodiodes provide a faster response time than photosensitive resistors or transistors. | ~$1.50 |

### Air Cannon
| Component | Part | Description | Price |
| --- | --- | --- | --- |
| Cannon Materials | Schedule 40 PVC | Rated for high psi and inexpensive | ~$20 |
| Adhesives | Oatey PVC Cement | Adhesive rated for 120 psi. This adhesive was a loan from the Trinity College Engineering Department. | ~$0 |
| Quick Release | Irritrol 205TF 1” Glove valve and a Neiko 31112 Air Blow Gun Oversized Trigger | To create the quick release valve, we modified a sprinkler solenoid valve. Instructions can be read in the report | ~$32.50 |
| Testing Surface | Ash Wood | A custom cut block of ash was used as a testing surface to mimic the materials used in baseball bats | ~$10 |
| Pump | Generic Bike Pump | Any bike pump with a standard schrader valve will fit our system | ~$20 |
