import csv
import re

#DEFUNCT
def fixCSV(airlineReviews, newfile, layoverPattern):
    # This list features words to exclude while looking for layovers.
    exclude_list = ["viadana", "viareggio", "vianden", "via del mar", "bolivia", "viaduct",
                    "viagrande", "slovakia", "viacha", "rome via napoli", "viamao", "vianden castle", "scandinavia",
                    "moldovia", "aviation", "tel avia", "latvia", "monrovia", "avianca", "smartavia", "transavia",
                    "peruvian",
                    "viaair", "boliviana", "belavia"]
    # Open the output file with the specifed name.
    with open(newfile, mode = 'w', encoding = 'utf-8', newline = '') as newFile:
        # Create the writer object.
        writer = csv.writer(newFile, delimiter = ',')

        # Open the input file.
        with open(airlineReviews, encoding = 'utf-8') as reviews:
            # Create the reader object.
            reviewReader = csv.reader(reviews, delimiter = ',')

            # Used to track if we are at the header.
            row = 0
            for review in reviewReader:
                # Print the header if that's the row the reader is on.
                if (row == 0):
                    writer.writerow(review)

                # Otherwise, check for layovers in the "Route" column (9).
                else:
                    # Get the match.
                    match = re.search(layoverPattern, review[9])
                    if match:
                        # The city we need to check is the one before "via" and it exists in group 5
                        via_city = match.group(5)

                        # Check if the city contains "via" when it is not supposed to. This is basically a typo check.
                        if via_city and ("via" in via_city) and (via_city not in exclude_list):
                            review[9] = match.group(3) + match.group(4) + match.group(5)[0 : match.group(5).find('via')]
                        else:
                            review[9] = match.group(1)
                    writer.writerow(review)
                row += 1


