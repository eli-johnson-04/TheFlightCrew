import csv
import re

#todo: currently defunct
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
def processCSV(input, output, rPattern, columnsToWrite, includeNoRoutes, outputMisses):
    # This list features words to exclude while looking for layovers.
    exclude_list = ["viadana", "viareggio", "vianden", "via del mar", "bolivia", "viaduct",
                    "viagrande", "slovakia", "viacha", "rome via napoli", "viamao", "vianden castle", "scandinavia",
                    "moldovia", "aviation", "tel avia", "latvia", "monrovia", "avianca", "smartavia", "transavia",
                    "peruvian",
                    "viaair", "boliviana", "belavia"]

    # "Open" the output file.
    with open(output, mode = 'w', encoding = 'utf-8', newline = '') as out:
        # Create the writer object.
        writer = csv.writer(out, delimiter = ',')

        # Open the input file.
        with open(input, encoding = 'utf-8') as inFile:
            # Create the reader object.
            reviewReader = csv.reader(inFile, delimiter = ',')

            # Create a separate file for checking non-matches.
            with open('misses.csv ', mode = 'w', encoding = 'utf-8', newline = '') as missesCSV:
                # Create the writer object.
                missesWriter = csv.writer(missesCSV, delimiter = ',')

                # TODO: the number of reviews without routes is not accounting for the discrepancy between total reviews and the sum of matches and misses???
                no_route_count = 0

                for review in reviewReader:
                    # Search for an accurate match to the correct pattern, excluding typos. When a correct route is found,
                    # columns 15 and 16 (Slug and Title) will be overwritten to store the values of source and destination.
                    match = re.search(rPattern, review[12])
                    if match:
                        # Set values in the source and destination columns.
                        review[15] = match.group(1)
                        review[16] = match.group(3)

                    # If a match is not found, write its ID to 'misses.csv' to improve data recognition. Prints the
                    # 'Route'(12) and 'unique-id'(21) columns for that review. I have tried multiple methods for
                    # selecting various rows but a generator is currently the only one that works consistently.

                    # When a review without a route is found, use the flags "NO_SOURCE" and "NO_DEST" in place of actual data.
                    else:
                        if includeNoRoutes and review[12] == '':
                            review[15] = 'NO_SOURCE'
                            review[16] = 'NO_DEST'
                            no_route_count += 1
                        elif outputMisses:
                            missesWriter.writerow([review[index] for index in [12, 21]])

                    # List generator for creating a list of the desired values. Checks if a given rating column does
                    # not have a value. If so, replace with '-1' so that it will be ignored when processed by the program.
                    line = [review[index] for index in columnsToWrite]
                    for index in range(1, 8):
                        if line[index] == '':
                            line[index] = '-1'

                    # In the event that the route information is properly formatted, this will remove layover information.
                    # Searches for 'via' within the string and checks that it is not part of a country or city name.
                    if 'via' in line[10] and line[10][:line[10].find(' ')] not in exclude_list:
                        line[10] = line[10][:line[10].find(' v')]


                    # Checks that the source and destination values are not empty, and that they have no spaces.
                    # This keeps improper information out, such as unmodified slug or review values.
                    if line[9] != '' and line[10] != '':
                        if ' ' not in line[9] and ' ' not in line[10]:
                            writer.writerow(line)

def main():
    # THIS PROGRAM OPERATES ON AN UNMODIFIED VERSION OF THE DATASET DIRECTLY FROM KAGGLE.
    '''
    Column Legend:
    0 - Aircraft
    1 - AirlineName
    2 - CabinType
    3 - DateFlown
    4 - DatePub
    5 - EntertainmentRating
    6 - FoodRating
    7 - GroundServiceRating
    8 - OriginCountry
    9 - OverallScore
    10 - Recommended
    11 - Review
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

    # Create a list containing the indices of the desired columns from the csv.
    columns_to_write = [1, 9, 5, 6, 13, 14, 19, 7, 20, 15, 16]

    # This pattern searches for "via" and any word following. We do not care about layovers.
    # DEFUNCT
    pattern = re.compile(r'(((.*)(\s+to\s+)(.*)|(([\w]+)-([A-Z]+))))\s+via\s+(\b\w+\b)\s*', flags=re.IGNORECASE)

    # This pattern is explicitly for checking for "XXX-XXX" formatting.
    sillyPattern = re.compile(r'(([\w]+)-([A-Z]+))', flags = re.IGNORECASE)

    # This pattern is explicitly for checking that there is proper route information.
    # DEFUNCT
    routePattern = re.compile(r'^((\b\w+(\s+\w+)*\b)\s+to\s+(\b\w+(\s+\w+)*\b))|(\b\w+)(-)(\w+\b)$', flags = re.IGNORECASE)

    # Barebones route pattern.                              Groups:
    bareRoutePattern = re.compile(r'^(\b\w+(\s+\w+)*\b)'  # 1 - Matches single or multi-word cities/airport codes. 
                                                          #     EX: 'Paris', 'Cape Town', 'LGA'
                                  r'\s+to\s+'             # 2 - Matches the phrase ' to ' with any number of spaces around it.
                                  r'(\b\w+(\s+\w+)*\b)'   # 3 - Matches single or multi-word cities/airport codes. Same as first group.
                                  r'\s*$',                #     Allows for an optional space at the end of the last string.
                                  flags = re.IGNORECASE)  # Ignores the case of all characters.


    #fixCSV('AirlineReviews.csv', 'test_12-2-23.csv', pattern)
    processCSV('AirlineReviews.csv', 'AirlineData.csv', bareRoutePattern, columns_to_write, includeNoRoutes = True, outputMisses = True)
    exit()

if __name__ == '__main__':
    main()