import csv
import re

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

# This function is going to process the fixed csv file to create the one that will be used by the program.
def processCSV(input, output, layoverPattern, rPattern):
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

            for review in reviewReader:
                '''
                # Check for layovers.
                match = re.search(layoverPattern, review[9])
                if match:
                    silly = re.search(XXXpattern, match)
                    # Check if the route format is "XXX-XXX". Otherwise it will be "[source] to [dest]"
                    if silly.group(0):
                        source = match.group(7)
                        dest = match.group(8)
                    else:
                        source = match.group(3)
                        dest = match.group(5)
                    writer.writerow(review[1:8] + ',' + source + ',' + dest)
                else:
                    print(review[18])
                '''
                # Search for an accurate match to the correct pattern, excluding typos.
                match = re.search(rPattern, review[9])
                if match:
                    # Set values in the source and destination columns.
                    review[10] = match.group(1)
                    review[11] = match.group(3)
                #else:
                    #review[10] = match.group(7)
                    #review[11] = match.group(9)
                # Create a list containing the indices of the desired columns from the csv.
                columns_to_write = [0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11]

                # List generator for creating a list of the desired values.
                line = [review[index] for index in columns_to_write]

                # In the event that the route information is properly formatted, this will remove layover information.
                # Searches for 'via' within the string and checks that it is not part of a country or city name.
                if 'via' in line[10] and line[10][:line[10].find(' ')] not in exclude_list:
                    line[10] = line[10][:line[10].find(' v')]

                # Checks that the source and destination values are not empty.
                if line[9] != '' and line[10] != '':
                    writer.writerow(line)

def main():
    # This pattern searches for "via" and any word following. We do not care about layovers.
    pattern = re.compile(r'(((.*)(\s+to\s+)(.*)|(([\w]+)-([A-Z]+))))\s+via\s+(\b\w+\b)\s*', flags=re.IGNORECASE)
    # This pattern is explicitly for checking for "XXX-XXX" formatting.
    sillyPattern = re.compile(r'(([\w]+)-([A-Z]+))', flags = re.IGNORECASE)
    # This pattern is explicitly for checking that there is proper route information.
    routePattern = re.compile(r'^((\b\w+(\s+\w+)*\b)\s+to\s+(\b\w+(\s+\w+)*\b))|(\b\w+)(-)(\w+\b)$', flags = re.IGNORECASE)
    # Barebones route pattern.
    bareRoutePattern = re.compile(r'^(\b\w+(\s+\w+)*\b)\s+to\s+(\b\w+(\s+\w+)*\b)$', flags = re.IGNORECASE)


    #fixCSV('AirlineReviews.csv', 'test_12-2-23.csv', pattern)
    processCSV('AirlineReviews.csv' , 'processTest.csv', pattern, bareRoutePattern)
    exit()

if __name__ == '__main__':
    main()