# This function processes the csv file to create the one that will be used by the program.
def processCSV(input, output, rPattern, columnsToWrite, includeNoRoutes = True, writeMisses = False, replaceCodes = True, debug = False):
    # This list features cities to exclude while looking for layovers.
    exclude_list = ["viadana", "viareggio", "vianden", "via del mar", "bolivia", "viaduct",
                    "viagrande", "slovakia", "viacha", "rome via napoli", "viamao", "vianden castle", "scandinavia",
                    "moldovia", "aviation", "tel avia", "latvia", "monrovia", "avianca", "smartavia", "transavia",
                    "peruvian",
                    "viaair", "boliviana", "belavia"]

    '''OPENING FILES-------------------------------------------------------------------------------------------------'''
    # Open the output file.
    with open(output, mode = 'w', encoding = 'utf-8', newline = '') as out:
        # Create the writer object.
        writer = csv.writer(out, delimiter = ',')

        # Open the input file.
        with open(input, encoding = 'utf-8', newline = '') as inFile:
            # Create the reader object.
            reviewReader = csv.reader(inFile, delimiter = ',')

            # Create a separate file for checking non-matches.
            with open('misses.csv ', mode = 'w', encoding = 'utf-8', newline = '') as missesCSV:
                # Create the writer object.
                missesWriter = csv.writer(missesCSV, delimiter = ',')

                '''SETUP---------------------------------------------------------------------------------------------'''
                # Track the number of reviews without routes.
                no_route_count = 0

                # Track the number of misses.
                misses = 0

                # Track the number of processed reviews.
                processedReviews = 0

                # Tracks the number of layovers found.
                layover_count = 0

                # Track airport code misses and which codes were missed.
                if replaceCodes:
                    code_misses = 0
                    airport_misses = set()

                    # Set up the dictionary containing the airport codes.
                    airportCodes = extractCodesCSV('airports.csv')

                    # Set up the regex for finding airport codes. Finds a sequence of 3 and only 3 capitalized letters.
                    codePattern = re.compile(r'^[A-Z]{3}$')

                # This pattern is for checking for "XXX-XXX" or "XXX to XXX" formatting.
                sillyPattern = re.compile(r'(([\w]+)(-|\s+to\s+)([A-Z]+))')

                # This pattern is the exact same as punctualPattern, except it uses 'via' instead of 'to'.
                # DEFUNCT
                viaPattern = re.compile(r'^([\w.-]+(?:\s+[\w.-]+)*)(?:\s*\(\w*\s*\w*\))?\s+via\s+([\w.-]+(?:\s+[\w.-]+)*)(?:\s*\(\w*\s*\w*\))?\s*$')

                '''PROCESSING REVIEWS--------------------------------------------------------------------------------'''
                for review in reviewReader:
                    '''CORRECT FORMATTING CHECK----------------------------------------------------------------------'''
                    # Search for an accurate match to the correct pattern, excluding typos. When a correct route is found,
                    # columns 15 and 16 (Slug and Title) will be overwritten to store the values of source and destination.
                    match = re.search(rPattern, review[12])
                    airportHyphenMatch = re.search(sillyPattern, review[12])
                    #viaMatch = re.search(viaPattern, review[12])

                    if match:
                        # Set values in the source and destination columns.
                        review[15] = match.group(1)
                        review[16] = match.group(2)

                    # If a match is found with the format "XXX-XXX" or "XXX to XXX" (the latter should still be captured by the first pattern).
                    elif airportHyphenMatch:
                        # Set values in the source and destination columns.
                        review[15] = airportHyphenMatch.group(2)
                        review[16] = airportHyphenMatch.group(4)

                    # Exact same regex parameters as the first pattern, except checks for 'via'.
                    # DEFUNCT
                    #elif viaMatch:
                        # In the case of "Bali via Perth", Perth is the source and Bali is the destination, so the groups are mirrored.
                        #review[15] = viaMatch.group(2)
                        #review[16] = viaMatch.group(1)


                        '''MATCH NOT FOUND / NO ROUTE CHECK----------------------------------------------------------'''
                    # If a match is not found, write its ID to 'misses.csv' to improve data recognition. Prints the
                    # 'Route'(12) and 'unique-id'(21) columns for that review. I have tried multiple methods for
                    # selecting various columns but a generator is currently the only one that works consistently.

                    # When a review without a route is found, use the flags "NO_SOURCE" and "NO_DEST" in place of actual data.
                    else:
                        # This conditional will interpret anything unmatched as not having a route. This data is still
                        # useful, but it also means that as the recognition is improved, matches will automatically be included.
                        if includeNoRoutes:
                            review[15] = 'NO_SOURCE'
                            review[16] = 'NO_DEST'

                        # If there is no route data, the review is not considered a miss.
                        if writeMisses and review[12] != '':
                            misses += 1
                            missesWriter.writerow([review[index] for index in [12, 21]])

                    '''NULL RATING CHECK-----------------------------------------------------------------------------'''
                    # List generator for creating a list of the desired values. Checks if a given rating column does
                    # not have a value. If so, replace with '-1' so that it will be ignored when processed by the program.
                    line = [review[index] for index in columnsToWrite]
                    for index in range(1, 8):
                        if line[index] == '':
                            line[index] = '-1'

                    '''CORRECTLY FORMATTED LAYOVER CHECK-------------------------------------------------------------'''
                    # In the event that the route information is properly formatted, this will remove layover information.
                    # Searches for 'via' within the string and checks that it is not part of a country or city name.
                    if 'via' in line[10] and line[10][:line[10].find(' ')] not in exclude_list:
                        layover_count += 1
                        line[10] = line[10][:line[10].find(' v')]

                    '''AIRPORT CODE CHECK / REPLACEMENT--------------------------------------------------------------'''
                    if replaceCodes:
                        # Search for airport codes in the source and destination columns.
                        src = re.search(codePattern, line[9])
                        dest = re.search(codePattern, line[10])

                        # If matches are found, replace them.
                        if src:
                            try:
                                line[9] = airportCodes[line[9]]

                                # If no source city is found, set to no-route.
                                if line[9] == '':
                                    line[9] = 'NO_SOURCE'
                            except:
                                airport_misses.add(line[9])
                                line[9] = 'NO_SOURCE'
                                code_misses += 1

                        if dest:
                            try:
                                line[10] = airportCodes[line[10]]

                                # If no destination city is found, set to no-route.
                                if line[10] == '':
                                    line[10] = 'NO_DEST'
                            except:
                                airport_misses.add(line[10])
                                line[10] = 'NO_DEST'
                                code_misses += 1


                        # If there is an instance where there is no city for an airport code, the row is deemed no-route.
                        if line[9] == 'NO_SOURCE' or line[10] == 'NO_DEST':
                            line[9] = 'NO_SOURCE'
                            line[10] = 'NO_DEST'

                    # This is a check for making sure that poorly captured data OR airport code conversion misses
                    # do not impede on useful data. If the length of a source or destination somehow ends up at only
                    # one character, the whole row is deemed as having no route. The same applies for airport codes
                    # without corresponding city entries.
                    tinyPat = re.compile(r'^(.)$|^([A-Z]{3})$', flags = re.IGNORECASE)
                    srcMatch = re.search(tinyPat, line[9])
                    dstMatch = re.search(tinyPat, line[10])
                    if srcMatch or dstMatch:
                        line[9] = 'NO_SOURCE'
                        line[10] = 'NO_DEST'

                    if line[9] == 'NO_SOURCE':
                        no_route_count += 1

                    # Write the final processed line, ignoring the header.
                    if line[0] != "AirlineName":
                        processedReviews += 1
                        writer.writerow(line)

                '''DEBUG---------------------------------------------------------------------------------------------'''
                if debug:
                    # 129455 is the total number of reviews.
                    print("processed reviews:", f"\b {processedReviews}/129455", f"\b : {(processedReviews / 129455) * 100}%")

                    # 90,826 is the total number of reviews with route information.
                    # String formatting from https://stackoverflow.com/questions/455612/limiting-floats-to-two-decimal-points
                    print("route capture rate:", f"\b {90826 - misses}/90826", "\b :", "%.2f" % round((((90826 - misses) / 90826) * 100), 2), "\b%")
                    print("no route entries:", no_route_count)
                    print("layovers caught:", layover_count)
                    if replaceCodes:
                        print('airport code misses:', code_misses)
                        print("missed airport codes:", sorted(airport_misses))



