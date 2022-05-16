# edge_coupled_cpwg

Impedance calculator for conductor-backed edge coupled coplanar waveguides



A simple and very efficient calculator of a differential pair impedance in a specific scenario, shown in ascii-art below.

The reason for creating this tool is I failed to find any other (free and open source) alternative. Certainly built-in KiCad calculators can't handle this case.

Simulations suggest this may be a viable way of routing proper, impedance matched differential pairs on any cheap, 2-layer prototype grade PCBs, such as offered by JLCPCB or OSH Park. 

```
[mctom@Tomusiomat edge_coupled_cpwg]$ edge_coupled_cpwg 

Conductor-backed edge coupled coplanar waveguides calculator
By Tomek Szczęsny, 2022

Based on:
Rainee N. Simons "Coplanar waveguide Circuits, Components, and Systems", 2001, Ch. 7.4
Brian C. Wadell "Transmission Line Design Handbook", 1991, Ch. 4.4.3

Usage:
edge_coupled_cpwg d S W t h Er

Example:
edge_coupled_cpwg 0.2 0.41 0.2 0.035 1.593 4.5

                      / /   /            / /   /            / /   /             
                     / /   /            / /   /            / /   /              
                    / /   /            / /   /            / /   /               
                   / /   /            / /   /            / /   /                
                  / /   /            / /   /            / /   /                 
-----------------+ /   +------------+ /   +------------+ /   +----------------  
  Ground Plane   |/    |   Diff -   |/    |   Diff +   |/    | Ground Plane   }t
-----------------+-----+------------+-----+------------+-----+----------------  
 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ^ 
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . | 
 . . . . . . . . . . . . . . . . .Dielectric . . . . . . . . . . . . . . . .  |h
. . . . . . . . . . . . . . . . . . . Er. . . . . . . . . . . . . . . . . . . | 
 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  | 
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . v 
------------------------------------------------------------------------------  
                           G r o u n d   P l a n e                              
                                                                                
                 |     |            |     |            |     |                  
                 |<--->|<---------->|<--->|<---------->|<--->|                  
                    W        S         d         S        W                     

[mctom@Tomusiomat edge_coupled_cpwg]$ edge_coupled_cpwg 0.2 0.41 0.2 0.035 1.593 4.5
Er_even = 2.82664
Er_odd  = 2.82057
Zeven   = 97.0059
Zodd    = 50.0657
Z0      = 69.6898
Zdiff   = 100.131
Zcomm   = 48.503
```

### Building and installation

This program is written in C++. In order to build it, GNU g++ 6.0 or above is required along with standard `cmath` library, or any other compiler that knows what `std::comp_ellint_1` is. Tested on Linux.

```
make
sudo make install
```



### Accuracy of the results

The formule and methodology implemented in this program has been created by far greater minds than my own, and described in source literature. I cannot claim I understand how this works and cannot make any claims about the performance of this software.

However, the same setup has been simulated using commercial `Si9000` and open-source `atlc`. The latter allows for simulation with any degree of precision that I classified by input bitmap size in bytes. Larger bitmaps contain more details, both in terms of input and intermediate simulation data, however simulation time quickly gets unbearable.

These are the results for selected programs, all with the same input data:

`edge_coupled_cpwg 0.15 0.28 0.15 0.035 1.593 4.5`

| Software          | Precision | Execution time | Zdiff   |
| ----------------- | --------- | -------------- | ------- |
| atlc              | 78198     | 362ms          | 120,504 |
| atlc              | 340086    | 2,73s          | 106,741 |
| atlc              | 698598    | 8,79s          | 103,124 |
| atlc              | 1204374   | 20,1s          | 100,429 |
| atlc              | 3668374   | 1m51s          | 98,418  |
| atlc              | 14536374  | 16m41s         | 97,063  |
| atlc              | 32604374  | 59m58s         | 96,605  |
| atlc              | 90340374  | 4h58m          | 96,117  |
| atlc              | 360680374 | 40h45m         | 95,234  |
| Si9000            | N/A       | Unknown        | 96,20   |
| edge_coupled_cpwg | N/A       | 9ms            | 102,841 |

The conclusion is left to the user.

### Disclaimer

This tool is provided as-is and may be used as you wish. Don't blame me if it won't work as you expected. Don't use it if anything serious is at stake.

By using this tool you agree to report back whether you got a working differential pair or not. ;)
