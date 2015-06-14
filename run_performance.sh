#!/bin/bash

mkdir build
make all
#python bench.py
#python make_chart_data.py < output | python make_html.py

#python bench_get_set.py
#python make_chart_data_get_set.py < output | python make_html_get_set.py

python bench_bulk.py
python make_chart_data_bulk.py < output | python make_html.py