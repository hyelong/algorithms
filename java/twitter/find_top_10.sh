#!/bin/bash

cat find_top_10.txt | tr '$' '\n' | sort | uniq -c | sort -r | head -3
