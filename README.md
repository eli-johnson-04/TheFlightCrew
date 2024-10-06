# No Room for Air-or
This project features an SFML executable that uses a dataset of 129,455 flight reviews to give a user the best recommendation for an inputted source and destination city. It will show all of the airlines that fly the route, ranked by overall score (out of 10), as well as averaged ratings (out of 5) for a variety of aspects of the in-flight experience. All of the reviews are from real people. 

## Table of Contents
[Airline Processing](https://github.com/eli-johnson-04/TheFlightCrew/tree/main/Airline%20Processing) - Contains the backend for the program that processes the formatted reviews. The Processor class contains the Hash Map and the Splay Tree and handles all data operations.\
[NoRoomForAiror SFML](https://github.com/eli-johnson-04/TheFlightCrew/tree/main/NoRoomForAiror%20SFML) - Contains the final SFML application with the user interface. \
[Project 3 Testing](https://github.com/eli-johnson-04/TheFlightCrew/tree/main/Project%203%20Testing) - Contains the integration of the backend and the frontend, used for testing and to generate a working executable. \
[data_processing](https://github.com/eli-johnson-04/TheFlightCrew/tree/main/data_processing) - Contains the Python script that processes the airline reviews and outputs the formatted data. See *Data* for more information. 

## Tutorial
Download the [release](https://github.com/eli-johnson-04/TheFlightCrew/releases/tag/release), extract the folder, then navigate to NoRoomForAiror\NoRoomForAiror SFML\cmake-build-debug and run the executable. Ignore the Windows Defender message. You can trust us :)\
This project is dependent on SFML. (see *Data*)

## Purpose
**No Room for Air-or** is a final project for COP3530 - Data Structures and Algorithms. The purpose of the project is to compare two data structures or algorithms using a dataset with >100,000 elements. In our case, we compared the search performance of a Hash Map, implented as an std::unordered_map, with a Splay Tree we found online for educational purposes. In our testing, we often found the Splay Tree to be just a little bit faster than the std::unordered_map, usually by a few hundred thousandths of a second. 

## Features
The program allows the user to input a source city and a destination city using the **GO** button. Then, airlines that cover the route, using data from the reviews, are shown and ranked by overall score, out of ten. Other rating categories are shown, including Entertainment, Food, Comfort, Service, Value, Ground Service, and Wifi. These are ranked out of five. The program also uses text in the whimsical Comic Neue font, with bright colors and graphics. 

## Data
The dataset containing the reviews is too large to be stored in the repo, but you can download it [here](https://www.kaggle.com/datasets/joelljungstrom/128k-airline-reviews/). However, the processed data *AirlineData.csv* and corresponding *misses.csv* in data_processing are current as of 12-4-23. *misses.csv* stores the route and respective unique-id associated with the missed reviews. The release is dependent on an [SFML install of 2.5.1 or later](https://www.sfml-dev.org/download/sfml/2.6.1/).

## Credits
Joseph Benigno [jbenigno@ufl.edu](mailto:jbenigno@ufl.edu) - Programmer, User Interface\
Elijah Johnson [elijah.johnson@ufl.edu](mailto:elijah.johnson@ufl.edu) - Programmer, Raw Data Handling and Formatting\
Jonathan Xavioer [jxavioer@ufl.edu](mailto:jxavioer@ufl.edu) - Programmer, Proccessed Data Manipulation and Data Structures\
Report - [Google Docs Link](https://docs.google.com/document/d/1xB2XX0hDOQ4nfWiN1vOKUG-qVA9NmOm_BXc9q97QiT8/edit?usp=sharing)

### Resources/Libraries
C++ SFML - [link](https://www.sfml-dev.org/)\
RapidCSV - [link](https://github.com/d99kris/rapidcsv)\
Splay Tree - [link](https://github.com/Bibeknam/algorithmtutorprograms/tree/master/data-structures/splay-trees)

## UNIVERSITY OF FLORIDA HONOR CODE NOTICE

This repository contains coursework for *COP3530: Data Structures and Algorithms* at the University of Florida. It is intended to be viewed and modified solely by its specified collaborators:

- [Joseph Benigno](https://github.com/jojongx)
- [Elijah Johnson](https://github.com/eli-johnson-04)
- [Jonathan Xavioer](https://github.com/jxavioer)

### Usage Restrictions:
1. This code is not open-source and is not available for general use, modification, or distribution.
2. Viewing this repository does not grant any rights or licenses to use, modify, or share its contents.
3. Current University of Florida students are expressly prohibited from using, referencing, or adapting any part of this code for their own coursework.

### Academic Integrity:
Any unauthorized access, use, copying, or adaptation of this repository's contents may constitute:
1. A violation of the University of Florida Student Honor Code and Student Conduct Code.
2. Academic misconduct, which may result in severe penalties.
3. Copyright infringement.

Such violations will be reported to the appropriate university authorities.

### For Recruiters and Prospective Employers:
This repository is made visible for demonstration of coding skills and project experience only. Any use beyond evaluation for employment purposes is not permitted without explicit written consent from the repository owners and the course instructor.

For more information on the UF Honor Code, please refer to the [University of Florida Student Honor Code and Student Conduct Code Regulation](https://sccr.dso.ufl.edu/policies/student-honor-code-student-conduct-code/).

© 2024 Joseph Benigno, Elijah Johnson, Jonathan Xavioer. All Rights Reserved.
