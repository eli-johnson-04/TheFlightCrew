import csv
import re

def fixCSV(airlineReviews, newfile):
    # This list features words to exclude while looking for layovers.
    exclude_list = ["viadana", "viareggio", "vianden", "via del mar", "bolivia", "viaduct",
    "viagrande", "slovakia", "viacha", "rome via napoli", "viamao", "vianden castle", "scandinavia",
    "moldovia", "aviation", "tel avia", "latvia", "monrovia", "avianca", "smartavia", "transavia", "peruvian",
    "viaair", "boliviana", "belavia"]


    # This pattern searches for "via" and any word following. We do not care about layovers.
    layoverPattern = re.compile(r'(((.*)(\s+to\s+)(.*)|[\w]+-[A-Z]+))\s+via\s+(\b\w+\b)\s*', flags = re.IGNORECASE)

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

                # Otherwise, check for layovers in the "Route" column (10).
                else:
                    # Get the match.
                    match = re.search(layoverPattern, review[10])
                    if match:
                        # The city we need to check is the one before "via" and it exists in group 5
                        via_city = match.group(5)

                        # Check if the city contains "via" when it is not supposed to. This is basically a typo check.
                        if via_city and ("via" in via_city) and (via_city not in exclude_list):
                            review[10] = match.group(3) + match.group(4) + match.group(5)[0 : match.group(5).find('via')]
                        else:
                            review[10] = match.group(1)
                    writer.writerow(review)
                row += 1

def main():
    fixCSV('AirlineReviews.csv', 'test_12-2-23.csv')
    exit()

if __name__ == '__main__':
    main()