#!/bin/bash

echo 'Generating documentation...'
doxygen FractalCooker.doxyfile > doxygen_log.log
echo 'Documentation complete : '
cat doxygen.log
