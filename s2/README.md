# Laboratory measurement sessions

The C++17 application manages devices, timestamped readings and measurement
sessions. Devices grow their owned reading arrays as needed and calculate minimum,
maximum and average values. Sessions own devices and a dynamically allocated notes array; their destructor
releases the array. Copying a session
creates an independent snapshot, and moving one transfers its contents.

`Device` and `MeasurementSession` each define copy and move constructors and
assignment operators. The app runs eight ownership checks (four per class),
plus checks for growth, statistics and invalid inputs, before opening a small
interactive menu. An archive in the menu is a temporary snapshot demonstrated
in memory; it is not saved to disk.

From `s2/`:

```sh
cmake -S . -B build
cmake --build build
./build/app/app
```

Run just the checks without the menu using `./build/app/app --demo-only`. For a
multi-configuration generator, select a configuration with `cmake --build build
--config Debug` and run `build/app/Debug/app`.