# This function is going to replace airport codes with their respective cities to standardize the data.
# DEFUNCT
def replaceAirportCodes(airlineData, airportCodes):
    # A dictionary where the airport code will map to the name of the city it is in. Will be used for replacement.
    codes = {}

    # Open the csv containing the airport codes.
    with open(airportCodes, encoding = 'utf-8') as airportCodesFile:
        # Create the reader object.
        codeReader = csv.reader(airportCodesFile, delimiter = ',')

        # Add every airport code (column 0) and its corresponding city (column 9) as an entry in the dictionary.
        for line in codeReader:
            # Skip the header.
            if line[0] != 'code':
                codes[line[0]] = line[9]


    # Open the airline data.
    with open(airlineData, encoding = 'utf-8') as airlines:
        # Create the reader object.
        reviewReader = csv.reader(airlines, delimiter = ',')

        # Set up the regex for finding airport codes. Finds a sequence of 3 and only 3 capitalized letters.
        codePattern = re.compile(r'^[A-Z]{3}$')

        # Track the number of missing codes.
        missing_codes = 0
        misses = set()

        for review in reviewReader:
            src = re.search(codePattern, review[9])
            dest = re.search(codePattern, review[10])

            # Try to replace the source and destination codes with their corresponding cities.
            if src:
                try:
                    review[9] = codes[review[9]]
                except:
                    missing_codes += 1
                    misses.add(review[9])

            if dest:
                try:
                    review[10] = codes[review[10]]
                except:
                    missing_codes += 1
                    misses.add(review[10])

        print(missing_codes)
        print(misses)


# Processes 'airports.csv' to place all the codes and cities into a dictionary and return it. Called inside processCSV.
def extractCodesCSV(airportCodes):
    # Set up the dictionary to be returned.
    codeDict = {}

    # Open the csv containing the airport codes.
    with open(airportCodes, encoding='utf-8') as airportCodesFile:
        # Create the reader object.
        codeReader = csv.reader(airportCodesFile, delimiter=',')

        # Add every airport code (column 0) and its corresponding city (column 9) as an entry in the dictionary.
        for line in codeReader:
            # Skip the header.
            if line[0] != 'code':
                codeDict[line[0]] = line[9]

    # Not all the needed airport codes are listed in airports.csv, so they are being manually added here for the ones
    # that could be found.
    codeDict['BJS'] = 'Beijing'
    codeDict['BUE'] = 'Buenos Aires'
    codeDict['CMB'] = 'Colombo'
    codeDict['FOZ'] = 'Foz do Iguacu'
    codeDict['JKT'] = 'Jakarta'
    codeDict['LON'] = 'London'
    codeDict['MIL'] = 'Milan'
    codeDict['NYC'] = 'New York'
    codeDict['OSA'] = 'Osaka'
    codeDict['REK'] = 'Reykjavik'
    codeDict['ROM'] = 'Rome'
    codeDict['SAO'] = 'Sao Paulo'
    codeDict['SEL'] = 'Seoul'
    codeDict['STO'] = 'Stockholm'

    # These are hand-checked typos.
    # Typo for JFK.
    codeDict['JFL'] = 'New York'

    # Hand-checked and verified to be Las Vegas.
    codeDict['LVG'] = 'Las Vegas'

    # Hand-checked to be a typo for Jakarta.
    codeDict['CGL'] = 'Jakarta'

    # Checked reviews and determined DBX is Dubai.
    codeDict['DBX'] = 'Dubai'

    return codeDict


# This function opens the CSV and verifies that every source and destination entry is one word with no spaces.
def verify(dataPath):
    # Open the file.
    with open(dataPath, encoding = 'utf-8', newline = '') as data:
        # Create the reader object.
        dataReader = csv.reader(data, delimiter = ',')

        # Track the number of incorrect entries.
        misses = 0

        # Iterate through every entry.
        for entry in dataReader:
            # Check the sources and destinations.
            if entry[9] == '' or len(entry[9]) <= 1:
                misses += 1
            if entry[10] == '' or len(entry[10]) <= 1:
                misses += 1

        # Display the number of misses.
        print("incorrect entries:", misses)


