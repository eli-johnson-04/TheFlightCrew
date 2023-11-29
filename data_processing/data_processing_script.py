import csv
import re

def fixCSV(airlineReviews, newfile):
    # This list features words to exclude while looking for layovers.
    exclude_list = ["viadana", "viareggio", "vianden", "via del mar", "bolivia", "viaduct",
    "viagrande", "slovakia", "viacha", "rome via napoli", "viamao", "vianden castle", "scandinavia",
    "moldovia", "aviation", "tel avia", "latvia", "monrovia", "avianca", "smartavia", "transavia", "peruvian",
    "viaair", "boliviana", "belavia"]

    # This pattern searches for "via" and any word following. We do not care about layovers.
    layoverPattern = re.compile(r'\bvia\b\s+(?!' + '|'.join(map(re.escape, exclude_list)) + r')\w+', flags=re.IGNORECASE)

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
                    if layoverPattern.search(review[10]):
                        # Get rid of the layover information.
                        review[10] = layoverPattern.sub('', review[10]).strip()
                    writer.writerow(review)
                row += 1
                #TODO: fix shitty data entry ????

def main():
    fixCSV('AirlineReviews.csv', 'test.csv')
    exit()

if __name__ == '__main__':
    main()