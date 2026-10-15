# Warehouse-Order-Processing-and-Truck-Dispatch-Simulation
C++ warehouse simulation using FIFO queues and a LIFO stack to manage order processing, truck loading, and dispatch over 50 simulated days.
# Warehouse Order Processing and Truck Dispatch Simulation

## Overview

A C++ console application that simulates warehouse order processing and truck dispatch over 50 simulated days. The program generates random orders, processes them through separate queues, and dispatches trucks when their capacity is reached.

## Features

- Generates random orders of three types: S, M, and B.
- Uses separate FIFO queues to manage order processing.
- Assigns random processing times to new orders.
- Tracks the number of completed orders for each truck type.
- Uses a LIFO stack to store and display dispatched trucks.
- Records order details, including the simulated day, order type, and original processing time.
- Displays daily queue states, truck fill progress, dispatched trucks, and a final order history table.

## Concepts Demonstrated

- C++ classes and objects
- Standard Library queues and stacks
- Arrays and record keeping
- Random number generation
- Loops, conditional statements, and functions
- Simulation and state management

## Technologies

- C++
- C++ Standard Library

## Running the Program

Compile with a C++ compiler that supports the required Standard Library features:

```bash
g++ warehouse_dispatch.cpp -o warehouse_dispatch
```

Run on Linux or WSL:

```bash
./warehouse_dispatch
```

On Windows, run the generated executable:

```bash
warehouse_dispatch.exe
```

## Project Context

Developed as an academic programming project to practise data structures and simulation in C++.
