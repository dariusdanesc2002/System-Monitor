# System Monitor

This is a terminal-based system monitor written in C++ that provides real-time information about your system's performance. The program displays information such as CPU usage, memory utilization, total and running processes, uptime, and a list of the top processes.

## Features

* **System Information**: Displays the operating system and kernel versions.
* **Resource Utilization**: Shows a progress bar for CPU and memory usage.
* **Process Management**: Lists the total number of processes and the number of currently running processes.
* **Uptime**: Displays the system's uptime in a formatted string (HH:MM:SS).
* **Process Details**: Shows a list of processes with details including PID, user, CPU usage, RAM usage, and command.

## Dependencies

This project requires the **ncurses** library for the terminal-based user interface. The `CMakeLists.txt` file is configured to find this package, and the build will fail if it is not installed.

## Building and Running

The project uses CMake for its build system. Follow these steps to build and run the application:

1.  **Clone the repository and navigate to the project directory.**
2.  **Create a build directory and run CMake:**
    ```bash
    mkdir build
    cd build
    cmake ..
    ```
3.  **Build the executable:**
    ```bash
    make
    ```
    This will create an executable named `monitor`.
4.  **Run the program:**
    ```bash
    ./monitor
    ```
5.  **Exit the program:**
    To stop the monitor, press the `q` key in the terminal.
