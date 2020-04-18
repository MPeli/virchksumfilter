Virus sample checksum filter (virchksumfilter)
----------------------------------------------

The program reads lines of base64-encoded checksums from the standard input and writes
filtered results in an opposite order to the standard output.

This utility has two modes of operation:

 * Filtering (set by command-line argument "-f").
 * Replacing (set by command-line argument "-r").

It is mandatory for the user to use one of the "-f" or "-r" arguments and they
cannot be used both simultaneously.

Another mandatory argument is a configuration file name.

In case of the filtering mode (-f), it contains checksums to be filtered out,
each checksum on a new line. (See "filter.cfg" example file.)

In case of the replacing mode (-r), the configuration file contains lines
with pairs of a regular expression matching certain checksums and their
replacement, separated by one or more space characters. You can safely assume
that any checksum can be matched by a single regular expression only.
(See "replace.cfg" example file.)

The algorithm works as follows:

 1. Reads a configuration file.
 2. Reads checksums from the standard input. Checksums are separated by spaces
    or new-lines.
 3. Replaces or removes checksums (based on the operation mode) and writes the
    checksums to standard output in the opposite order they were read, each
    checksum on a new line.

Sample configuration files and checksum input are attached.


Examples using the attached sample configuration
------------------------------------------------

    > cat .\inputF.txt | .\virchksumfilter -f filter.cfg
    b21lZGlhLWViZjA3Njc0MTFkYTg3NmMwMWIwMWZhOTI2MThlNjNlZTIwMWE2ODg=

    > cat .\inputR.txt | .\virchksumfilter -r replace.cfg
    bXNvZndvLWMwYWM4NGUxOGEzNWViODY2ZTJhMjExY2QzMmE3MjkzZTcxODE5MGM=
    dmVyaWZ5LTZmMzM3ZDdhZWMzOTZmMGVmNzA4ODM5OTcxYjFhZjRkMmMwMGE1ZjM=
    ZmFsc2VwLTA4OTYxNjU0MzkxOWFlODI4YzMzZTQ5YmYwMjMyMDNkYjU2ZGNiN2Q=


How to run
---------------------------

Navigate to Relase folder, open a command line prompt and run one of the following commands,
make sure that all the input files exist

 1. cat .\inputF.txt | .\virchksumfilter -f filter.cfg
 2. cat .\inputR.txt | .\virchksumfilter -r replace.cfg

Experienced developers can try one of the these. It is recommended to comment out 
writing to standard output. 

 3. cat ..\tester-generator\input.txt | .\virchksumfilter -f ..\tester-generator\filter.cfg
 4. cat ..\tester-generator\input.txt | .\virchksumfilter -r ..\tester-generator\replace.cfg

Solution structure
---------------------------
There is one static library (Common) which is used by two executables (test-generator.exe) and (virchksumfilter.exe).
You are most likely interestd in virchksumfilter, however, if you wish to generate some input files
for the virchksumfilter or play with containers, check the test-generator project.

Good luck.