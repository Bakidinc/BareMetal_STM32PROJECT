🚀 STM32 Bare-Metal Programming Series

This project was created to document my learning journey of bare-metal (library-free) programming on the STM32F410RB (Nucleo-64) microcontroller. As an embedded software engineer, through this step into the world of embedded systems, I aim to dive into the deepest levels of hardware and develop systems that are efficient, reliable, and highly optimized.

🛠️ Development Environment and Tools

The project has a two-stage structure:

BaremetalF410rbgit
The initial setup and fundamental configuration stages of the project were carried out using STM32CubeIDE.

Bare_Metal_Series
All other application code, drivers, and register-level developments were written in VS Code, using OpenOCD, ARM GNU Toolchain, and Cortex-Debug.

📚 References and Resources

While developing this project, the following technical documents and valuable content creators were utilized:

📄 Technical Documents

STM32F410x8 / STM32F410xB Datasheet
For hardware specifications and pin configurations.

RM0401 Reference Manual
STM32F410 advanced Arm®-based 32-bit MCUs
(For register details and peripheral management).

🎥 Educational Channels

Low Byte Productions (lowbyteproductions) – Bare Metal Programming Series

AsabreTech (ebenezerasabre) – Bare Metal Programming STM32

📁 Project Structure

Within the scope of the training series, each topic is organized under a separate directory.

🚀 Getting Started

If you would like to explore or build the project on your local machine:

git clone --recursive https://github.com/Bakidinc/BareMetal_STM32PROJECT.git


Open the project using VS Code and build it via the Makefile located in the relevant project directory.

For debugging, make sure the SVD paths in launch.json point to the STM32F410.svd file.
