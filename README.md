# GigaCell
## Transistor level automatic layout generator
### This repository aims to implement a transistor-level layout generator for unit circuits based on IC EDA Elite Challenge.


## Reference:
- Transistor level automatic layout generator for non-complementary CMOS cells[[1]](https://doi.org/10.1109/VLSISOC.2007.4402483)
- Transistor-Level Layout of Integated Circuits[[2]](https://www.pearsonhighered.com/assets/samplechapter/0/1/3/9/0139896902.pdf)

## TODO：
- File parser and writer implementation : Finished
- Database construction : Add pair, configuration, ...
- Problem modeling
- Basic algorithm implementation
- Add constraints: NetLength, Area, Pin Density, ...
- Algorithm Optimization

## Preliminaries
- Graph theory : Bipartite Matching
- Simulated Annealing
- Other optimization algorithms with multi-constraints
- Min-cut partitioning
## Operators
- Diffusion Sharing
- Flip
- Swap
- Folding
- Move
- Flip Flag
- Set gate nets' weights

## Framework
Partitioning --> Pairing -->

Random Swap --> Check Flip Flag -->

Diffusion Sharing --> Move --> Calculate Cost -->

Next Step --> ... -->

Converge --> Stop