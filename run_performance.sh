#!/bin/bash

mkdir build
make all
python bench.py
python make_chart_data.py < output | python make_html.py