def main():
    # THIS PROGRAM OPERATES ON UNMODIFIED VERSIONS OF THE ORIGINAL DATASETS.
    '''
    Column Legend for AirlineReviews.csv (129456 rows)      Column Legend for airports.csv (missing some codes)
    0 - Aircraft                                            0 - code
    1 - AirlineName                                         1 - time_zone_id
    2 - CabinType                                           2 - name
    3 - DateFlown                                           3 - city_code
    4 - DatePub                                             4 - country_id
    5 - EntertainmentRating                                 5 - location
    6 - FoodRating                                          6 - elevation
    7 - GroundServiceRating                                 7 - url
    8 - OriginCountry                                       8 - icao
    9 - OverallScore                                        9 - city
    10 - Recommended                                        10 - county
    11 - Review                                             11 - state
    12 - Route
    13 - SeatComfortRating
    14 - ServiceRating
    15 - Slug
    16 - Title
    17 - TravelType
    18 - TripVerified
    19 - ValueRating
    20 - WifiRating
    21 - unique_id
    '''

    # Create a list containing the indices of the desired columns from AirlineReviews.csv.
    COLUMNS_TO_WRITE = [1, 9, 5, 6, 13, 14, 19, 7, 20, 15, 16]

    '''
    Column Legend for AirlineData.csv
    0 - AirlineName
    1 - OverallScore
    2 - EntertainmentRating
    3 - FoodRating
    4 - SeatComfortRating
    5 - ServiceRating
    6 - ValueRating
    7 - GroundServiceRating
    8 - WifiRating
    9 - Source
    10 - Destination
    '''

    # This pattern searches for "via" and any word following. We do not care about layovers.
    # DEFUNCT
    pattern = re.compile(r'(((.*)(\s+to\s+)(.*)|(([\w]+)-([A-Z]+))))\s+via\s+(\b\w+\b)\s*', flags=re.IGNORECASE)

    # This pattern is explicitly for checking that there is proper route information.
    # DEFUNCT
    routePattern = re.compile(r'^((\b\w+(\s+\w+)*\b)\s+to\s+(\b\w+(\s+\w+)*\b))|(\b\w+)(-)(\w+\b)$', flags = re.IGNORECASE)

    # Barebones route pattern.                              Groups:
    # DEFUNCT
    bareRoutePattern = re.compile(r'^(\b\w+(\s+\w+)*\b)'  # 1 - Matches single or multi-word cities/airport codes. 
                                                          #     EX: 'Paris', 'Cape Town', 'LGA'
                                  r'\s+to\s+'             # 2 - Matches the phrase ' to ' with at least one space on either side. 
                                  r'(\b\w+(\s+\w+)*\b)'   # 3 - Matches single or multi-word cities/airport codes. Same as first group.
                                  r'\s*$',                #     Allows for an optional space at the end of the last string.
                                  flags = re.IGNORECASE)  #     Ignores the case of all characters.

    # Route pattern with punctuation.                            Groups:
    punctualPattern = re.compile(r'^([\w.-]+(?:\s+[\w.-]+)*)'  # 1 - Matches a single or multiword city/airport code, with hyphens and periods allowed. 
                                                               #     EX: 'Paris', 'Cape Town', 'LGA', 'St. Petersburg', 'Ixtapa-Zihuatanejo'
                                 r'(?:\s*\(\w*\s*\w*\))?'      # NON-CAPTURING - OPTIONALLY matches a space followed by an airport code in parentheses '(XXX)'.
                                 r'\s+to\s+'                   #     Matches the phrase 'to' with at least one space on either side. 
                                 r'([\w.-]+(?:\s+[\w.-]+)*)'   # 2 - Same as first group. 
                                 r'(?:\s*\(\w*\s*\w*\))?'      # NON-CAPTURING - Same as first noncapturing group. 
                                 r'\s*$',                      #     Allows for an optional space at the end of the last string.
                                 flags = re.IGNORECASE)        #     Ignores the case of all characters.

    # Used to choose if debug information is shown and then if the output file is verified.
    DEBUG = False

    # Process the CSV containing the reviews.
    processCSV('AirlineReviews.csv', 'AirlineData.csv', punctualPattern, COLUMNS_TO_WRITE, debug = DEBUG)

    # If the script is in debug mode, verify the data.
    if DEBUG:
        verify('AirlineData.csv')

    exit()

if __name__ == '__main__':
    main()