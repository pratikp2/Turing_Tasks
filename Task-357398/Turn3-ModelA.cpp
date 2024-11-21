cppcheck_run(
       INPUTS src/main.cpp src/another_source.cpp
       OUTPUT_XML output/cppcheck_report.xml
       OPTIONS --inline-suppr --suppress=all --enable=all
     )
