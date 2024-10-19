# HTML Home Work 1 Code
### B13902149 高翊恩
### last edit: 2024/10/03
---

## Main script (Linear Regression)
```
g++ -std=c++17 ./main.cpp -D PRINT
./a.out output_10.txt < data.txt
g++ -std=c++17 ./main.cpp -D MULTIPLE_N -D PRINT
./a.out output_11.txt < data.txt
g++ -std=c++17 ./main.cpp -D MULTIPLE_N -D POP_TO_2 -D PRINT
./a.out output_12.txt < data.txt
```

## Generate Figure
```
python3 -m venv ./python
./python/bin/pip install matplotlib PyQt6
./python/bin/python ./python/scatter_chart.py figure_10.png < output_10.txt
./python/bin/python ./python/colored_scatter_chart.py figure_11.png < output_11.txt
./python/bin/python ./python/colored_scatter_chart.py figure_12.png < output_12.txt
```
