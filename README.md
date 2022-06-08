### HY340 Project

##### Building

Both compiler and virtual machine follow same procedure for building.
On the respective project directory run:
`$ make`

##### Running
Compiler: 
`./alpha.exe [input_file, [output_file]]`
If no output file is supplied then stout is used for output instead.
If no input file is supplied then stdin is used for input instead.

##### Testing

We have created a **tests/** directory under each module, which contains all the test files that we used to
assert the functionality of our code. Tests have been done on `damaskino`.
